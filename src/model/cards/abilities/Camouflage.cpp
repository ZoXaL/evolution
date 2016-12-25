#include "model/cards/abilities/Camouflage.h"
#include "model/cards/abilities/AcuteEyesight.h"
#include "model/cards/AbilityCard.h"
#include "model/cards/Animal.h"
#include "model/cards/interfaces/DefendAbility.h"
#include <iostream>
#include <string>

Camouflage::Camouflage() : AbilityCard(Ability::CAMOUFLAGE, false) {};

bool Camouflage::defend(Animal* hunter) {
	vector<shared_ptr<AbilityCard>>* hunterAbilities = hunter->getAbilities();
	for (auto i = hunterAbilities->begin(); i != hunterAbilities->end(); i++) {
		AcuteEyesight* acuteEyesight = dynamic_cast<AcuteEyesight*>(i->get());
		if (acuteEyesight) {
			return false;
		}
	}
	return true;
}

string Camouflage::getStatus() {
	return abilityToString(ability);
}

int Camouflage::getCost() {
	return 1;
}

AbilityCard* Camouflage::clone() {
	return new Camouflage(*this);
}

ostream& Camouflage::write(ostream& stream)  {
	stream << ability << ' ' << endl;
	return stream;
}
istream& Camouflage::read(istream& stream) {
	cout << "Reading from stream: " << abilityToString(ability) << endl;
	return stream;
}