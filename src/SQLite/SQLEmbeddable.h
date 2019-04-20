#ifndef SQLEMBEDDABLE_H
#define SQLEMBEDDABLE_H

#include <string>
#include <vector>

namespace WorldArchitect
{
	class SQLEmbeddable
	{
		public:
			virtual std::string getTableName() = 0;
			virtual std::vector<std::string> > getFieldTypes() = 0;
	};
}

#endif
