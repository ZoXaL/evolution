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

string Exception::getMessage() {
	return message;
}