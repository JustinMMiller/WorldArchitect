#ifndef PERLIN_H
#define PERLIN_H
using namespace std;
#include<vector>
#include<cmath>
#include<random>
#include<algorithm>
#include<numeric>

class Perlin
{
	private:
		int fidel = 256;
		vector<int> p;
		double fade(double t);
		double lerp(double t, double a, double b);
		double grad(int hash, double x, double y, double z);
	public:
		Perlin();
		Perlin(int fidelity);
		double noise(double x, double y, double z = 0);
};
#endif
