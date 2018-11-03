#ifndef GRIDPOINTSTORAGE_H
#define GRIDPOINTSTORAGE_H
using namespace std;
#include "utils/GridPoint.h"
#include<stdlib.h>
#include<stdio.h>
#include<shared_mutex>

class GridPointStorage
{
	private:
		GridPoint **arr;
		shared_mutex *lock;
		int x, y;
	public:
		GridPointStorage(int numX, int numY, GridPoint *initial);
		~GridPointStorage();
		GridPoint getGridPointAt(int locX, int locY);
		void updateGridPointAt(int x, int y, GridPoint *change);
};
#endif
