#include<stdlib.h>
#include<math.h>
#include "lib/qdbmp/qdbmp.h"
#include "Graphics/Draw.h"
#include "MapGen/GridMapGenerator.h"
#include "utils/Logging.h"
#define P_WIDTH 512
#define P_HEIGHT 512


//This is the main function. Currently used to manually render image of map generated
//with the MapGenerator selected. This functionality will be moved to Graphics later
//(probably).
int main()
{
	BMP *bmp;
	bmp = BMP_Create(P_WIDTH, P_HEIGHT, 24);
	if(BMP_GetError() != BMP_OK)
	{
		printf( "An error has occurred: %s (code %d)\n", BMP_GetErrorDescription(), BMP_GetError() );
	}

	MapGenerator *mapGen = getMapGenerator(GridPerlin);
	Map *m = mapGen->generateMap(P_WIDTH, P_HEIGHT, 20, 0.8f);
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
	BMP_WriteFile(bmp, "drawing.bmp");
	BMP_Free(bmp);
	delete m;
	return 0;
}
