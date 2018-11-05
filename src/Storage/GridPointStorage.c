#include "GridPointStorage.h"

GridPointStorage::GridPointStorage(int numX, int numY, GridPoint *initial)
{
	this->lock = new shared_mutex();
	this->x = abs(numX);
	this->y = abs(numY);
	printf("%i %i\n", initial->x, initial->y);
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

GridPoint GridPointStorage::getGridPointAt(int locX, int locY)
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

void GridPointStorage::updateGridPointAt(int locX, int locY, GridPoint *change)
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
		if(arr[locX][locY].LandmassIndex > 0)
		{
			err->log("Double write to point " +
			to_string(locX) + " " + to_string(locY) + 
			" was " + to_string(arr[locX][locY].LandmassIndex) +
			" changed to " + to_string(change->LandmassIndex) + "\n");
		}
		arr[locX][locY] = *change;
	}
	lock->unlock();
}

GridPointStorage::~GridPointStorage()
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
