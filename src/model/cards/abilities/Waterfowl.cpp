#include "model/cards/abilities/Waterfowl.h"
#include "model/cards/AbilityCard.h"
#include "model/cards/Animal.h"
#include "model/cards/interfaces/DefendAbility.h"
#include <iostream>
#include <string>

Waterfowl::Waterfowl() : AbilityCard(Ability::WATERFOWL, false) {};

bool Waterfowl::defend(Animal* hunter) {
	return false;
}

string Waterfowl::getStatus() {
	return abilityToString(ability);
}

int Waterfowl::getCost() {
	return 1;
}

ostream& Waterfowl::write(ostream& stream)  {
	stream << ability << ' ' << endl;
	return stream;
}
istream& Waterfowl::read(istream& stream) {
	cout << "Reading from stream: " << abilityToString(ability) << endl;
	return stream;
}