#ifndef WATERFOWL_H
#define WATERFOWL_H

#include "model/cards/AbilityCard.h"
#include "model/cards/interfaces/DefendAbility.h"
#include <iostream>
#include <string>

class Waterfowl : public AbilityCard, public DefendAbility {
int reserve;
public:
	Waterfowl();
	virtual ~Waterfowl() {};

	bool defend(Animal* hunter);

	std::string getStatus();
	int getCost();

	std::ostream& write(std::ostream&);
	std::istream& read(std::istream&);
};

#endif