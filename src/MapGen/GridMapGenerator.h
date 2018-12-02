#ifndef GRIDMAPGENERATOR_H
#define GRIDMAPGENERATOR_H

#include<algorithm>
#include<vector>
#include<cmath>
#include<stdio.h>
#include<shared_mutex>
#include<thread>
#include<queue>
#include<random>
#include "vector.h"
#include "MapGenerator.h"
#include "GridMap.h"
#include "utils/Perlin.h"

namespace WorldArchitect
{
	/// \class GridMapGenerator
	/// 
	/// \brief This class extends MapGenerator.
	/// 
	/// This class uses GridPoints as the basis for how it grows landmasses and
	/// interprets the world. It uses a thread per landmass to grow it concurrently.
	///
	/// This Generator is associated with two Methods, GridRandom and GridPerlin.
	class GridMapGenerator : public MapGenerator
	{
		private:
			int numUsed;
			int landTiles;
			Method selection = GridRandom;
			std::shared_mutex lock;
			std::vector<Point> getNeighbors(GridMap *map, int x, int y);
			void makeContinents(GridMap *map, int numContinents, float percentWater);
			void growLandmass(GridMap *map, std::vector<Point> Landmass, std::vector<Point> Candidates, int numCands, Perlin *perlin);
		public:
			GridMapGenerator(Method method);
			Map * generateMap(int mapX, int mapY, int numContinents, float percentWater);
	};
}
#endif
