#ifndef DRAW_H
#define DRAW_H
#include "MapGen/vector.h"
#include "lib/qdbmp/qdbmp.h"
#include <stdlib.h>

/// Struct to hold RGB values for use with QDBMP library. 
typedef struct 
{
	char R;
	char G;
	char B;
} ColorMap;

/**
 * drawPointsVector(Vector v, BMP *bmp)
 *
 * This function takes in a Vector (a Vector consists of an origin point and a direction vector (also a Point because math))
 * and renders it onto the given BMP.
 * This function currently does nothing. may be used later. Was from original tests with qdbmp library.
 */
void drawPointsVector(Vector v, BMP *bmp);
#endif
