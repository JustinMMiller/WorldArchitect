#ifndef PERLIN_H
#define PERLIN_H
#include<cmath>
#include<vector>
#include<time.h>
#include<algorithm>
#include<random>


namespace WorldArchitect
{
	class Perlin
	{
		public:
			double noise(double x, double y);
			double noise(double x, double y, double z);
			double octaveNoise(double x, double y);
			double octaveNoise(double x, double y, int octaves);
			Perlin();
			Perlin(unsigned int seed, int fidelity);
			Perlin(unsigned int seed, int fidelity, double amp);
		private:
			std::vector<int> p;
			double fade(double t);
			double lerp(double t, double a, double b);
			double grad(int hash, double x, double y, double z);
			double amp;
			void initP(unsigned int seed);
			int fidelity;
	};
}
#endif
