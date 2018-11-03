#include "GridMapGenerator.h"

GridMapGenerator::GridMapGenerator(Method method) :lock() {}

vector<Point> GridMapGenerator::getNeighbors(GridMap *map, int x, int y)
{
	vector<Point> ret;
	int lx, ux, ly, uy;
	if(x == 0)
	{
		lx = 0;
		ux = 1;
	}
	else if(x == map->getSizeX()-1)
	{
		lx = map->getSizeX()-2;
		ux = map->getSizeX()-1;
	}
	else
	{
		lx = x-1;
		ux = x+1;
	}
	if(y == 0)
	{
		ly = 0;
		uy = 1;
	}
	else if(y == map->getSizeY()-1)
	{
		ly = map->getSizeY()-2;
		uy = map->getSizeY()-1;
	}
	else
	{
		ly = y-1;
		uy = y+1;
	}
	for(int i = lx; i <= ux; i++)
	{
		for(int j = ly; j <= uy; j++)
		{
			Point p;
			p.x = i;
			p.y = j;
			ret.push_back(p);
		}
	}
	return ret;
}

void GridMapGenerator::growLandmass(GridMap *map, vector<Point> Landmass, vector<Point> Candidates, int numCand)
{
	int numCands = numCand;
	bool canContinue = true;
	while(numUsed < landTiles && canContinue)
	{
		if(numCands == 0)
		{
			canContinue = false;
			break;
		}
		int cn = rand()%numCands;
		Point addPoint = Candidates[cn];
		GridPoint add = map->getGridPointAt(addPoint.x, addPoint.y);
		bool canAdd = true;
		vector<Point> neighbors = getNeighbors(map, add.x, add.y);
		for(Point p : neighbors)
		{
			GridPoint g = map->getGridPointAt(p.x, p.y);
			printf("add landmass %i : g landmass %i : point %i %i\n", add.LandmassIndex, g.LandmassIndex, p.x, p.y);
			if(g.LandmassIndex == -1)
			{
				g.LandmassIndex = add.LandmassIndex;
				map->updateGridPointAt(p.x, p.y, &g);
				Candidates.push_back(p);
				numCands++;
			}
			else if(g.LandmassIndex != add.LandmassIndex)
			{
				canAdd = false;
			}
		}
		if(canAdd)
		{
			add.water = false;
			vector<Point> candUpdate;
			map->updateGridPointAt(addPoint.x, addPoint.y, &add);
			copy(Candidates.begin(), Candidates.begin()+cn, back_inserter(candUpdate));
			copy(Candidates.begin()+cn+1, Candidates.end(), back_inserter(candUpdate));
			Landmass.push_back(addPoint);
			Candidates = candUpdate;
			numCands--;
			lock.lock();
			numUsed++;
			lock.unlock();
		}
	}
}

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
	thread *threads = new thread[numContinents];
	for(int i = 0; i < numContinents; i++)
	{
		threads[i] = thread(&GridMapGenerator::growLandmass, this, map, Landmasses[i], Candidates[i], numCands[i]);
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
	GridPoint *t = (GridPoint *)malloc(sizeof(GridPoint));
	t->x = 0;
	t->y = 0;
	t->height = 0.0f;
	t->ClimateIndex = 0;
	t->LandmassIndex = -1;
	t->water = true;
	t->TerrainIndex = 0;
	GridMap *m = new GridMap(mapX, mapY, t);
	free(t);
	srand(time(NULL));
	makeContinents(m, numContinents, percentWater);
	return m;
}

