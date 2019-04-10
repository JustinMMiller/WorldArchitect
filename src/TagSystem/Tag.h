#ifndef TAG_H
#define TAG_H
#include "SettlementSystem/Settlement.h"
namespace WorldArchitect
{
	class Tag
	{
		public:
			bool meetsCondition(Settlement *s);
			Tag();
	};
}
#endif
