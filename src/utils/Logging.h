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

namespace WorldArchitect
{
	//This is an asynchronous logging system. Loggers are requested from the LogManager, and only one of each Logger
	//will exist. 

	//
	//USAGE NOTES:
	// To use a predefined Logger:
	// 	Logger *logger = LogManager::getInstance()->getLogger(<Log Type desired>);
	// 	logger->log("String to log");
	//
	// To define a new Logger:
	// 	Add a new LogType (ie TerrainCreation)
	// 	create new case in getLogger()
	// 	Use in same manner as predefined Logger.
	//


	/// This enum lists the different types of Loggers. Used for lookup of Loggers when requested with getLogger.
	enum LogType
	{
		Error,
		MapCreation
	};

	/// Struct to order messages for a Logger so that order is preserved.
	typedef struct _MESSAGE
	{
		time_t timestamp;
		std::string message;
		bool operator<(const struct _MESSAGE& rhs) const
		{
			return difftime(timestamp, rhs.timestamp) < 0;
		}
	} Message;

	/**
	 * \class Logger
	 * \brief Each Logger writes it's contents to a specific file. Works asynchronously.
	 *
	 * This class is accessed through the LogManager singleton. Each Logger is responsible
	 * for one log file. It is designed to be thread safe.
	 *
	 * \author Justin Miller
	 */
	class Logger
	{
		private:
			/// Locks the priority_queue of Messages
			std::mutex lock;
			/// Holds the list of Messages sorted by timestamp.
			std::priority_queue<Message> messages;
			/// The file the Logger writes to
			char *fhandle;
			/// The thread this Logger is running on.
			std::thread *logThread;
			/// What type of Logger is this. Each logfile is associated with a different type.
			LogType logType;
			/// Set when the logger is closed, indicates to flush the contents of messages.
			bool closing;
			/**
			 * This function runs the Logger in the background, consuming messages in
			 * the queue whenever they are available.
			 */
			void threadFunc();
			/// This function adds a Message to the queue.
			void addMessage(Message mess);
		public:
			/// Returns the type of the Logger. Used to determine if specific Loggers have been instantiated by the LogManager.
			LogType getType();
			/// This takes in the string from the user, forms it into a Message and passes it to addMessage.
			void log(std::string mess);
			/// This function sets the closing variable and waits for the thread to finish.
			void close();
			/// This function starts the Logger thread.
			void open();
			/**
			 * \brief Creates a new Logger.
			 * \param filehandle the name of the file to log to.
			 * \param t The type of the Logger. Used when checking if a specific Logger is available.
			 * 
			 */
			Logger(char *filehandle, LogType t);
			/// Destructor. Calls close()
			~Logger();
	};


	/**
	 * \class LogManager
	 * \brief Used to manage Loggers.
	 *
	 * This is a singleton to request a Logger of a specific type. This ensures that only one Logger
	 * is writing to a given file.
	 */
	class LogManager
	{
		private:
			/// vector of Loggers created as the Logger is needed.
			std::vector<Logger *> logs;
			std::mutex m;
			/// Instantiates LogManager.
			LogManager();
			/// Empty constructor to ensure no copy.
			LogManager(LogManager const& copy);
			/// Empty constructor to ensure no copy.
			LogManager& operator=(LogManager const&copy);
			/// Destructor.
			~LogManager();
			/// This is the only instance of the LogManager class. 
			static LogManager *instance;
		public:
			/// returns instance if available, instantiates and returns if it doesn't exist yet.
			static LogManager *getInstance();
			/// Returns the Logger of the requested type, creating it if it does not already exist. 
			Logger *getLogger(LogType type);
			/// Closes all open Loggers.
			void closeAllLogs();
	}; // $$TODO : Should have a lock on the vector of Loggers. Need to figure out lock that'll work. May preemptively initialize every logger then open before returning if they aren't already open.
}
#endif
