#ifndef TOXIC_H
#define TOXIC_H

#include "model/cards/AbilityCard.h"
#include "model/cards/interfaces/DefendAbility.h"
#include <iostream>
#include <string>

class Toxic : public AbilityCard, public DefendAbility {
int reserve;
public:
	Toxic();
	virtual ~Toxic() {};

	bool defend(Animal* hunter);

	AbilityCard* clone();

	std::string getStatus();
	int getCost();

	std::ostream& write(std::ostream&);
	std::istream& read(std::istream&);
};

#endif