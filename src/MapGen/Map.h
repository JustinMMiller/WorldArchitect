#ifndef MAP_H
#define MAP_H

/// \class Map
/// \brief This is a virtual class for extension for different Map Generation methods. 
namespace WorldArchitect
{
	class Map{
		protected:
			int x, y;
		public:
			virtual bool isWaterAt(int x, int y) = 0;
			virtual int distToWater(int x, int y) = 0;
			int getSizeX(){return x;}
			int getSizeY(){return y;}
			virtual ~Map() = 0;
	};
}
#endif
