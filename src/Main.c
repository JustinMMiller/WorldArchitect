#include<stdlib.h>
#include<math.h>
#include "lib/qdbmp/qdbmp.h"
#include "TerrainGen/Generator.h"
#define P_WIDTH 512
#define P_HEIGHT 512
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
