#ifndef MAPGENSYSTEM_H
#define MAPGENSYSTEM_H

#include <thread>
#include <mutex>

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
			static MapGenSystem *getInstance();
		private:
			std::mutex m;
			MapGenSystem();
			Map *map = NULL;
			void threadFunc(Method method);
			std::thread t;
			static MapGenSystem *instance;
	};
}

#endif
