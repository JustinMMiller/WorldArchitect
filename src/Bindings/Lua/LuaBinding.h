#ifndef LUABINDING_H
#define LUABINDING_H

#include "lib/sol2/sol.hpp"

namespace WorldArchitect
{
	void prepareLuaState(sol::state *lua);
}

#endif
