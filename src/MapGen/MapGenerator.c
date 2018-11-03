#include "MapGenerator.h"
#include "GridMapGenerator.h"


/**
 * getMapGenerator
 * This method returns an instance of a MapGenerator 
 * depending on the Method it is passed.
 */
MapGenerator *getMapGenerator(Method method)
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
