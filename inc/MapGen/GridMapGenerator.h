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
using namespace std;

class GridMapGenerator : public MapGenerator
{
	private:
		int numUsed;
		int landTiles;
		Method selection = GridRandom;
		shared_mutex lock;
		vector<Point> getNeighbors(GridMap *map, int x, int y);
		void makeContinents(GridMap *map, int numContinents, float percentWater);
		void growLandmass(GridMap *map, vector<Point> Landmass, vector<Point> Candidates, int numCands);
	public:
		GridMapGenerator(Method method);
		Map * generateMap(int mapX, int mapY, int numContinents, float percentWater);
};
#endif
