#include "Distribution.h"
#include<algorithm>

using namespace WorldArchitect;

Distribution::Distribution()
	: vals()
{
}

void Distribution::calcStdDev()
{
	if(mean == std::numeric_limits<double>::max())
	{
		calcMean();
	}
	if(stdev == std::numeric_limits<double>::max())
	{
		double tot = 0;
		for(double v : vals)
		{
			tot += pow(v - mean, 2);
		}
		if(vals.size() == 0)
		{
			stdev = 1;
		}
		else
		{
			tot /= vals.size();
			stdev = sqrt(tot);
		}
	}
	else
	{
		double tot = pow(stdev, 2);
		tot * size;
		for(double v : vals)
		{
			tot += pow(v - mean, 2);
		}
		if(vals.size() == 0)
		{
			stdev = 1;
		}
		else
		{
			tot /= vals.size();
			stdev = sqrt(tot);
		}

	}
}

void Distribution::calcMean()
{
	if(mean == std::numeric_limits<double>::max())
	{
		double total = 0;
		for(double v : vals)
		{
			total += v;
		}
		if(vals.size() == 0)
		{
			mean = 0;
		}
		else
		{
			mean = total / vals.size();
		}
	}
	else
	{
		std::vector<double> newVals(vals.begin()+size - 1, vals.end());
		double total = mean * size;
		for(double v : newVals)
		{
			total += v;
		}
		mean = total / vals.size();
	}
}

double Distribution::getPercentile(double percentile)
{
	if(!sorted)
	{
		std::sort(vals.begin(), vals.end());
		sorted = true;
	}
	return vals[(int)round((double)vals.size()*percentile) - 1];
}

double Distribution::getMean()
{
	if(mean == std::numeric_limits<double>::max())
	{
		calcMean();
	}
	return mean;
}

double Distribution::getStdDev()
{
	if(stdev == std::numeric_limits<double>::max())
	{
		calcStdDev();
	}
	return stdev;
}

void Distribution::addVal(double val)
{
	vals.push_back(val);

	if(stdev != std::numeric_limits<double>::max())
	{
		calcStdDev();
	}
	if(mean != std::numeric_limits<double>::max())
	{
		calcMean();
	}
	size = vals.size();
	sorted = false;
}

void Distribution::addVals(std::vector<double> newVals)
{
	vals.insert(vals.end(), newVals.begin(), newVals.end());
	if(stdev != std::numeric_limits<double>::max())
	{
		calcStdDev();
	}
	if(mean != std::numeric_limits<double>::max())
	{
		calcMean();
	}
	size = vals.size();
	sorted = false;

}

Distribution::~Distribution()
{
}

Distribution::Distribution(double mean, double stdev)
	: mean(mean), stdev(stdev), vals()
{
}
