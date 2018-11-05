#ifndef GRIDPOINTSTORAGE_H
#define GRIDPOINTSTORAGE_H
using namespace std;
#include "utils/GridPoint.h"
#include "utils/Logging.h"
#include<stdlib.h>
#include<stdio.h>
#include<shared_mutex>

//This is used by a GridMap to store its data, with the GridMap being blind to the 
//internal workings. Currently uses a 2d array of GridPoints to store data.
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
