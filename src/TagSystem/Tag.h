#ifndef TAG_H
#define TAG_H

#include <string>

#include "SettlementSystem/Settlement.h"

namespace WorldArchitect
{
	/// \class Tag
	/// \brief This class associates a tag string with a script which checks to see if a Settlement meets the condition for said Tag.
	class Tag
	{
		public:
			virtual bool meetsCondition(Settlement *s) = 0;
			Tag(std::string tagName);
			Tag();
			std::string getName() {return name;}
		private:
			std::string name;
	};
}
#endif
