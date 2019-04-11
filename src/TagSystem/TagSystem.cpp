#include "TagSystem.h"

using namespace WorldArchitect;

TagSystem::TagSystem()
	: tags()
{
	tags.push_back(new Tag("example", "Tags/test.lua"));
}

void TagSystem::loadTags()
{
}

bool TagSystem::checkTag(std::string tagName, Settlement *s)
{
	return getTag(tagName)->meetsCondition(s);
}

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
