#ifndef MAPGENSYSTEM_H
#define MAPGENSYSTEM_H

#include <thread>

#include "MapGenerator.h"
#include "GridMapGenerator.h"
#include "Map.h"

namespace WorldArchitect
{
	class MapGenSystem
	{
		public:
			//This function returns a MapGenerator which uses the requested method.
			MapGenerator *getMapGenerator(Method method);
			void createMap(Method method);
			Map *getMap();
			~MapGenSystem();
		private:
			Map *map = NULL;
			void threadFunc(Method method);
			std::thread t;
	};
}

#endif
