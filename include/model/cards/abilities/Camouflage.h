#ifndef CAMOUFLAGE_H
#define CAMOUFLAGE_H

#include "model/cards/AbilityCard.h"
#include "model/cards/interfaces/DefendAbility.h"
#include <iostream>
#include <string>

class Camouflage : public AbilityCard, public DefendAbility {
int reserve;
public:
	Camouflage();
	virtual ~Camouflage() {};

	bool defend(Animal* hunter);

	AbilityCard* clone();

	std::string getStatus();
	int getCost();

	std::ostream& write(std::ostream&);
	std::istream& read(std::istream&);
};

#endif