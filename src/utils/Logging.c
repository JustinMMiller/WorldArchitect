#include "Logging.h"
#include<stdio.h>
#include<stdlib.h>


using namespace WorldArchitect;
using namespace std;
LogManager *LogManager::instance = NULL;
//Default constructor for a Logger. Ensures that the thread for the Logger 
//is started on creation.
Logger::Logger(std::string filehandle, LogType t)
	: lock(),
	messages(),
	closing(false)
{
	fhandle = std::string(filehandle);
	this->logType = t;
	this->open();
}

//This is the thread function for a Logger. This runs in the background and consumes Message
//objects from the messages queue. It sleeps for 1 second if there are no messages to consume.
void Logger::threadFunc()
{
	printf("Opening %s for logging\n", fhandle.c_str());
	ofstream file;
	file.open(fhandle.c_str());
	if(!file.is_open())
	{
		//This was used for debugging purposes. 
		//printf("Unable to open log %s for writing.\n", fhandle);
		return;
	}
	while(!closing)
	{
		if(messages.empty())
		{
			//This was used for debugging purposes. 
			//printf("No messages, %s sleeping\n", fhandle);
			this_thread::sleep_for(chrono::milliseconds(250));
		}
		else
		{
			lock.lock();
			file << messages.top().message;
			messages.pop();
			lock.unlock();
		}
	}
	//This was used for debugging purposes. 
	//printf("Log %s closing, flushing queue\n", fhandle);
	lock.lock();
	while(!messages.empty())
	{
		file << messages.top().message;
		messages.pop();
	}
	file.close();
	lock.unlock();
}


/**
 * addMessage(Message mess)
 * This is an internal method to insert a Message struct into the queue for the Logger to consume.
 */
void Logger::addMessage(Message mess)
{
	lock.lock();
	messages.push(mess);
	lock.unlock();
}

//The destructor closes the Logger.
Logger::~Logger()
{
	this->close();
}


//This method sets the closing variable to true, which tells the thread to finish the queue and exit.
void Logger::close()
{
	closing = true;
	if(logThread)
	{
		logThread->join();
	}
}

//This method takes in a string and puts it in a Message struct, then passes it to addMessage.
void Logger::log(string mess)
{
	if(!logThread)
	{
		open();
	}
	Message newMessage;
	newMessage.message = string(mess);
	newMessage.timestamp = time(0);
	addMessage(newMessage);
}

//This method starts the thread for the Logger.
void Logger::open()
{
	lock.lock();
	logThread = new thread(&Logger::threadFunc, this);
	lock.unlock();
}

//This is a helper method for ensuring only one of each Logger is created.
LogType Logger::getType()
{
	return logType;
}

//Constructor for LogManager
LogManager::LogManager()
	: logs(), m()
{
	logs.push_back(new Logger("Error.log", Error));
	logs.push_back(new Logger("MapCreation.log", MapCreation));
}

//This function returns the only instance of a LogManager, creating it if it is null.
LogManager *LogManager::getInstance()
{
	if(LogManager::instance == NULL)
	{
		LogManager::instance = new LogManager();
	}
	return LogManager::instance;
}

//Empty destructor for LogManager.
LogManager::~LogManager()
{
}

//This function first checks to see if the requested Logger exists, returning it
//if it does. If not, it creates it, adds it to the vector of Loggers, and returns it.
Logger *LogManager::getLogger(LogType ltype)
{
	Logger *log;
	m.lock();
	for(Logger *l : logs)
	{
		if(l->getType() == ltype)
		{
			log = l;
			goto cleanup;
		}
	}
	switch (ltype)
	{
		case Error:
			log = new Logger("Error.log", Error);
			logs.push_back(log);
			goto cleanup;
			break;
		case MapCreation:
			log = new Logger("MapCreation.log", MapCreation);
			logs.push_back(log);
			goto cleanup;
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
						log = l;
						goto cleanup;
					}
				}
				printf("Unable to open requested log\n");
				log = new Logger("Error.log", Error);
				log->log("Unable to open requested log, returning Error log\n");
				logs.push_back(log);
				goto cleanup;
			}
			printf("Unable to open requested log\n");
			log = new Logger("Error.log", Error);
			log->log("Unable to open requested log, returning Error log\n");
			logs.push_back(log);
			goto cleanup;
	}

cleanup:
	m.unlock();
	return log;
}
