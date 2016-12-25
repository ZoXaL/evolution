#ifndef FAST_H
#define FAST_H

#include "model/cards/AbilityCard.h"
#include "model/cards/interfaces/DefendAbility.h"
#include <iostream>
#include <string>

class Fast : public AbilityCard, public DefendAbility {
int reserve;
public:
	Fast();
	virtual ~Fast() {};

	bool defend(Animal* hunter);

	AbilityCard* clone();

	std::string getStatus();
	int getCost();

	std::ostream& write(std::ostream&);
	std::istream& read(std::istream&);
};

#endif