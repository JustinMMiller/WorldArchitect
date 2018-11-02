#include "GridMap.h"
#include <stdbool.h>

bool GridMap::isWaterAt(int x, int y)
{
	return points.getGridPointAt(x, y).water;
}

GridMap::GridMap(int x, int y, GridPoint *initial)
	: points(x, y, initial)
{
	this->x = x;
	this->y = y;
}
