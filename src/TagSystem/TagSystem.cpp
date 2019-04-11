#include "TagSystem.h"

using namespace WorldArchitect;

/**
 * Default constructor.
 */
TagSystem::TagSystem()
	: tags()
{
	tags.push_back(new Tag("example", "Tags/test.lua"));
}

/**
 * This function loads in all Tags from their respective script files.
 */
void TagSystem::loadTags()
{
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
