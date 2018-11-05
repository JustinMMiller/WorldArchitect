#ifndef GRIDPOINT_H
#define GRIDPOINT_H
#define INVALID_POINT -5

// This struct is how a GridMap stores its data for each point internally.
// Contents:
// 	x : x coordinate
// 	y : y coordinate
// 	height : Height of the location
// 	ClimateIndex : lookup for the climate of the location
// 	LandmassIndex : lookup for the Landmass the location is contained within.
// 	water : is the point water.
// 	TerrainIndex : lookup for what Terrain the point is categorized as.
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
