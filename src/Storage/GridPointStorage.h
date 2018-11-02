#ifndef GRIDPOINTSTORAGE_H
#define GRIDPOINTSTORAGE_H
#include "utils/GridPoint.h"
#include<stdlib.h>
#include<stdio.h>

class GridPointStorage
{
	private:
		GridPoint **arr;
		int x, y;
	public:
		GridPointStorage(int numX, int numY, GridPoint *initial);
		~GridPointStorage();
		GridPoint getGridPointAt(int locX, int locY);
		void updateGridPointAt(int x, int y, GridPoint *change);
};
#endif
