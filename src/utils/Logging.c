#include "Logging.h"

Logger::Logger(char *filehandle, LogType t)
	: lock(),
	fhandle(filehandle),
	logType(t),
	messages(),
	closing(false)
{
}

void Logger::threadFunc()
{
	ofstream file;
	file.open(fhandle, ios_base::app);
	if(!file.is_open())
	{
		printf("Unable to open log %s for writing.\n", fhandle);
		return;
	}
	while(!closing)
	{
		if(messages.empty())
		{
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
	close();
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
	if(LogManager::manager == NULL)
	{
		LogManager::manager = new LogManager();
	}
	return LogManager::manager;
}

LogManager::~LogManager()
{
	for(Logger *l : manager->logs)
	{
		l->close();
	}
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
						l->log("Unable to open requested log, returning Error log\n");
						return l;
					}
				}
				log = new Logger("Error.log", Error);
				log->log("Unable to open requested log, returning Error log\n");
				logs.push_back(log);
				return log;
			}
			log = new Logger("Error.log", Error);
			log->log("Unable to open requested log, returning Error log\n");
			logs.push_back(log);
			return log;
	}
}
