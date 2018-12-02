#include "Perlin.h"

using namespace WorldArchitect;
Perlin::Perlin()
	: Perlin(time(NULL), 512)
{
}

Perlin::Perlin(unsigned int seed, int fidelity)
	: Perlin(seed, fidelity, 1)
{
}

Perlin::Perlin(unsigned int seed, int fidelity, double amp)
	: fidelity(fidelity), amp(amp)
{
	initP(seed);
}

void Perlin::initP(unsigned int seed)
{
	for(int i = 0; i < fidelity; i++)
	{
		p.push_back(i);
	}
	std::default_random_engine engine(seed);
	shuffle(p.begin(), p.end(), engine);
	// Duplicate the permutation vector
	p.insert(p.end(), p.begin(), p.end());
}

double Perlin::noise(double x, double y)
{
	noise(x, y, 0);
}

double Perlin::noise(double x, double y, double z)
{
	int X = (int) floor(x) % fidelity;
	int Y = (int) floor(y) % fidelity;
	int Z = (int) floor(z) % fidelity;
	x -= floor(x);
	y -= floor(y);
	z -= floor(z);
	double u = fade(x);
	double v = fade(y);
	double w = fade(z);
	int A = p[X]+Y;
	int AA = p[A]+Z;
	int AB = p[A+1]+Z;
	int B = p[X+1]+Y;
	int BA = p[B]+Z;
	int BB = p[B+1]+Z;
	return lerp(w, lerp(v, lerp(u, grad(p[AA  ], x  , y  , z   ),  // AND ADD
					grad(p[BA  ], x-1, y  , z   )), // BLENDED
				lerp(u, grad(p[AB  ], x  , y-1, z   ),  // RESULTS
					grad(p[BB  ], x-1, y-1, z   ))),// FROM  8
			lerp(v, lerp(u, grad(p[AA+1], x  , y  , z-1 ),  // CORNERS
					grad(p[BA+1], x-1, y  , z-1 )), // OF CUBE
				lerp(u, grad(p[AB+1], x  , y-1, z-1 ),
					grad(p[BB+1], x-1, y-1, z-1 ))));
}

double Perlin::octaveNoise(double x, double y)
{
	octaveNoise(x, y, 8);
}

double Perlin::octaveNoise(double x, double y, int octaves)
{
	double ret = 0;
	double freq = 1;
	double maxValue = 0;
	double amplitude = amp;
	for(int i = 0; i < octaves; i++)
	{
		ret += noise(x * freq, y * freq) * amplitude;
		maxValue += amplitude;
		amplitude *= 0.5;
		freq *= 2;
	}
	return ret/maxValue;
}

double Perlin::fade(double t)
{
	return t * t * t * (t * (t * 6 - 15) + 10);
}

double Perlin::lerp(double t, double a, double b)
{
	return a + t * (b - a);
}

double Perlin::grad(int hash, double x, double y, double z)
{
	int h = hash & 15;                      // CONVERT LO 4 BITS OF HASH CODE
	double u = h<8 ? x : y,                 // INTO 12 GRADIENT DIRECTIONS.
	       v = h<4 ? y : h==12||h==14 ? x : z;
	return ((h&1) == 0 ? u : -u) + ((h&2) == 0 ? v : -v);
}
