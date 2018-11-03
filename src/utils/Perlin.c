#include "Perlin.h"

Perlin::Perlin(int fidelity = 256)
	: fidel(fidelity)
{
	srand(time(NULL));
	p.resize(fidel);
	iota(p.begin(), p.end(), 0);

	default_random_engine engine(rand());

	shuffle(p.begin(), p.end(), engine);
	p.insert(p.end(), p.begin(), p.end());
}

double Perlin::noise(double x, double y, double z)
{
	int X = (int) floor(x) & (fidel - 1);
	int Y = (int) floor(y) & (fidel - 1);
	int Z = (int) floor(z) & (fidel - 1);
	x -= floor(x);
	y -= floor(y);
	z -= floor(z);
	double u = fade(x);
	double v = fade(y);
	double w = fade(z);

	int A = p[X] + Y;
	int AA = p[A] + Z;
	int AB = p[A + 1] + Z;
	int B = p[X + 1] + Y;
	int BA = p[B] + Z;
	int BB = p[B + 1] + Z;

	double res = lerp(w, lerp(v, lerp(u, grad(p[AA], x, y, z), grad(p[BA], x-1, y, z)), lerp(u, grad(p[AB], x, y-1, z), grad(p[BB], x-1, y-1, z))), lerp(v, lerp(u, grad(p[AA+1], x, y, z-1), grad(p[BA+1], x-1, y, z-1)), lerp(u, grad(p[AB+1], x, y-1, z-1), grad(p[BB+1], x-1, y-1, z-1))));
	return (res + 1.0)/2.0;
}

double Perlin::fade(double t)
{
	return t * t * t * (t * (t * 6 - 15) + 10);
}

double Perlin::lerp(double t, double a, double b) {
	return a + t * (b - a);
}

double Perlin::grad(int hash, double x, double y, double z) {
	int h = hash & 15;
	// Convert lower 4 bits of hash into 12 gradient directions
	double u = h < 8 ? x : y,
		   v = h < 4 ? y : h == 12 || h == 14 ? x : z;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}
