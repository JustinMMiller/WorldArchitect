#ifndef GRIDMAP_H
#define GRIDMAP_H
#include "Map.h"
#include "utils/GridPoint.h"
#include "utils/Logging.h"
#include <stdlib.h>
#include <stdio.h>
#include <shared_mutex>
#include <string>
#include <vector>
#include "vector.h"


namespace WorldArchitect
{
	/// \class GridMap
	/// \brief This class extends Map.
	/// 
	/// This class extends Map. This is a Map for use with GridPoint generation (Generating terrain at a point by point level.)
	class GridMap : public Map
	{
		public :
			GridMap(int numX, int numY, GridPoint *initial);
			~GridMap();
			bool isWaterAt(int x, int y) override; 	//Inherited from Map superclass.
			int distToWater(int x, int y) override; 	//Inherited from Map superclass.
			GridPoint getGridPointAt(int locX, int locY);
			/// Updates the GridPoint at the given point with the given GridPoint's values
			void updateGridPointAt(int x, int y, GridPoint *change);
			std::vector<Point> getNeighbors(int x, int y);
		private:
			void initStorage(int numX, int numY, GridPoint *initial);
			GridPoint **arr;
			std::shared_mutex *lock;
	};

}
#endif
