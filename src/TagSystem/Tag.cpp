#include "Tag.h"
#include "Bindings/Lua/LuaBinding.h"
#include "MapGenSystem/MapGenSystem.h"

using namespace WorldArchitect;

/**
 * This function returns true if the given Settlement meets the condition, false otherwise.
 * @param s The settlement to check the Tag against.
 */
bool Tag::meetsCondition(Settlement *s)
{
	return false;
}

Tag::Tag()
	: name()
{
}

Tag::Tag(std::string tagName)
	: name(tagName)
{
}
