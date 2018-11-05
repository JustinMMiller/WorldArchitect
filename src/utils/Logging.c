#include "Logging.h"
#include<stdio.h>
#include<stdlib.h>

Logger::Logger(char *filehandle, LogType t)
	: lock(),
	fhandle(filehandle),
	logType(t),
	messages(),
	closing(false)
{
	this->open();
}

LogManager* LogManager::instance = NULL;

void Logger::threadFunc()
{
	printf("Opening %s for logging\n", fhandle);
	ofstream file;
	file.open(fhandle);
	if(!file.is_open())
	{
		printf("Unable to open log %s for writing.\n", fhandle);
		return;
	}
	while(!closing)
	{
		if(messages.empty())
		{
			printf("No messages, %s sleeping\n", fhandle);
			this_thread::sleep_for(chrono::seconds(1));
		}
		else
		{
			lock.lock();
			file << messages.top().message;
			messages.pop();
			lock.unlock();
		}
	}
	printf("Log %s closing, flushing queue\n", fhandle);
	lock.lock();
	while(!messages.empty())
	{
		file << messages.top().message;
		messages.pop();
	}
	file.close();
	lock.unlock();
}

void Logger::addMessage(Message mess)
{
	lock.lock();
	messages.push(mess);
	lock.unlock();
}

Logger::~Logger()
{
	this->close();
}

void Logger::close()
{
	closing = true;
	logThread->join();
}

void Logger::log(string mess)
{
	Message newMessage;
	newMessage.message = mess;
	newMessage.timestamp = time(0);
	addMessage(newMessage);
}

void Logger::open()
{
	logThread = new thread(&Logger::threadFunc, this);
}

LogType Logger::getType()
{
	return logType;
}


LogManager::LogManager()
	: logs()
{
}

LogManager *LogManager::getInstance()
{
	if(!instance)
	{
		instance = new LogManager();
	}
	return instance;
}

LogManager::~LogManager()
{
}

Logger *LogManager::getLogger(LogType ltype)
{
	for(Logger *l : logs)
	{
		if(l->getType() == ltype)
		{
			return l;
		}
	}
	Logger *log;
	switch (ltype)
	{
		case Error:
			log = new Logger("Error.log", Error);
			logs.push_back(log);
			return log;
			break;
		case MapCreation:
			log = new Logger("MapCreation.log", MapCreation);
			logs.push_back(log);
			return log;
			break;
		default:
			if(!logs.empty())
			{
				for(Logger *l : logs)
				{
					if(l->getType() == Error)
					{
						printf("Unable to open requested log\n");
						l->log("Unable to open requested log, returning Error log\n");
						return l;
					}
				}
				printf("Unable to open requested log\n");
				log = new Logger("Error.log", Error);
				log->log("Unable to open requested log, returning Error log\n");
				logs.push_back(log);
				return log;
			}
			printf("Unable to open requested log\n");
			log = new Logger("Error.log", Error);
			log->log("Unable to open requested log, returning Error log\n");
			logs.push_back(log);
			return log;
	}
}
