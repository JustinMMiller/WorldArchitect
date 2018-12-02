#include "GridMap.h"
#include <stdbool.h>

using namespace WorldArchitect;
//This function tells you if a point is water.
bool GridMap::isWaterAt(int x, int y)
{
	return points.getGridPointAt(x, y).water;
}

//Constructor for GridMap.
//Parameters:
// 	x : size in X direction
// 	y : size in Y direction
// 	initial : initial value of points.
GridMap::GridMap(int x, int y, GridPoint *initial)
	: points(x, y, initial)
{
	this->x = x;
	this->y = y;
}

//Empty destructor.
GridMap::~GridMap()
{
}

//This gets the GridPoint at coordinate (x, y)
GridPoint GridMap::getGridPointAt(int x, int y)
{
	return points.getGridPointAt(x, y);
}

//This updates the GridPoint at (x, y) with the contents of update
void GridMap::updateGridPointAt(int x, int y, GridPoint *update)
{
	points.updateGridPointAt(x, y, update);
}
