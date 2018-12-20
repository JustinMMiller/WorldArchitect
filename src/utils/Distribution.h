#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H
#include <vector>
#include <limits>
#include <math.h>
#include<stdbool.h>

namespace WorldArchitect
{
	/// \class Distribution
	/// \brief This is a utility class for representing 
	/// normal Gaussian distributions.
	class Distribution
	{
		private:
			double mean = std::numeric_limits<double>::max();
			double stdev = std::numeric_limits<double>::max();
			int size = 0;
			std::vector<double> vals;
			void calcMean();
			void calcStdDev();
			bool sorted = false;
		public:
			/// \function getPercentile
			/// \param percentile - double from (0,1.0)
			/// This function will return the value in the distribution
			/// with the given percentile. This won't be a perfectly accurate 
			/// implementation. I will be using the sorted values of the distribution 
			/// to calculate percentiles.
			double getPercentile(double percentile);
			/// returns the mean of the Distribution
			double getMean();
			/// returns the standard deviation of the Distribution
			double getStdDev();
			/// Adds a single double to the Distribution
			void addVal(double val);
			/// Adds a vector of doubles to the Distribution
			void addVals(std::vector<double> newVals);
			Distribution();
			~Distribution();
			/// Constructor which allows you to specify the mean 
			/// and standard deviation. Note, that if any values are
			/// added to a Distribution created in this way the mean
			/// and standard deviation are recalculated.
			Distribution(double mean, double stdev);
	};
}
#endif
