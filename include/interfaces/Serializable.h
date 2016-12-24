#ifndef SERIALIZEABLE_H
#define SERIALIZEABLE_H
#include <iostream>

class Serializable {
public:
	virtual std::ostream& write(std::ostream&) = 0;
	virtual std::istream& read(std::istream&) = 0;
	virtual ~Serializable() {};
};
#endif