#ifndef GRIDMAP_H
#define GRIDMAP_H
#include "Map.h"
#include "Storage/GridPointStorage.h"


namespace WorldArchitect
{
	/// \class GridMap
	/// \brief This class extends Map.
	/// 
	/// This class extends Map. This is a Map for use with GridPoint generation (Generating terrain at a point by point level.)
	class GridMap : public Map
	{
		public :
			GridMap(int x, int y, GridPoint *initial);
			~GridMap();
			GridPoint getGridPointAt(int x, int y);
			void updateGridPointAt(int x, int y, GridPoint *update);
			bool isWaterAt(int x, int y); 	//Inherited from Map superclass.
			int distToWater(int x, int y); 	//Inherited from Map superclass.
		private:
			GridPointStorage points;
	};
}
#endif
