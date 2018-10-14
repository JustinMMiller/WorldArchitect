#include<stdlib.h>
#include<math.h>
#include "qdbmp.h"
#include "vector.h"
#define P_WIDTH 256
#define P_HEIGHT 256

void drawPointsVector(Vector v, BMP *bmp)
{
	int i;
	float m, b;
//	m = v.direction.Vy / v.direction.Vx;
}

int main()
{
	BMP *bmp;
	Vector v;
	int x, y;
	UCHAR r, g, b;
	v.point.x = 40;
	v.point.y = 60;
	//v.direction.Vx = 20;
	//v.direction.Vy = 10;
	bmp = BMP_Create(P_WIDTH, P_HEIGHT, 8);
	BMP_WriteFile(bmp, "test.bmp");
	BMP_Free(bmp);
	return 0;
}
