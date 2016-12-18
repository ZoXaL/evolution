#include "exceptions/Exception.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

Exception::Exception() {
	strcpy(logPath, "log/log.txt");
	message = "No message";
	time_t tmp = time(nullptr);
	eTime = localtime(&tmp);
	log();
}
Exception::Exception(string message) {
	strcpy(logPath, "log/log.txt");
	this->message = message;
	time_t tmp = time(nullptr);
	eTime = localtime(&tmp);
	log();
}

void Exception::log() {
	ofstream stream;
	stream.open(logPath, ios::app | ios::out);
	if (!stream) {
		return;
	} else {
		stream << eTime->tm_mday << "-" << (1 + eTime->tm_mon) << "-"
		<< (1900+eTime->tm_year) << " " << (eTime->tm_hour) << ":" << (eTime->tm_min) 
		<< ":" << (eTime->tm_sec) << "    " << message << endl;
	}
}

ofstream& operator<<(ofstream& stream, const Exception& exception) {
	cout << "Writing exception to log file" << endl;
	cout << "Exception time: " << exception.eTime->tm_mday << "-" << (1 + exception.eTime->tm_mon) << "-"
		<< (1900+exception.eTime->tm_year) << " " << (exception.eTime->tm_hour) << ":" << (exception.eTime->tm_min) 
		<< ":" << (exception.eTime->tm_sec) << endl;
	cout << "Exception message: " << exception.message << endl;
	return stream;
}
ostream& operator<<(ostream& stream, const Exception& exception) {
	cout << "Writing exception to log file" << endl;
	cout << "Exception time:" << exception.eTime->tm_mday << "-" << (1 + exception.eTime->tm_mon) << "-"
		<< (1900+exception.eTime->tm_year) << " " << (exception.eTime->tm_hour) << ":" << (exception.eTime->tm_min) 
		<< ":" << (exception.eTime->tm_sec) << endl;
	cout << "Exception message: " << exception.message << endl;
	return stream;
}

// struct tm {
//    int tm_sec;   // seconds of minutes from 0 to 61
//    int tm_min;   // minutes of hour from 0 to 59
//    int tm_hour;  // hours of day from 0 to 24
//    int tm_mday;  // day of month from 1 to 31
//    int tm_mon;   // month of year from 0 to 11
//    int tm_year;  // year since 1900
//    int tm_wday;  // days since sunday
//    int tm_yday;  // days since January 1st
//    int tm_isdst; // hours of daylight savings time
// }