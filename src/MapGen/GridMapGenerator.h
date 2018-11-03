#ifndef GRIDMAPGENERATOR_H
#define GRIDMAPGENERATOR_H

#include<algorithm>
#include<vector>
#include<cmath>
#include<stdio.h>
#include<mutex>
#include "vector.h"
#include "MapGenerator.h"
#include "GridMap.h"
using namespace std;

class GridMapGenerator : public MapGenerator
{
	private:
		int landTiles;
		mutex lock;
		vector<Point> getNeighbors(GridMap *map, int x, int y);
		void makeContinents(GridMap *map, int numContinents, float percentWater);
	public:
		Map * generateMap(int mapX, int mapY, int numContinents, float percentWater);
};
#endif
