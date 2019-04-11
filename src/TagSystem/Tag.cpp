#include "Tag.h"
#include "Bindings/Lua/LuaBinding.h"
#include "MapGenSystem/MapGenSystem.h"

using namespace WorldArchitect;

bool Tag::meetsCondition(Settlement *s)
{
	return lua["testFunc"](MapGenSystem::getInstance()->getMap());
}

Tag::Tag(std::string tagName, std::string scriptFile)
{
	prepareLuaState(&(this->lua));
	this->lua.script_file(scriptFile);
	this->name = tagName;
}

Tag::Tag(std::string tagName)
{
	this->name = tagName;
}

std::string Tag::getName()
{
	return this->name;
}
