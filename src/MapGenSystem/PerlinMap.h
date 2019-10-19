#ifndef PERLINMAP_H
#define PERLINMAP_H

#include "Map.h"

namespace WorldArchitect
{
	/// \class PerlinMap
	/// \brief A map generated purely from Perlin noise, 
	/// with minimal configuration.
	/// 
	/// This Map class requires minimal configuration. 
	class PerlinMap : public Map
	{
		public:
			bool isWaterAt(int x, int y) override;
			int distToWater(int x, int y) override;
			int getHeightAt(int x, int y) override;
			void populate() override;
		private:
			float cutoff;
			void calcCutoff();
	};
}
#endif
