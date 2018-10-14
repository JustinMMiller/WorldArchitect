#include<stdlib.h>
#include<math.h>
#include "./qdbmp.h"
#include "./vector.h"
#define P_WIDTH 100
#define P_HEIGHT 100

void drawPointsVector(Vector v, BMP *bmp)
{
	int i, y;
	float m, b;
	m = v.direction.y / v.direction.x;
	b = -m*v.point.x + v.point.y;
	for(int i = v.point.x; i < (v.point.x + v.direction.x); i++)
	{
		y = (int)(lroundf(m*i + b));
		printf("Setting %i, %i\n", i, y);
		BMP_SetPixelRGB(bmp, i, y, 255, 255, 255);
		if(BMP_GetError() != BMP_OK)
		{
			printf( "An error has occurred: %s (code %d)\n", BMP_GetErrorDescription(), BMP_GetError() );
		}
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
	v.direction.x = 20;
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
