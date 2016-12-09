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
public:
	AbilityCard(Ability::AbilityType);

	Ability::AbilityType getAbility();	

	string getDescription();
	virtual ostream& write(ostream&) = 0;
	virtual istream& read(istream&) = 0;

	// virtual string getStatus();
};

#endif