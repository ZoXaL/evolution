#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <ctime>
#include <iostream>
#include <string>
#include "Logger.h"
using namespace std;

class Exception {
protected:
	string message;
public:
	Exception(string message = "No message");
	virtual void log();
	virtual void log(Logger::LogLevel level);
	virtual string getMessage();
	virtual ~Exception() {};
};
#endif