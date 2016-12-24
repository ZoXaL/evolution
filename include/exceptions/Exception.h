#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <ctime>
#include <iostream>
#include <string>
#include "Logger.h"
using namespace std;

class Exception {
string message;
public:
	Exception(string message = "No message");
	void log();
	void log(Logger::LogLevel level);
	virtual string getMessage();
	friend ostream& operator<<(ostream& stream, const Exception&);
	virtual ~Exception() {};
};
#endif