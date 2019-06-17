#ifndef LUATAG_H
#define LUATAG_H

#include <string>

#include "Tag.h"
#include "SettlementSystem/Settlement.h"
#include "lib/sol2/sol.hpp"

namespace WorldArchitect
{
	/// \class LuaTag
	/// \brief This class associates a tag string with a script which checks to see if a Settlement meets the condition for said Tag.
	class LuaTag : public Tag
	{
		public:
			bool meetsCondition(Settlement *s);
			LuaTag(std::string tagName, std::string scriptFile);
			LuaTag(std::string tagName);
		private:
			sol::state lua;
	};
}
#endif
