#ifndef GRIDPOINT_H
#define GRIDPOINT_H
#define INVALID_POINT -5
typedef struct _GRIDPOINT
{
	int x, y;
	float height;
	int ClimateIndex;
	int LandmassIndex;
	bool water;
	int TerrainIndex;
} GridPoint;
#endif
