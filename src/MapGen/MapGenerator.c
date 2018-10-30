#include "MapGenerator.h"
#include<vector>
#include<cmath>
#include<stdio.h>

using namespace std;
/**
 * Commenting out to refactor, potentially remove.
vector<GridPoint> getNeighbors(vector<vector<GridPoint> > points, GridPoint p, int mX, int mY)
{
	printf("Passed in point %i, %i\n", p.x, p.y);
	vector<GridPoint> ret;
	int lx, ux, ly, uy;
	if(p.x == 0)
	{
		lx = 0;
		ux = 1;
	}
	else if(p.x == mX-1)
	{
		lx = points.size()-2;
		ux = points.size()-1;
	}
	else
	{
		lx = p.x-1;
		ux = p.x+1;
	}
	if(p.y == 0)
	{
		ly = 0;
		uy = 1;
	}
	else if(p.y == mY-1)
	{
		ly = points.size()-2;
		uy = points.size()-1;
	}
	else
	{
		ly = p.y-1;
		uy = p.y+1;
	}
	printf("bounds : %i, %i,   %i, %i\n", lx, ux, ly, uy);
	for(int i = lx; i <= ux; i++)
	{
		for(int j = ly; j <= uy; j++)
		{
			if(points[i][j].LandmassIndex != -2)
			{
				ret.push_back(points[i][j]);
			}
		}
	}
	return ret;
}

void makeContinents(Map *map, int numContinents, float percentWater)
{
	vector<vector<GridPoint> > AllPoints (map->x, vector<GridPoint>(map->y));
	vector<vector<GridPoint> > Landmasses (map->x, vector<GridPoint>(map->y));
	vector<vector<GridPoint> > Candidates (map->x, vector<GridPoint>(map->y));
	int *numCands = new int[numContinents];
	for(int i = 0; i < map->x; i++)
	{
		for(int j = 0; j < map->y; j++)
		{
			AllPoints[i][j] = map->points[i][j];
		}
	}
	int cx, cy;
	int numUsed = 0;
	int mapSize = map->x * map->y;
	int landTiles = (int)round(mapSize * (1.0f - percentWater));
	int continentsMade = 0;
	bool canContinue = true;
	while(numUsed < landTiles)
	{
		if(continentsMade < numContinents)
		{
			printf("%i, %i, %i\n", numUsed, landTiles, numContinents);
			vector<GridPoint> v(1);
			vector<GridPoint> vc(4);
			cx = rand()%map->x;
			cy = rand()%map->y;
			if(AllPoints[cx][cy].LandmassIndex == -1)
			{
				printf("Found potential candidate at %i, %i\n", cx, cy);
				vc = getNeighbors(AllPoints, AllPoints[cx][cy], map->x, map->y);
				if(vc.size() < 4)
				{
					continue;
				}
				else
				{
					AllPoints[cx][cy].LandmassIndex = continentsMade;
					vector<GridPoint> t;
					for(int r = 0; r < vc.size(); r++)
					{
						GridPoint g = vc[r];
						bool clear = true;
						t = getNeighbors(AllPoints, g, map->x, map->y);
						for(GridPoint gp : t)
						{
							if(gp.LandmassIndex != -1 && gp.LandmassIndex != continentsMade)
							{
								clear = false;
							}
						}
						if(clear)
						{
							for(GridPoint gp : t)AllPoints[gp.x][gp.y].LandmassIndex = continentsMade;
							g.LandmassIndex = continentsMade;
							Candidates[continentsMade].push_back(g);
							numCands[continentsMade]++;
							AllPoints[g.x][g.y].LandmassIndex = -2;
						}
					}// end for r 0...vc.size()
					AllPoints[cx][cy].LandmassIndex = continentsMade;
					AllPoints[cx][cy].water = false;
					v.push_back(AllPoints[cx][cy]);
					numUsed++;
					Landmasses.push_back(v);
					continentsMade++;
					AllPoints[cx][cy].LandmassIndex = -2;
				}//end else of if vc.size < 4
			} // end if AllPoints[cx][cy] is acceptable
		}//End if Landmasses.size < numContinents
		else
		{
			printf("Working on expanding continents\n");
			if(Candidates.size() == 0)
			{
				canContinue = false;
			}
			else
			{
				int c = rand()%numContinents;
				printf("%i : numCands %i\n", c, numCands[c]);
				if(numCands[c] == 0)
				{
					canContinue = false;
					int numNonEmpty = 0;
					vector<int> nonEmpty;
					for(int i = 0; i < numContinents; i++)
					{
						if(numCands[i] > 0)
						{
							nonEmpty.push_back(i);
							numNonEmpty++;
							canContinue = true;
						}
					}
					if(numNonEmpty > 0)
					{
						c = nonEmpty[rand() % numNonEmpty];
					}
				}
				else
				{
					int coord = rand() % numCands[c];
					GridPoint g = Candidates[c][coord];
					printf("g : %i, %i\n", g.x, g.y);
					vector<GridPoint> t, newcands;
					newcands = getNeighbors(AllPoints, g, map->x, map->y);
					for(GridPoint gt : newcands)
					{
						t = getNeighbors(AllPoints, gt, map->x, map->y);
						bool clear = true;
						for(GridPoint neighbor : t)
						{
							if(neighbor.LandmassIndex != -1)
							{
								clear = false;
							}
						}
						if(clear)
						{
							gt.LandmassIndex = g.LandmassIndex;
							Candidates[c].push_back(gt);
							numCands[c]++;
							AllPoints[gt.x][gt.y].LandmassIndex = -2;
						}
					}
					g.water = false;
					Landmasses[c].push_back(g);
					Candidates[c].erase(Candidates[c].begin() + coord);
					numCands[c]--;
					numUsed++;
				}

			}
		}//end else landmasses == numContinents
	}//end while numUsed < landTiles
	for(vector<GridPoint> landmass : Landmasses)
	{
		for(GridPoint g : landmass)
		{
			map->points[g.x][g.y] = g;
		}
	}
}
*/








vector<GridPoint *> getNeighbors(Map *map, int x, int y)
{
	printf("%i, %i\n", x, y);
	vector<GridPoint *> ret;
	int lx, ux, ly, uy;
	if(x == 0)
	{
		lx = 0;
		ux = 1;
	}
	else if(x == map->x-1)
	{
		lx = map->x-2;
		ux = map->x-1;
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
	else if(y == map->y-1)
	{
		ly = map->y-2;
		uy = map->y-1;
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
			if(map->points[i][j].LandmassIndex == -1)
			{
				ret.push_back(&map->points[i][j]);
			}
		}
	}
	return ret;
}

void makeContinents(Map *map, int numContinents, float percentWater)
{
	vector<vector<GridPoint *> > Landmasses(numContinents, vector<GridPoint *>());
	Landmasses.push_back(vector<GridPoint *>());
	vector<vector<GridPoint *> > Candidates(numContinents, vector<GridPoint *>());
	Candidates.push_back(vector<GridPoint *>());
	int *numCands = new int[numContinents];
	int cx, cy;
	int numUsed = 0;
	int mapSize = map->x * map->y;
	int landTiles = (int)round(mapSize * (1.0f - percentWater));
	int continentsMade = 0;
	bool canContinue = true;
	for(int i = 0; i < numContinents; i++)numCands[i] = 0;
	while(numUsed < landTiles && canContinue)
	{
		if(continentsMade < numContinents)
		{
			cx = rand()%map->x;
			cy = rand()%map->y;
			if(map->points[cx][cy].LandmassIndex == -1)
			{
				vector<GridPoint *> neighbors = getNeighbors(map, cx, cy);
				for(GridPoint *g : neighbors)
				{
					if(g->LandmassIndex == -1)
					{
						g->LandmassIndex = continentsMade;
						Candidates[continentsMade].push_back(g);
						numCands[continentsMade]++;
					}
				}
				map->points[cx][cy].LandmassIndex = continentsMade;
				map->points[cx][cy].water = false;
				Landmasses[continentsMade].push_back(&map->points[cx][cy]);
				Candidates[continentsMade].erase(Candidates[continentsMade].begin()+4);
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
			GridPoint *add = Candidates[c][cn];
			vector<GridPoint *> neighbors = getNeighbors(map, add->x, add->y);
			for(GridPoint *g : neighbors)
			{
				if(g->LandmassIndex == -1)
				{
					g->LandmassIndex = add->LandmassIndex;
					Candidates[c].push_back(g);
					numCands[c]++;
				}
			}
			add->water = false;
			Landmasses[c].push_back(add);
			Candidates[c].erase(Candidates[c].begin()+cn-1);
			numUsed++;
			numCands[c]--;
		}//end else of if continentsMade < numContinents
	}
}

/**
 * This function will return a completed Map structure. The program should
 * be blind to the exact implementation used to generate this map.
 */
Map *generateMap(int mapX, int mapY, int numContinents, float percentWater)
{
	Map *m = (Map *)malloc(sizeof(Map));
	vector<vector<GridPoint> > mat  (mapX, vector<GridPoint>(mapY));
	m->x = mapX;
	m->y = mapY;
	m->points = mat;
	for(int i = 0; i < mapX; i++)
	{

		for(int j = 0; j < mapY; j++)
		{
			GridPoint t;
			t.x = i;
			t.y = j;
			t.height = 0.0f;
			t.ClimateIndex = 0;
			t.LandmassIndex = -1;
			t.water = true;
			t.TerrainIndex = 0;
			m->points[i][j] = t;
		}
	}
	makeContinents(m, numContinents, percentWater);
	return m;
}


