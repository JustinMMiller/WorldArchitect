#include "GridMapGenerator.h"



using namespace std;
using namespace WorldArchitect;
//Constructor. Sets the method used.
GridMapGenerator::GridMapGenerator(Method method) :lock() 
{
	selection = method;
}


///This function returns all the points which are neighbors to the 
///given coordinate (x, y) in the given GridMap.
///Note: This method does return the given point in the set of Points it returns.
vector<Point> GridMapGenerator::getNeighbors(GridMap *map, int x, int y)
{
	vector<Point> ret;
	vector<int> xSet, ySet;
	if(x == 0)
	{
		xSet.push_back(0);
		xSet.push_back(1);
		xSet.push_back(map->getSizeX()-1);
	}
	else if(x == map->getSizeX()-1)
	{
		xSet.push_back(map->getSizeX()-2);
		xSet.push_back(map->getSizeX()-1);
		xSet.push_back(0);
	}
	else
	{
		xSet.push_back(x-1);
		xSet.push_back(x);
		xSet.push_back(x+1);
	}
	if(y == 0)
	{
		ySet.push_back(0);
		ySet.push_back(1);
		ySet.push_back(map->getSizeY()-1);
	}
	else if(x == map->getSizeY()-1)
	{
		ySet.push_back(map->getSizeY()-2);
		ySet.push_back(map->getSizeY()-1);
		ySet.push_back(0);
	}
	else
	{
		ySet.push_back(y-1);
		ySet.push_back(y);
		ySet.push_back(y+1);
	}

	for(int i : xSet)
	{
		for(int j : ySet)
		{
			Point p;
			p.x = i;
			p.y = j;
			ret.push_back(p);
		}
	}
	return ret;
}


/// \class Compare
/// \brief Internal class for ordering Point by Perlin noise value
///
/// Internal class to sort Point based on Perlin noise value of x, y coordinate
/// Class for comparing Points for ordering in a priority_queue. This is used in 
/// Method GridPerlin.
class Compare
{
	bool reverse;
	Perlin *p;
	double scaleX, scaleY;
	public:
	Compare(const bool& revparam = false, int x = 0, int y = 0, Perlin *perlin = NULL)
		: scaleX(x), scaleY(y)
	{
		if(perlin != NULL)
		{
			p = perlin;
		}
		else
		{
			p = new Perlin();
		}
		reverse = revparam;
	}
	bool operator() (Point& lhs, Point& rhs)
	{
		double lx, ly, rx, ry;
		lx = (double)lhs.x / scaleX;
		ly = (double)lhs.y / scaleY;
		rx = (double)rhs.x / scaleX;
		ry = (double)rhs.y / scaleY;
		if(reverse) return (p->octaveNoise(lx, ly) > p->octaveNoise(rx, ry));
		else return p->octaveNoise(lx, ly) < p->octaveNoise(rx, ry); 
	}
};


//This is the method each thread runs. It takes in the starter Landmasses and the associated candidates and
//grows it according to the chosen method. Defaults to GridRandom.
void GridMapGenerator::growLandmass(GridMap *map, vector<Point> Landmass, vector<Point> Candidates, int numCand, Perlin *perlin)
{
	Logger *l = LogManager::getInstance()->getLogger(MapCreation);
	Perlin *perl = new Perlin();
	int numCands = numCand;
	bool canContinue = true;
	typedef priority_queue<Point, vector<Point>, Compare> mypq;
	GridPoint first = map->getGridPointAt(Landmass[0].x, Landmass[0].y);
	mypq pq(Compare(first.LandmassIndex%2==0, map->getSizeX(), map->getSizeY(), perlin));
	for(Point p : Candidates)pq.push(p);
	while(numUsed < landTiles && canContinue)
	{
		if(numCands == 0)
		{
			canContinue = false;
			break;
		}
		Point addPoint;
		int cn = 0;
		if(selection == GridPerlin)
		{
			cn = ceil((double)numCands * 0.1);
			int sel = 0;
			if(cn > 0)sel = rand()%cn;
			vector<Point> t(sel);
			for(int k = 0; k < sel; k++)
			{
				t.push_back(pq.top());
				pq.pop();
			}
			addPoint = pq.top();
			pq.pop();
			for(Point p : t)pq.push(p);
		}
		else
		{
			cn = rand()%numCands;
			addPoint = Candidates[cn];
		}
		GridPoint add = map->getGridPointAt(addPoint.x, addPoint.y);
		double h = perl->noise((double)(add.x / (double)map->getSizeX()) * 10,0, (double)(add.y / (double)map->getSizeY())* 10.0);
		h = h - floor(h);
		h = floor(255*h);
		add.height = h;
		string str = to_string(add.x) + " " + to_string(add.y) + " " +  to_string(add.height) + "\n";
		std::cout << str;
		l->log(str);
		bool canAdd = true;
		vector<Point> neighbors = getNeighbors(map, add.x, add.y);
		for(Point p : neighbors)
		{
			GridPoint g = map->getGridPointAt(p.x, p.y);
			if(g.LandmassIndex == -1)
			{
				g.LandmassIndex = add.LandmassIndex;
				map->updateGridPointAt(p.x, p.y, &g);
				if(selection == GridPerlin)
				{
					pq.push(p);
				}
				else
				{
					Candidates.push_back(p);
				}
				numCands++;
			}
			else if(g.LandmassIndex != add.LandmassIndex && rand()%100 >= 5)
			{
				canAdd = false;
			}
		}
		if(canAdd)
		{
			add.water = false;
			map->updateGridPointAt(addPoint.x, addPoint.y, &add);
			Landmass.push_back(addPoint);
			lock.lock();
			numUsed++;
			lock.unlock();
		}
		if(selection == GridPerlin)
		{
		}
		else{
			vector<Point> candUpdate;
			copy(Candidates.begin(), Candidates.begin()+cn, back_inserter(candUpdate));
			copy(Candidates.begin()+cn+1, Candidates.end(), back_inserter(candUpdate));
			Candidates = candUpdate;
		}
		numCands--;
	}
}


//This method selects numContinents number of continents, then passes of the initial seeds to growLandmass 
//to grow each one in a thread of it's own.
void GridMapGenerator::makeContinents(GridMap *map, int numContinents, float percentWater)
{
	vector<vector<Point> > Landmasses(numContinents, vector<Point>());
	Landmasses.push_back(vector<Point>());
	vector<vector<Point> > Candidates(numContinents, vector<Point>());
	Candidates.push_back(vector<Point>());
	int *numCands = new int[numContinents];
	int cx, cy;
	numUsed = 0;
	int mapSize = map->getSizeX() * map->getSizeY();
	landTiles = (int)round(mapSize * (1.0f - percentWater));
	int continentsMade = 0;
	for(int i = 0; i < numContinents; i++)numCands[i] = 0;
	while(numUsed < numContinents)
	{
		cx = rand()%map->getSizeX();
		cy = rand()%map->getSizeY();
		if(map->getGridPointAt(cx, cy).LandmassIndex == -1)
		{
			vector<Point> neighbors = getNeighbors(map, cx, cy);
			for(Point p : neighbors)
			{
				GridPoint g = map->getGridPointAt(p.x, p.y);
				if(g.LandmassIndex == -1)
				{
					g.LandmassIndex = continentsMade;
					map->updateGridPointAt(p.x, p.y, &g);
					Candidates[continentsMade].push_back(p);
					numCands[continentsMade]++;
				}
			}
			GridPoint update = map->getGridPointAt(cx, cy);
			update.LandmassIndex = continentsMade;
			update.water = false;
			map->updateGridPointAt(cx, cy, &update);
			Point newLand;
			newLand.x = cx;
			newLand.y = cy;
			vector<Point>::iterator position = std::find(Candidates[continentsMade].begin(), Candidates[continentsMade].end(), newLand);
			Landmasses[continentsMade].push_back(newLand);
			vector<Point> candUpdate;
			copy(Candidates[continentsMade].begin(), position, back_inserter(candUpdate));
			copy(position + 1, Candidates[continentsMade].end(), back_inserter(candUpdate));
			Candidates[continentsMade] = candUpdate;
			numUsed++;
			continentsMade++;
		}
		//end if continentsMade < numContinents

	}
	Perlin *p = new Perlin();
	thread *threads = new thread[numContinents];
	for(int i = 0; i < numContinents; i++)
	{
		threads[i] = thread(&GridMapGenerator::growLandmass, this, map, Landmasses[i], Candidates[i], numCands[i], p);
	}
	for(int i = 0; i < numContinents; i++)
	{
		threads[i].join();
	}
	delete[] numCands;
	delete[] threads;
}

/**
 * This function will return a completed Map structure. The program should
 * be blind to the exact implementation used to generate this map.
 */
Map * GridMapGenerator::generateMap(int mapX, int mapY, int numContinents, float percentWater)
{
	GridPoint *t = new GridPoint(); 
	t->x = 0;
	t->y = 0;
	t->height = 0.0f;
	t->ClimateIndex = 0;
	t->LandmassIndex = -1;
	t->water = true;
	t->TerrainIndex = 0;
	GridMap *m = new GridMap(mapX, mapY, t);
	delete t;
	srand(time(NULL));
	makeContinents(m, numContinents, percentWater);
	return m;
}

