#include "GridMap.h"
#include <stdbool.h>
#include <stdio.h>

using namespace WorldArchitect;
using namespace std;
//This function tells you if a point is water.
bool GridMap::isWaterAt(int x, int y)
{
	return getGridPointAt(x, y).water;
}

void GridMap::notifyAssignmentsDone()
{
	printf("%f , %f\n", heights.getMean(), heights.getStdDev());
}

int GridMap::getHeightAt(int x, int y)
{
	return (int)round(getGridPointAt(x, y).height);
}


///This function returns all the points which are neighbors to the 
///given coordinate (x, y) in the given GridMap.
///Note: This method does return the given point in the set of Points it returns.
vector<Point> GridMap::getNeighbors(int x, int y)
{
	vector<Point> ret;
	vector<int> xSet, ySet;
	if(x == 0)
	{
		xSet.push_back(0);
		xSet.push_back(1);
		xSet.push_back(getSizeX()-1);
	}
	else if(x == getSizeX()-1)
	{
		xSet.push_back(getSizeX()-2);
		xSet.push_back(getSizeX()-1);
		xSet.push_back(0);
	}
	else
	{
		xSet.push_back(x-1);
		xSet.push_back(x);
		xSet.push_back(x+1);
	}
	if(y == 0)
	{
		ySet.push_back(0);
		ySet.push_back(1);
		ySet.push_back(getSizeY()-1);
	}
	else if(x == getSizeY()-1)
	{
		ySet.push_back(getSizeY()-2);
		ySet.push_back(getSizeY()-1);
		ySet.push_back(0);
	}
	else
	{
		ySet.push_back(y-1);
		ySet.push_back(y);
		ySet.push_back(y+1);
	}

	for(int i : xSet)
	{
		for(int j : ySet)
		{
			Point p;
			p.x = i;
			p.y = j;
			ret.push_back(p);
		}
	}
	return ret;
}


int GridMap::distToWater(int x, int y)
{
	int dist = 0;
	return dist;
}

//Constructor for GridMap.
//Parameters:
// 	x : size in X direction
// 	y : size in Y direction
// 	initial : initial value of points.
GridMap::GridMap(int numX, int numY, GridPoint *initial)
	: heights()
{
	this->lock = new shared_mutex();
	this->x = numX;
	this->y = numY;
	initStorage(x, y, initial);
}

/// This function initializes the array. Holdover from old implementation
/// where storage was separate from the map. 
void GridMap::initStorage(int numX, int numY, GridPoint *initial)
{
	arr = new GridPoint*[x];
	for(int i = 0; i < x; i++)
	{
		arr[i] = new GridPoint[y];
	}
	for(int i = 0; i < x; i++)
	{
		for(int j = 0; j < y; j++)
		{
			arr[i][j].x = i;
			arr[i][j].y = j;
			arr[i][j].height = initial->height;
			arr[i][j].ClimateIndex = initial->ClimateIndex;
			arr[i][j].LandmassIndex = initial->LandmassIndex;
			arr[i][j].water = initial->water;
			arr[i][j].TerrainIndex = initial->TerrainIndex;
		}
	}
}


//This function returns a copy of the contents of the GridPoint located at (locX, locY)
GridPoint GridMap::getGridPointAt(int locX, int locY)
{
	lock->lock_shared();
	GridPoint ret;
	if(locX < 0 || locX > x || locY < 0 || locY > y)
	{
		ret.TerrainIndex = INVALID_POINT;
	}
	else
	{
		ret = arr[locX][locY];
	}
	lock->unlock_shared();
	return ret;
}


//This updates the contents of the internal storage for the GridPoint at (locX, locY)
//with the contents of change.
void GridMap::updateGridPointAt(int locX, int locY, GridPoint *change)
{	
	Logger *err = LogManager::getInstance()->getLogger(Error);
	lock->lock();
	if(locX < 0 || locX > x || locY < 0 || locY > y)
	{
		err->log("Invalid bounds to updateGridPointAt, coord : " + to_string(locX) + 
				", " + to_string(locY) + "\n");
	}
	else if(change == NULL)
	{
		err->log("Received a NULL pointer in updateGridPointAt\n");
		printf("Received a NULL pointer in updateGridPointAt\n");
	}
	else
	{
		if(arr[locX][locY].LandmassIndex > 0 && (arr[locX][locY].water == false))
		{
			err->log("Double write to point " +
			to_string(locX) + " " + to_string(locY) + 
			" was " + to_string(arr[locX][locY].LandmassIndex) +
			" changed to " + to_string(change->LandmassIndex) + "\n");
		}
		else
		{
			heights.addVal((double)change->height);
		}
		arr[locX][locY] = *change;
	}
	lock->unlock();
}

//Destructor for GridMap.
GridMap::~GridMap()
{
	lock->lock();
	for(int i = 0; i < x; i++)
	{
		delete[] arr[i];
	}
	lock->unlock();
	delete lock;
	delete[] arr;
}
