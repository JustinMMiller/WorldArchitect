#ifndef MAPGEN_H
#define MAPGEN_H
using namespace std;
#include<vector>
#include<stdbool.h>
#include<stdlib.h>
#include "Map.h"



//The possible methods for generating a Map.
// GridRandom : Randomly select points from Grid, and add connected points to grow landmasses
// GridPerlin : Randomly select points from Grid, then grow landmasses in accordance to Perlin noise map.
enum Method
{
	GridRandom, 
	GridPerlin
};


//virtual class to represent a Map Generator. Extended with other methods.
class MapGenerator
{
	public:
		/**
		 * This function will return a completed Map object. The program should
		 * be blind to the exact implementation used to generate this map.
		 */
		virtual Map *generateMap(int mapX, int mapY, int numContinents, float percentWater) = 0;
};


//This function returns a MapGenerator which uses the requested method.
MapGenerator *getMapGenerator(Method method);

#endif
