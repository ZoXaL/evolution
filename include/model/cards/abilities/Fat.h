#ifndef FAT_H
#define FAT_H

#include <string>
#include "model/cards/AbilityCard.h"
#include <iostream>
#include <string>

class Fat : public AbilityCard {
bool reserve;
public:
	Fat();
	virtual ~Fat() {};

	bool hasReserve();
	void useReserve();
	void fillReserve();

	std::string getStatus();

	std::ostream& write(std::ostream&);
	std::istream& read(std::istream&);
};

#endif