#ifndef GRIDMAP_H
#define GRIDMAP_H
#include "Map.h"
#include "Storage/GridPointStorage.h"
class GridMap : public Map
{
	public :
		GridMap(int x, int y, GridPoint *initial);
		GridPointStorage points;
};
#endif
