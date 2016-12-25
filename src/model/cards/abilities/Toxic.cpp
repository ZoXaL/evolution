#include "model/cards/abilities/Toxic.h"
#include "model/cards/abilities/AcuteEyesight.h"
#include "model/cards/AbilityCard.h"
#include "model/cards/Animal.h"
#include "model/cards/interfaces/DefendAbility.h"
#include "controllers/commands/CommandHolder.h"
#include "controllers/commands/KillAnimalCommand.h"
#include <iostream>
#include <string>

Toxic::Toxic() : AbilityCard(Ability::TOXIC, false) {};

bool Toxic::defend(Animal* hunter) {
	CommandHolder::getInstance()->addCommand(new KillAnimalCommand(hunter));
	return false;
}

string Toxic::getStatus() {
	return abilityToString(ability);
}

int Toxic::getCost() {
	return 1;
}

AbilityCard* Toxic::clone() {
	return new Toxic(*this);
}

ostream& Toxic::write(ostream& stream)  {
	stream << ability << ' ' << endl;
	return stream;
}
istream& Toxic::read(istream& stream) {
	cout << "Reading from stream: " << abilityToString(ability) << endl;
	return stream;
}