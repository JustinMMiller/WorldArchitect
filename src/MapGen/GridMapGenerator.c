#include "GridMapGenerator.h"

vector<Point> GridMapGenerator::getNeighbors(GridMap *map, int x, int y)
{
	printf("%i, %i\n", x, y);
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
	printf("bounds : %i, %i,   %i, %i\n", lx, ux, ly, uy);
	for(int i = lx; i <= ux; i++)
	{
		for(int j = ly; j <= uy; j++)
		{
			if(map->points.getGridPointAt(i, j).LandmassIndex == -1)
			{
				Point p;
				p.x = i;
				p.y = j;
				ret.push_back(p);
			}
		}
	}
	return ret;
}

void GridMapGenerator::makeContinents(GridMap *map, int numContinents, float percentWater)
{
	vector<vector<Point> > Landmasses(numContinents, vector<Point>());
	Landmasses.push_back(vector<Point>());
	vector<vector<Point> > Candidates(numContinents, vector<Point>());
	Candidates.push_back(vector<Point>());
	int *numCands = new int[numContinents];
	int cx, cy;
	int numUsed = 0;
	int mapSize = map->getSizeX() * map->getSizeY();
	int landTiles = (int)round(mapSize * (1.0f - percentWater));
	int continentsMade = 0;
	bool canContinue = true;
	for(int i = 0; i < numContinents; i++)numCands[i] = 0;
	while(numUsed < landTiles && canContinue)
	{
		if(continentsMade < numContinents)
		{
			cx = rand()%map->getSizeX();
			cy = rand()%map->getSizeY();
			if(map->points.getGridPointAt(cx, cy).LandmassIndex == -1)
			{
				vector<Point> neighbors = getNeighbors(map, cx, cy);
				for(Point p : neighbors)
				{
					GridPoint g = map->points.getGridPointAt(p.x, p.y);
					if(g.LandmassIndex == -1)
					{
						g.LandmassIndex = continentsMade;
						Candidates[continentsMade].push_back(p);
						numCands[continentsMade]++;
					}
				}
				GridPoint update = map->points.getGridPointAt(cx, cy);
				update.LandmassIndex = continentsMade;
				update.water = false;
				map->points.updateGridPointAt(cx, cy, &update);
				Point newLand;
				newLand.x = cx;
				newLand.y = cy;
				Landmasses[continentsMade].push_back(newLand);
				vector<Point> candUpdate;
				copy(Candidates[continentsMade].begin(), Candidates[continentsMade].begin()+4, back_inserter(candUpdate));
				copy(Candidates[continentsMade].begin()+5, Candidates[continentsMade].end(), back_inserter(candUpdate));
				Candidates[continentsMade] = candUpdate;
				numUsed++;
				continentsMade++;
			}
		}//end if continentsMade < numContinents
		else
		{
			printf("%i, %i, %i\n", numUsed, landTiles, numContinents);
			int c = rand()%numContinents;
			if(numCands[c] == 0)
			{
				canContinue = false;
				for(int i = 0; i < numContinents; i++)
				{
					if(numCands[i] > 0)c = i;
				}
				if(numCands[c] > 0)canContinue = true;
				else
				{
					printf("Couldn't find any candidates\n");
					break;
				}
			}
			int cn = rand()%numCands[c];
			Point addPoint = Candidates[c][cn];
			GridPoint add = map->points.getGridPointAt(addPoint.x, addPoint.y);
			vector<Point> neighbors = getNeighbors(map, add.x, add.y);
			for(Point p : neighbors)
			{
				GridPoint g = map->points.getGridPointAt(p.x, p.y);
				if(g.LandmassIndex == -1)
				{
					g.LandmassIndex = add.LandmassIndex;
					Candidates[c].push_back(p);
					map->points.updateGridPointAt(p.x, p.y, &g);
					numCands[c]++;
				}
			}
			add.water = false;
			Landmasses[c].push_back(addPoint);
			map->points.updateGridPointAt(addPoint.x, addPoint.y, &add);
			vector<Point> candUpdate;
			copy(Candidates[c].begin(), Candidates[c].begin()+cn, back_inserter(candUpdate));
			copy(Candidates[c].begin()+cn+1, Candidates[c].end(), back_inserter(candUpdate));
			Candidates[c] = candUpdate;
			numUsed++;
			numCands[c]--;
		}//end else of if continentsMade < numContinents
	}
	delete[] numCands;
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
	for(int i = 0; i < mapX; i++)
	{
		for(int j = 0; j < mapY; j++)
		{
			t->x = i;
			t->y = j;
			m->points.updateGridPointAt(i, j, t);
		}
	}
	makeContinents(m, numContinents, percentWater);
	return m;
}

