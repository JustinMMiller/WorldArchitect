#include<stdlib.h>
#include<math.h>
#include "lib/qdbmp/qdbmp.h"
#include "vector.h"
#define P_WIDTH 512
#define P_HEIGHT 512

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

int main()
{
	BMP *bmp;
	Vector v;
	int x, y;
	UCHAR r, g, b;
	v.point.x = 40;
	v.point.y = 60;
	v.direction.x = 0;
	v.direction.y = 10;
	bmp = BMP_Create(P_WIDTH, P_HEIGHT, 24);
	if(BMP_GetError() != BMP_OK)
	{
		printf( "An error has occurred: %s (code %d)\n", BMP_GetErrorDescription(), BMP_GetError() );
	}
	drawPointsVector(v, bmp);
	BMP_WriteFile(bmp, "drawing.bmp");
	BMP_Free(bmp);
	return 0;
}
