#include "model/cards/abilities/AcuteEyesight.h"
#include "model/cards/AbilityCard.h"
#include "model/cards/Animal.h"
#include <iostream>
#include <string>

AcuteEyesight::AcuteEyesight() : AbilityCard(Ability::ACUTE_EYESIGHT, false) {};

string AcuteEyesight::getStatus() {
	return abilityToString(ability);
}

int AcuteEyesight::getCost() {
	return 1;
}

AbilityCard* AcuteEyesight::clone() {
	return new AcuteEyesight(*this);
}

ostream& AcuteEyesight::write(ostream& stream)  {
	stream << ability << ' ' << endl;
	return stream;
}
istream& AcuteEyesight::read(istream& stream) {
	cout << "Reading from stream: " << abilityToString(ability) << endl;
	return stream;
}