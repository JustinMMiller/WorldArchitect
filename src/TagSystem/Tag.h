#ifndef TAG_H
#define TAG_H

#include <string>

#include "SettlementSystem/Settlement.h"
#include "lib/sol2/sol.hpp"

namespace WorldArchitect
{
	class Tag
	{
		public:
			bool meetsCondition(Settlement *s);
			Tag(std::string tagName, std::string scriptFile);
			Tag(std::string tagName);
		private:
			sol::state lua;
	};
}
#endif
