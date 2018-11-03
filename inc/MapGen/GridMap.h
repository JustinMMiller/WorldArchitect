#ifndef GRIDMAP_H
#define GRIDMAP_H
#include "Map.h"
#include "Storage/GridPointStorage.h"
class GridMap : public Map
{
	public :
		GridMap(int x, int y, GridPoint *initial);
		~GridMap();
		GridPoint getGridPointAt(int x, int y);
		void updateGridPointAt(int x, int y, GridPoint *update);
		bool isWaterAt(int x, int y);
	private:
		GridPointStorage points;
};
#endif
