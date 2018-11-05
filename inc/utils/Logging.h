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

enum LogType
{
	Error,
	MapCreation
};

typedef struct _MESSAGE
{
	time_t timestamp;
	string message;
	bool operator<(const struct _MESSAGE& rhs) const
	{
		return difftime(timestamp, rhs.timestamp) < 0;
	}
} Message;

class Logger
{
	private:
		mutex lock;
		priority_queue<Message> messages;
		string fhandle;
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