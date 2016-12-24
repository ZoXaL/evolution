#include "model/cards/AbilityCard.h"
#include "model/cards/abilities/Fat.h"
#include "model/cards/abilities/Ability.h"
#include "exceptions/Exception.h"
#include "functions.h"
#include <string>
using namespace std;

AbilityCard::AbilityCard(Ability::AbilityType _ability, bool _duplicated, bool _passive) : ability(_ability) {
	this->duplicated = duplicated;
	this->passive = passive;
};

Ability::AbilityType AbilityCard::getAbility() {
	return ability;
}
string AbilityCard::getDescription() {
	return abilityToString(ability);
}

bool AbilityCard::isDuplicated() {
	return this->duplicated;
}
bool AbilityCard::isPassive() {
	return this->passive;
}
AbilityCard* AbilityCard::getAbilityCard() {
	return this;
}
void AbilityCard::setOwner(Animal* owner) {
	this->owner = owner;
}

shared_ptr<AbilityCard> AbilityCard::readFromFile(istream& stream) {
	Ability::AbilityType type;
	AbilityCard* abilityToReturn;
	int ability;
	stream >> ability;
	switch (ability) {
		case (Ability::FAT) : {
			abilityToReturn = new Fat();
			abilityToReturn->read(stream);
			break;
		}
		default : {
			throw Exception("AbilityCard::readFromFile -- unexpected ability type");
		}
	}
	return shared_ptr<AbilityCard>(abilityToReturn);
}