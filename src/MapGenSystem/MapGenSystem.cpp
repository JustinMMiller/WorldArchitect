#include "MapGenSystem.h"

using namespace WorldArchitect;

MapGenSystem * MapGenSystem::instance = NULL;

/**
 * getMapGenerator
 * This method returns an instance of a MapGenerator 
 * depending on the Method it is passed.
 */
MapGenerator * MapGenSystem::getMapGenerator(Method method)
{
	MapGenerator *generator;
	switch(method)
	{
		case GridRandom:
			generator = new GridMapGenerator(GridRandom);
			break;
		case GridPerlin:
			generator = new GridMapGenerator(GridPerlin);
			break;
		default:
			generator = new GridMapGenerator(GridPerlin);
	}
	return generator;
}

void MapGenSystem::createMap(Method method)
{
	this->t = std::thread(&MapGenSystem::threadFunc, this, method);
}

MapGenSystem::MapGenSystem()
{
}

MapGenSystem * MapGenSystem::getInstance()
{
	if(MapGenSystem::instance == NULL)
	{
		MapGenSystem::instance = new MapGenSystem();
	}
	return MapGenSystem::instance;
}

Map * MapGenSystem::getMap()
{
	if(this->map == NULL)
	{
		this->createMap(GridPerlin);
	}
	if(this->t.joinable())
	{
		this->t.join();
	}
	return this->map;
}

void MapGenSystem::threadFunc(Method method)
{
	// This needs to be changed to get parameters properly. I don't feel
	// like doing that right this second. $$TODO
	this->map = this->getMapGenerator(method)->generateMap(128, 128, 20, 0.9);
}

MapGenSystem::~MapGenSystem()
{
	if(this->t.joinable())
	{
		this->t.join();
	}
}
