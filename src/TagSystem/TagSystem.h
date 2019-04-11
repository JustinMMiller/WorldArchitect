#ifndef TAGSYSTEM_H
#define TAGSYSTEM_H

#include <vector>
#include "Tag.h"
#include "SettlementSystem/Settlement.h"

namespace WorldArchitect
{
	class TagSystem
	{
		public:
			TagSystem();
			void loadTags();
			bool checkTag(std::string tagName, Settlement *s);
		private:
			std::vector<Tag*> tags;
			Tag *getTag(std::string tagName);
	};
}

#endif
