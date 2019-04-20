#ifndef TUI_H
#define TUI_H
#include<string>
#include "UI.h"

namespace WorldArchitect
{
	class TUI : public UI
	{
		int requestInt(std::string paramName);
		std::string requestString(std::string paramName);
		double requestDouble(std::string paramName);
		void init();
	};
}
#endif
