#ifndef GRIDPOINT_H
#define GRIDPOINT_H
#define INVALID_POINT -5


namespace WorldArchitect
{
	/** 
	 * @struct GridPoint
	 * @brief This struct is how a GridMap stores its data for each point internally.
	 * @var GridPoint::x : x coordinate
	 * @var GridPoint::y : y coordinate
	 * @var GridPoint::height : Height of the location
	 * @var GridPoint::ClimateIndex : lookup for the climate of the location
	 * @var GridPoint::LandmassIndex : lookup for the Landmass the location is contained within.
	 * @var GridPoint::water : is the point water.
	 * @var GridPoint::TerrainIndex : lookup for what Terrain the point is categorized as.
	 */
	typedef struct _GridPoint
	{
		int x, y;
		float height;
		int LandmassIndex;
		bool water;
		int TerrainIndex;
		bool operator==(const _GridPoint& a) const
		{
			return (
					x == a.x &&
					y == a.y &&
					height == a.height &&
					LandmassIndex == a.LandmassIndex &&
					water == a.water &&
					TerrainIndex == a.TerrainIndex
			       );
		}
	} GridPoint;
}
#endif
