#ifndef PARAMETERS_H
#define PARAMETERS_H

#include<string>

namespace WorldArchitect
{
	template<typename T> class Parameter
	{
		public:
			char *getName() {return typeid(T).name();}
			void setValue(T newval);
			T getValue() {return value; }
		private:
			T value;
	};
}
#endif
