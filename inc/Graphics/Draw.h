#ifndef DRAW_H
#define DRAW_H
#include "MapGen/vector.h"
#include "lib/qdbmp/qdbmp.h"
#include <stdlib.h>
typedef struct _COLORMAP
{
	char R;
	char G;
	char B;
} ColorMap;
void drawPointsVector(Vector v, BMP *bmp);
#endif
