#ifndef MAPGEN_H
#define MAPGEN_H
#include "Graphics/Draw.h"
#include <stdbool.h>

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
	GridPoint **points;

} Map;


/**
 * This function will return a completed Map structure. The program should
 * be blind to the exact implementation used to generate this map.
 */
Map *generateMap(int mapX, int mapY, int numContinents, float percentWater);

#endif
