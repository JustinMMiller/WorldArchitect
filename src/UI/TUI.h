#ifndef TUI_H
#define TUI_H
#include<string>
#include "UI.h"
namespace WorldArchitect
{
	class TUI : public UI
	{
		int requestInt(std::string name);
		char *requestString(std::string name);
	};
}
#endif
