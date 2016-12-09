#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <ctime>
#include <iostream>
#include <string>
using namespace std;

class Exception {
tm* eTime;
string message;
char logPath[80];
public:
	Exception();
	Exception(string message);
	void log();
	friend ofstream& operator<<(ofstream& stream, const Exception&);
	friend ostream& operator<<(ostream& stream, const Exception&);
};
#endif