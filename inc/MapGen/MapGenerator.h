#ifndef MAPGEN_H
#define MAPGEN_H
using namespace std;
#include<vector>
#include<stdbool.h>
#include<stdlib.h>
#include "Map.h"


/**
 * This function will return a completed Map object. The program should
 * be blind to the exact implementation used to generate this map.
 */
class MapGenerator
{
	public:
		virtual Map *generateMap(int mapX, int mapY, int numContinents, float percentWater) = 0;
};

#endif
