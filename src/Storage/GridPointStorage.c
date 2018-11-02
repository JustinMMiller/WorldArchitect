#include "GridPointStorage.h"

GridPointStorage::GridPointStorage(int numX, int numY, GridPoint *initial)
	: x(abs(numX)),
	y(abs(numY))
{
	printf("%i %i\n", initial->x, initial->y);
	arr = new GridPoint*[numX];
	for(int i = 0; i < numY; i++)
	{
		arr[i] = new GridPoint[numY];
	}
	printf("arr : %p\n", arr);
	for(int i = 0; i < x; i++)
	{
		for(int j = 0; j < y; j++)
		{
			arr[i][j].x = initial->x;
			arr[i][j].y = initial->y;
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
	GridPoint ret;
	if(locX < 0 || locX > x || locY < 0 || locY > y)
	{
		ret.TerrainIndex = INVALID_POINT;
	}
	else
	{
		ret = arr[locX][locY];
	}
	return ret;
}

void GridPointStorage::updateGridPointAt(int locX, int locY, GridPoint *change)
{	
	if(locX < 0 || locX > x || locY < 0 || locY > y)
	{
		printf("Invalid bounds to updateGridPointAt, coord : %i, %i\n", locX, locY);
	}
	else if(change == NULL)
	{
		printf("Received a NULL pointer in updateGridPointAt\n");
	}
	else
	{
		arr[locX][locY] = *change;
	}
}

GridPointStorage::~GridPointStorage()
{
	for(int i = 0; i < x; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;
}
