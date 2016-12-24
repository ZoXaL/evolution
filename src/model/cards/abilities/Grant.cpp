#include "model/cards/AbilityCard.h"
#include "model/cards/abilities/Grant.h"
#include "exceptions/Exception.h"
#include <iostream>
#include <string>

Grant::Grant() : AbilityCard(Ability::GRANT, false) {};

bool Grant::needFood() {
	return !reserve;
}
bool Grant::canGetFood() {
	return !reserve;
}

void Grant::resetFood() {
	reserve = false;
}
void Grant::decreaseFood() {
	reserve = false;
}

void Grant::giveFood() {
	if (reserve) {
		throw Exception("Cannot fill full reserve for Grant ability");
	}
	reserve = true;
}

bool Grant::defend(Animal* hunter) {
	vector<shared_ptr<AbilityCard>>* hunterAbilities = hunter->getAbilities();
	for (auto i = hunterAbilities->begin(); i != hunterAbilities->end(); i++) {
		Grant* waterfowl = dynamic_cast<Grant*>(i->get());
		if (waterfowl) {
			return false;
		}
	}
	return true;
}

string Grant::getStatus() {
	string status = abilityToString(ability);
	status += "(";
	status += (reserve)? "f" : "e";
	status += ")";
	return status;
}

int Grant::getCost() {
	return (reserve) ? 2 : 1;
}

AbilityCard* Grant::clone() {
	return new Grant(*this);
}

ostream& Grant::write(ostream& stream)  {
	stream << ability << ' ' << reserve << endl;
	return stream;
}
istream& Grant::read(istream& stream) {
	cout << "Reading from stream: " << abilityToString(ability) << endl;
	stream >> reserve;
	return stream;
}