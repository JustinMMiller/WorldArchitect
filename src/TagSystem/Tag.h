#ifndef TAG_H
#define TAG_H

#include <string>

#include "SettlementSystem/Settlement.h"
#include "lib/sol2/sol.hpp"

namespace WorldArchitect
{
	/// \class Tag
	/// \brief This class associates a tag string with a script which checks to see if a Settlement meets the condition for said Tag.
	class Tag
	{
		public:
			bool meetsCondition(Settlement *s);
			Tag(std::string tagName, std::string scriptFile);
			Tag(std::string tagName);
			std::string getName();
		private:
			sol::state lua;
			std::string name;
	};
}
#endif
