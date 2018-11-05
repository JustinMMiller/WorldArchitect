#include <vector>

// THIS CLASS IS A TRANSLATION TO C++11 FROM THE REFERENCE
// JAVA IMPLEMENTATION OF THE IMPROVED PERLIN FUNCTION (see http://mrl.nyu.edu/~perlin/noise/)
// THE ORIGINAL JAVA IMPLEMENTATION IS COPYRIGHT 2002 KEN PERLIN

// I ADDED AN EXTRA METHOD THAT GENERATES A NEW PERMUTATION VECTOR (THIS IS NOT PRESENT IN THE ORIGINAL IMPLEMENTATION)

//
// This code is from https://github.com/sol-prog/Perlin_Noise/blob/master/PerlinNoise.h . I have added some methods for added functionality not in the 
// original implementation.
//
#ifndef PERLINNOISE_H
#define PERLINNOISE_H

using namespace std;
class Perlin {
	// The permutation vector
	std::vector<int> p;
public:
	// Initialize with the reference values for the permutation vector
	Perlin(double amp, int octaves);
	Perlin();
	// Generate a new permutation vector based on the value of seed
	// Get a noise value, for 2D images z can have any value
	double noise(double x, double y, double z);
	double octaveNoise(double x, double y);
private:
	double fade(double t);
	double lerp(double t, double a, double b);
	double grad(int hash, double x, double y, double z);
	double amp;
	int octaves;
};

#endif
