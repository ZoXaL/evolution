#ifndef FAT_H
#define FAT_H

#include <string>
#include "AbilityCard.h"

class Fat : public AbilityCard {
bool reserve;
public:
	bool hasReserve();
	void useReserve();

	// std::string getDescription();
	// ostream& write(ostream&);
	// istream& read(istream&);
}

#endif