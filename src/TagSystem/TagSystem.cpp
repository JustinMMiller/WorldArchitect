#include <dirent.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

#include "TagSystem.h"
#include "utils/ConfigSystem.h"

using namespace WorldArchitect;

/**
 * Default constructor.
 */
TagSystem::TagSystem()
	: tags()
{
}

void TagSystem::init()
{
	auto config = ConfigSystem::getInstance();
	config->addParameter("TagDir", ParamType::StringParam, "Tags");
	config->addParameter("TagConfFile", ParamType::StringParam, "conf.json");
}

/**
 * This function loads in all Tags from their respective script files.
 */
void TagSystem::loadTags()
{
	auto conf = ConfigSystem::getInstance();
	std::filesystem::path tagdir(conf->getParameterValue("TagDir"));
	std::filesystem::path tagconf = tagdir;
	tagconf /= conf->getParameterValue("TagConfFile");
	std::ifstream i(tagconf.string());
	nlohmann::json j;
	i >> j;
	for (auto ent : j)
	{
		tags.push_back(new LuaTag(ent["name"], tagdir / ent["file"]));
	}
}

/**
 * This function returns checks if a Settlement meets the conditions of the Tag 
 * with the given name
 * @param tagName The name of the Tag to be checked against.
 * @param s The Settlement to pass to the Tag to check.
 */
bool TagSystem::checkTag(std::string tagName, Settlement *s)
{
	return getTag(tagName)->meetsCondition(s);
}

/**
 * Internal helper method to find a Tag with a given name. Might switch to a 
 * HashMap like system rather than iterative search. $$TODO Figure this out.
 */
Tag * TagSystem::getTag(std::string tagName)
{
	for(Tag *tag : tags)
	{
		if(!tag->getName().compare(tagName))
		{
			return tag;
		}
	}
	return NULL;
}
