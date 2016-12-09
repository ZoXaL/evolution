#ifndef ABILITY_CARD_H
#define ABILITY_CARD_H

#include <string>
#include <iostream>
#include "model/cards/Card.h"
#include "model/cards/abilities/Ability.h"
#include "exceptions/Exception.h"
#include "functions.h"
using namespace std;

class AbilityCard : public Card {
Ability::AbilityType ability;

public:
	Ability::AbilityType getAbility() {
		return ability;
	}
	AbilityCard* getAbilityCard() {
		return this;
	}
	string getDescription() {
		string desc = "Ability card: type: ";
		desc += abilityToString(ability);
		return desc;
	}
	AbilityCard(Ability::AbilityType _ability) : ability(_ability) {};
	~AbilityCard() {	};

	ostream& write(ostream& stream)  {
		stream << getDescription() << endl;
		return stream;
	}
	istream& read(istream& stream) {
		cout << "Writing to stream: " << getDescription() << endl;
		return stream;
	}
};

#endif