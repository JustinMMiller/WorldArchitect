#include<stdlib.h>
#include<math.h>
#include "lib/qdbmp/qdbmp.h"
#include "Graphics/Draw.h"
#include "MapGen/MapGenerator.h"
#define P_WIDTH 512
#define P_HEIGHT 512
int main()
{
	BMP *bmp;
	Vector v;
	v.point.x = 40;
	v.point.y = 60;
	v.direction.x = 0;
	v.direction.y = 10;
	bmp = BMP_Create(P_WIDTH, P_HEIGHT, 24);
	if(BMP_GetError() != BMP_OK)
	{
		printf( "An error has occurred: %s (code %d)\n", BMP_GetErrorDescription(), BMP_GetError() );
	}
	Map *m = generateMap(512, 512, 10, 0.9f);
	for(int i = 0; i < m->x; i++)
	{
		for(int j = 0; j < m->y; j++)
		{
			if(m->points[i][j].water)
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
	return 0;
}
