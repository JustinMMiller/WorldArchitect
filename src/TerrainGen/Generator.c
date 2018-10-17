#include "TerrainGen/Generator.h"
void drawPointsVector(Vector v, BMP *bmp)
{
	float x, y, z, dx, dy, len;
	len = hypotf(v.direction.x, v.direction.y);
	dx = v.direction.x / len;
	dy = v.direction.y / len;
	x = v.point.x;
	y = v.point.y;
	for(z = 0; z <= len; z++)
	{
		BMP_SetPixelRGB(bmp, floorf(x), y, 255, 255, 255);
		if(BMP_GetError() != BMP_OK)
		{
			printf( "An error has occurred: %s (code %d)\n", BMP_GetErrorDescription(), BMP_GetError() );
		}
		BMP_SetPixelRGB(bmp, ceilf(x), y, 255, 255, 255);
		if(BMP_GetError() != BMP_OK)
		{
			printf( "An error has occurred: %s (code %d)\n", BMP_GetErrorDescription(), BMP_GetError() );
		}
		BMP_SetPixelRGB(bmp, x, floorf(y), 255, 255, 255);
		if(BMP_GetError() != BMP_OK)
		{
			printf( "An error has occurred: %s (code %d)\n", BMP_GetErrorDescription(), BMP_GetError() );
		}
		BMP_SetPixelRGB(bmp, x, ceilf(y), 255, 255, 255);
		if(BMP_GetError() != BMP_OK)
		{
			printf( "An error has occurred: %s (code %d)\n", BMP_GetErrorDescription(), BMP_GetError() );
		}
		x += dx;
		y += dy;
	}
}


