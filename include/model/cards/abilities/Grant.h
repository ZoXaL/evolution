#ifndef GRANT_H
#define GRANT_H

#include <string>
#include "model/cards/AbilityCard.h"
#include "model/cards/interfaces/FoodModification.h"
#include "model/cards/interfaces/DefendAbility.h"
#include <iostream>
#include <string>

class Grant : public AbilityCard, public FoodModification, public DefendAbility {
bool reserve;
public:
	Grant();
	virtual ~Grant() {};

	bool needFood();
	void giveFood();
	void resetFood();
	void decreaseFood();
	bool canGetFood();

	AbilityCard* clone();

	bool defend(Animal* hunter);

	std::string getStatus();
	int getCost();

	std::ostream& write(std::ostream&);
	std::istream& read(std::istream&);
};

#endif