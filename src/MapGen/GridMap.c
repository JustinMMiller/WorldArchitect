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

GridMap::~GridMap()
{
}

GridPoint GridMap::getGridPointAt(int x, int y)
{
	return points.getGridPointAt(x, y);
}

void GridMap::updateGridPointAt(int x, int y, GridPoint *update)
{
	points.updateGridPointAt(x, y, update);
}
