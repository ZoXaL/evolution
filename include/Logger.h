#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger {
	static const char logPath[80];	
public:
	enum LogLevel{
		FATAL = 1, WARN, INFO, DEBUG, TRACE
	};
	static void log(std::string message, LogLevel level);
	static void fatal(std::string message);
	static void warn(std::string message);
	static void info(std::string message);
	static void debug(std::string message);
	static void trace(std::string message);
private:
	static const LogLevel logLevel;	
	static std::string logLevelToString(Logger::LogLevel level);
};

#endif
