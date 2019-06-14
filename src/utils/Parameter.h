#ifndef PARAMETER_H
#define PARAMETER_H

#include<string>

namespace WorldArchitect
{
	enum ParamType
	{
		IntParam,
		StringParam,
		RealParam
	};

	class Parameter
	{
		public:
			void setValue(std::string newval) {value = newval;}
			std::string getValue() const {return value;}
			Parameter(std::string v, ParamType t) : value(v), type(t) {}
			Parameter() {}
		private:
			std::string value;
			ParamType type;
	};
}
#endif
