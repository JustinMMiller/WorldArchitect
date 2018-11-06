#ifndef GRIDPOINT_H
#define GRIDPOINT_H
#define INVALID_POINT -5

/** This struct is how a GridMap stores its data for each point internally.
 * @struct GridPoint
 * @var GridPoint::x : x coordinate
 * @var GridPoint::y : y coordinate
 * @var GridPoint::height : Height of the location
 * @var GridPoint::ClimateIndex : lookup for the climate of the location
 * @var GridPoint::LandmassIndex : lookup for the Landmass the location is contained within.
 * @var GridPoint::water : is the point water.
 * @var GridPoint::TerrainIndex : lookup for what Terrain the point is categorized as.
 */
typedef struct 
{
	int x, y;
	float height;
	int ClimateIndex;
	int LandmassIndex;
	bool water;
	int TerrainIndex;
} GridPoint;
#endif
