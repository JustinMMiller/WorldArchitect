#ifndef PARAMETER_H
#define PARAMETER_H

#include<string>

namespace WorldArchitect
{
	template<typename T> class Parameter
	{
		public:
			void setValue(T newval) {value = newval;}
			T getValue() {return value;}
		private:
			T value;
	};
}
#endif
