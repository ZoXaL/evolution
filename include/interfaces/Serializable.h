#ifndef SERIALIZEABLE_H
#define SERIALIZEABLE_H
#include <iostream>

class Serializable {
public:
	virtual ostream& write(ostream&) = 0;
	virtual istream& read(istream&) = 0;
};
#endif