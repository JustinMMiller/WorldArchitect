#ifndef MAPGEN_H
#define MAPGEN_H
using namespace std;
#include<vector>
#include <stdbool.h>
#include<stdlib.h>

typedef struct _GRIDPOINT
{
	int x, y;
	float height;
	int ClimateIndex;
	int LandmassIndex;
	bool water;
	int TerrainIndex;
} GridPoint;
typedef struct _MAP
{
	int x, y;
	vector<vector<GridPoint> > points;

} Map;


/**
 * This function will return a completed Map structure. The program should
 * be blind to the exact implementation used to generate this map.
 */
Map *generateMap(int mapX, int mapY, int numContinents, float percentWater);

#endif
