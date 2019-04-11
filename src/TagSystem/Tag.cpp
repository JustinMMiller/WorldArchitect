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
	return lua["testFunc"](s);
}

/**
 * Constructor which takes in a tagName and a scriptFile.
 * @param tagName The name for this Tag
 * @param scriptFile The name of the script to load for this Tag.
 */
Tag::Tag(std::string tagName, std::string scriptFile)
{
	prepareLuaState(&(this->lua));
	this->lua.script_file(scriptFile);
	this->name = tagName;
}

/**
 * Constructor which only takes in a tagName. 
 * @param tagName The name for this Tag.
 */
Tag::Tag(std::string tagName)
{
	this->name = tagName;
}

/**
 * This function just returns the name of the Tag.
 */
std::string Tag::getName()
{
	return this->name;
}
