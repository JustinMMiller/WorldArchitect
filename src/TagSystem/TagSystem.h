#ifndef TAGSYSTEM_H
#define TAGSYSTEM_H

#include <vector>

#include "Tag.h"
#include "SettlementSystem/Settlement.h"

namespace WorldArchitect
{

	/// \class TagSystem
	/// 
	/// \brief This class wraps Tags for the rest of the program.
	/// 
	/// This class handles loading and interacting with Tags. It will handle
	/// loading in each Tag from the file they are defined in.
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
