#ifndef UISYSTEM_H
#define UISYSTEM_H

#include "UI.h"
#include "TUI.h"
#include <mutex>

namespace WorldArchitect
{
	class UISystem
	{
		public:
			static UISystem *getInstance();
			int requestInt(std::string paramName);
			std::string requestString(std::string paramName);
			double requestDouble(std::string paramName);
		private:
			UISystem();
			static UISystem *instance;
			static std::mutex lock;
			UI *ui;
	};
}

#endif
