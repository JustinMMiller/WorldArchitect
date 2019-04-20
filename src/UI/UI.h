#ifndef UI_H
#define UI_H

#include <string>

namespace WorldArchitect
{
	class UI
	{
		virtual int requestInt(std::string paramName) = 0;
		virtual std::string requestString(std::string paramName) = 0;
		virtual double requestDouble(std::string paramName) = 0;
		virtual void init() = 0;
	};
}
#endif
