#include <ctime>
#include <fstream>
#include <string>

#include "Logger.h"
using namespace std;


const char Logger::logPath[80] = "log/log.txt";
const Logger::LogLevel Logger::logLevel= Logger::DEBUG;

void Logger::log(string message, Logger::LogLevel level) {
	if (level > logLevel) return;

	time_t tmp = time(nullptr);
	tm* eTime = localtime(&tmp);

	ofstream stream;
	stream.open(logPath, ios::app | ios::out);
	if (!stream) {
		return;
	} else {
		stream << eTime->tm_mday << "-" << (1 + eTime->tm_mon) << "-"
		<< (1900+eTime->tm_year) << " " << (eTime->tm_hour) << ":" << (eTime->tm_min) 
		<< ":" << (eTime->tm_sec) << " : " << logLevelToString(level) << "    " << message << endl;
	}
	stream.close();
}
string Logger::logLevelToString(Logger::LogLevel level) {
	switch (level) {
		case (Logger::FATAL) : {
			return "[FATAL]";
		}
		case (Logger::WARN) : {
			return "[WARN]";
		}
		case (Logger::INFO) : {
			return "[INFO]";
		}
		case (Logger::DEBUG) : {
			return "[DEBUG]";
		}
		case (Logger::TRACE) : {
			return "[TRACE]";
		}
	}
}

void Logger::fatal(std::string message) {
	log(message, Logger::FATAL);
}
void Logger::warn(std::string message) {
	log(message, Logger::WARN);
}
void Logger::info(std::string message) {
	log(message, Logger::INFO);
}
void Logger::debug(std::string message) {
	log(message, Logger::DEBUG);
}
void Logger::trace(std::string message) {
	log(message, Logger::TRACE);
}