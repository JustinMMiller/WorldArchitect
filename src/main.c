#include<stdlib.h>
#include<math.h>
#include<string>
#include "lib/qdbmp/qdbmp.h"
#include "MapGen/GridMapGenerator.h"
#include "utils/Logging.h"

using namespace std;

char *getCmdOption(char **begin, char **end, const string & option)
{
	char **itr = find(begin, end, option);
	if(itr != end && ++itr != end)
	{
		return *itr;
	}
	return 0;
}

bool cmdOptionExists(char **begin, char **end, const string & option)
{
	return find(begin, end, option) != end;
}

void printOpts()
{
	printf("Available command line parameters:\n");
	printf("-f <filename> to indicate what name to give the resulting map image\n");
	printf("-w <percent> to indicate percent of map which is water (values from 0.0-1.0\n");
	printf("-l <number> to indicate number of landmasses to generate\n");
	printf("-s <number> to indicate size of map (currently supports square maps)\n");
	printf("-g <method> to choose generation method (ie GridPerlin, GridRandom)\n");
}

/** 
 * This is the main function. Currently used to manually render image of map generated
 * with the MapGenerator selected. This functionality will be moved to Graphics later
 * (probably).
 */
int main(int argc, char *argv[])
{
	int p_width = 512, p_height = 512;
	int numLandmasses = 20;
	float percentWater = 0.9;
	Method gen = GridPerlin;
	string fname("drawing.bmp");
	if(argc < 2)
	{
		printf("Note: this program can be run with the following parameters");
		printOpts();
	}
	else
	{
		if(cmdOptionExists(argv, argv+argc, "-f"))
		{
			fname = string(getCmdOption(argv, argv+argc, "-f"));
		}
		if(cmdOptionExists(argv, argv+argc, "-w"))
		{
			percentWater = atof(getCmdOption(argv, argv+argc, "-f"));
		}
		if(cmdOptionExists(argv, argv+argc, "-l"))
		{
			numLandmasses = atoi(getCmdOption(argv, argv+argc, "-l"));
		}
		if(cmdOptionExists(argv, argv+argc, "-s"))
		{
			p_width = atoi(getCmdOption(argv, argv+argc, "-s"));
			p_height = p_width;
		}
		if(cmdOptionExists(argv, argv+argc, "-g"))
		{
			string res = getCmdOption(argv, argv+argc, "-g");
			if(res == "GridPerlin")gen = GridPerlin;
			else if(res == "GridRandom")gen = GridRandom;
		}
	}
	BMP *bmp;
	bmp = BMP_Create(p_width, p_height, 24);
	if(BMP_GetError() != BMP_OK)
	{
		printf( "An error has occurred: %s (code %d)\n", BMP_GetErrorDescription(), BMP_GetError() );
	}

	MapGenerator *mapGen = getMapGenerator(gen);
	Map *m = mapGen->generateMap(p_width, p_height, numLandmasses, percentWater);
	for(int i = 0; i < m->getSizeX(); i++)
	{
		for(int j = 0; j < m->getSizeY(); j++)
		{
			if(m->isWaterAt(i, j))
			{
				BMP_SetPixelRGB(bmp, i, j, 0, 0, 200);
			}
			else
			{
				BMP_SetPixelRGB(bmp, i, j, 0, 200, 0);
			}
		}
	}
	//drawPointsVector(v, bmp);
	BMP_WriteFile(bmp, fname.c_str());
	BMP_Free(bmp);
	delete m;
	return 0;
}
