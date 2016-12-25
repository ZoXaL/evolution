#include "model/cards/abilities/Fast.h"
#include "model/cards/AbilityCard.h"
#include "model/cards/Animal.h"
#include "model/cards/interfaces/DefendAbility.h"
#include <iostream>
#include <string>
#include <stdlib.h>

Fast::Fast() : AbilityCard(Ability::FAST, false) {};

bool Fast::defend(Animal* hunter) {
	vector<shared_ptr<AbilityCard>>* hunterAbilities = hunter->getAbilities();
	for (auto i = hunterAbilities->begin(); i != hunterAbilities->end(); i++) {
		Fast* fast = dynamic_cast<Fast*>(i->get());
		if (fast) {
			return (rand()%3==0);
		}
	}
	return (rand()%2==0);
}

string Fast::getStatus() {
	return abilityToString(ability);
}

int Fast::getCost() {
	return 1;
}

AbilityCard* Fast::clone() {
	return new Fast(*this);
}

ostream& Fast::write(ostream& stream)  {
	stream << ability << ' ' << endl;
	return stream;
}
istream& Fast::read(istream& stream) {
	cout << "Reading from stream: " << abilityToString(ability) << endl;
	return stream;
}