#ifndef ABILITY_CARD_H
#define ABILITY_CARD_H

#include <string>
#include <iostream>
#include "model/cards/Card.h"
#include "model/cards/abilities/Ability.h"
#include "functions.h"
using namespace std;

class AbilityCard : public Card {
protected:
Ability::AbilityType ability;
bool duplicated;
bool passive;
public:
	AbilityCard(Ability::AbilityType, bool duplicated, bool passive);

	Ability::AbilityType getAbility();	

	string getDescription();
	AbilityCard* getAbilityCard();

	virtual ostream& write(ostream&) = 0;
	virtual istream& read(istream&) = 0;

	bool isDuplicated();
	bool isPassive();

	virtual string getStatus() = 0;
	
};

#endif