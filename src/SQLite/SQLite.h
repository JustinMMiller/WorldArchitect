#ifndef SQLITE_H
#define SQLITE_H

#include <mutex>
#include <cstdarg>
#include <vector>
#include <sqlite3pp.h>


namespace WorldArchitect
{
	class SQLite
	{
		public:
			SQLite *getInstance();
		private:
			SQLite();
			static SQLite *instance;
			std::mutex lock;
	};
}

#endif
