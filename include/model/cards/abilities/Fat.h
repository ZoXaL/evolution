#ifndef FAT_H
#define FAT_H

#include <string>
#include "model/cards/AbilityCard.h"
#include "model/cards/interfaces/FoodModification.h"
#include <iostream>
#include <string>

class Fat : public AbilityCard, public FoodModification {
bool reserve;
public:
	Fat();
	virtual ~Fat() {};

	bool needFood();
	void giveFood();
	void resetFood();

	std::string getStatus();
	int getCost();

	std::ostream& write(std::ostream&);
	std::istream& read(std::istream&);
};

#endif