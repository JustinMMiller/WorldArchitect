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
			/** 
			 * The following two commented functions will be 
			 * added later. Intended functionality is 
			 * Map subclasses should be serializable to and from strings.
			 * This is to enable saving and reloading Maps. 
			 */
			//virtual std::string exportString() = 0;
			//virtual void loadFromString(std::string save) = 0;
			virtual bool isWaterAt(int x, int y) = 0;
			virtual int distToWater(int x, int y) = 0;
			virtual int getHeightAt(int x, int y) = 0;
			virtual void populate() = 0;
			virtual ~Map() = 0;
			int getSizeX(){return x;}
			int getSizeY(){return y;}
	};
}
#endif
