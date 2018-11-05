#ifndef LOGGING_H
#define LOGGING_H
#include<mutex>
#include<thread>
#include<ctime>
#include<iostream>
#include<fstream>
#include<string>
#include<queue>
#include<vector>
#include<chrono>

using namespace std;

//This is an asynchronous logging system. Loggers are requested from the LogManager, and only one of each Logger
//will exist. 


//This enum lists the different types of Loggers. Used for lookup of Loggers when requested with getLogger.
enum LogType
{
	Error,
	MapCreation
};

//Struct to order messages for a Logger so that order is preserved.
typedef struct _MESSAGE
{
	time_t timestamp;
	string message;
	bool operator<(const struct _MESSAGE& rhs) const
	{
		return difftime(timestamp, rhs.timestamp) < 0;
	}
} Message;

//Each Logger writes it's contents to a specific file. Works asynchronously.
class Logger
{
	private:
		mutex lock;
		priority_queue<Message> messages;
		char *fhandle;
		thread *logThread;
		LogType logType;
		bool closing;
		void threadFunc();
		void addMessage(Message mess);
	public:
		LogType getType();
		void log(string mess);
		void close();
		void open();
		Logger(char *filehandle, LogType t);
		~Logger();
};


//This is a singleton to request a Logger of a specific type. This ensures that only one Logger
//is writing to a given file.
class LogManager
{
	private:
		vector<Logger *> logs;
		LogManager();
		LogManager(LogManager const& copy);
		LogManager& operator=(LogManager const&copy);
		~LogManager();
		static LogManager *instance;
	public:
		static LogManager *getInstance();
		Logger *getLogger(LogType type);
		void closeAllLogs();
};
#endif
