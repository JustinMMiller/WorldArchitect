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
			virtual std::string getColumnNames() = 0;
			virtual std::string getSQLValueString() = 0;
			virtual std::string getPrimaryKey() = 0;
	};
}

#endif
