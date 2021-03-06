#ifndef MAPGEN_H
#define MAPGEN_H
#include<vector>
#include<stdbool.h>
#include<stdlib.h>
#include "Map.h"


namespace WorldArchitect
{
	//The possible methods for generating a Map.
	// GridRandom : Randomly select points from Grid, and add connected points to grow landmasses
	// GridPerlin : Randomly select points from Grid, then grow landmasses in accordance to Perlin noise map.
	enum Method
	{
		GridRandom, 
		GridPerlin
	};


	/// \class MapGenerator
	/// \brief Virtual class to represent a Map Generator. Extended with other methods.
	class MapGenerator
	{
		public:
			/**
			 * This function will return a completed Map object. The program should
			 * be blind to the exact implementation used to generate this map.
			 */
			virtual Map *generateMap(int mapX, int mapY, int numContinents, float percentWater) = 0;
	};


}
#endif
