#include "LuaTag.h"
#include "Bindings/Lua/LuaBinding.h"
#include "MapGenSystem/MapGenSystem.h"

using namespace WorldArchitect;

/**
 * This function returns true if the given Settlement meets the condition, false otherwise.
 * @param s The settlement to check the LuaTag against.
 */
bool LuaTag::meetsCondition(Settlement *s)
{
	return lua["testFunc"](s);
}

/**
 * Constructor which takes in a tagName and a scriptFile.
 * @param tagName The name for this LuaTag
 * @param scriptFile The name of the script to load for this LuaTag.
 */
LuaTag::LuaTag(std::string tagName, std::string scriptFile)
	: Tag(tagName)
{
	prepareLuaState(&(this->lua));
	this->lua.script_file(scriptFile);
}

/**
 * Constructor which only takes in a tagName. 
 * @param tagName The name for this LuaTag.
 */
LuaTag::LuaTag(std::string tagName)
	: Tag(tagName)
{
}
