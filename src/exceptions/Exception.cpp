#include "exceptions/Exception.h"
#include <iostream>
#include <string>
#include <string.h>
#include <ctime>
#include "Logger.h"

Exception::Exception(string message) {
	this->message = message;
	Logger::warn(message);
}

void Exception::log() {
	Logger::log(message, Logger::WARN);
}
void Exception::log(Logger::LogLevel level) {
	Logger::log(message, level);
}

ostream& operator<<(ostream& stream, const Exception& exception) {
	time_t tmp = time(nullptr);
	tm* eTime = localtime(&tmp);
	cout << "Exception time:" << eTime->tm_mday << "-" << (1 + eTime->tm_mon) << "-"
		<< (1900+eTime->tm_year) << " " << (eTime->tm_hour) << ":" << (eTime->tm_min) 
		<< ":" << (eTime->tm_sec) << endl;
	cout << "Exception message: " << exception.message << endl;
	return stream;
}
string Exception::getMessage() {
	return message;
}