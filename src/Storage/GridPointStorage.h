#ifndef GRIDPOINTSTORAGE_H
#define GRIDPOINTSTORAGE_H
#include "utils/GridPoint.h"
#include "utils/Logging.h"
#include<stdlib.h>
#include<stdio.h>
#include<shared_mutex>


/// \brief Used internally by GridMap to store its information, with GridMap being blind to its workings.
//
/// This is used by a GridMap to store its data, with the GridMap being blind to the 
/// internal workings. Currently uses a 2d array of GridPoints to store data.
namespace WorldArchitect
{
	class GridPointStorage
	{
		private:
			GridPoint **arr;
			std::shared_mutex *lock;
			int x, y;
		public:
			/// Constructs GridPointStorage with given parameters.
			GridPointStorage(int numX, int numY, GridPoint *initial);
			/// Default Deconstructor
			~GridPointStorage();
			/// Returns a copy of the GridPoint at the requested point if it exists
			GridPoint getGridPointAt(int locX, int locY);
			/// Updates the GridPoint at the given point with the given GridPoint's values
			void updateGridPointAt(int x, int y, GridPoint *change);
	};
}
#endif
