#include "model/cards/AbilityCard.h"
#include "model/cards/abilities/Fat.h"
#include "model/cards/abilities/Hunter.h"
#include "model/cards/abilities/Waterfowl.h"
#include "model/cards/abilities/Grant.h"
#include "model/cards/abilities/Fast.h"
#include "model/cards/abilities/Camouflage.h"
#include "model/cards/abilities/AcuteEyesight.h"
#include "model/cards/abilities/Toxic.h"
#include "model/cards/abilities/Ability.h"
#include "exceptions/Exception.h"
#include "functions.h"
#include <string>
using namespace std;

AbilityCard::AbilityCard(Ability::AbilityType _ability, bool _duplicated) : ability(_ability) {
	this->duplicated = _duplicated;
};

Ability::AbilityType AbilityCard::getAbility() {
	return ability;
}
string AbilityCard::getDescription() {
	return abilityToString(ability);
}

bool AbilityCard::canDuplicate() {
	return this->duplicated;
}

AbilityCard* AbilityCard::getAbilityCard() {
	return this;
}
void AbilityCard::setOwner(Animal* owner) {
	this->owner = owner;
}
Animal* AbilityCard::getOwner() {
	return owner;
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
		case (Ability::HUNTER) : {
			abilityToReturn = new Hunter();
			abilityToReturn->read(stream);
			break;
		}
		case (Ability::WATERFOWL) : {
			abilityToReturn = new Waterfowl();
			abilityToReturn->read(stream);
			break;
		}
		case (Ability::GRANT) : {
			abilityToReturn = new Grant();
			abilityToReturn->read(stream);
			break;
		}
		case (Ability::FAST) : {
			abilityToReturn = new Fast();
			abilityToReturn->read(stream);
			break;
		}
		case (Ability::ACUTE_EYESIGHT) : {
			abilityToReturn = new AcuteEyesight();
			abilityToReturn->read(stream);
			break;
		}
		case (Ability::CAMOUFLAGE) : {
			abilityToReturn = new Camouflage();
			abilityToReturn->read(stream);
			break;
		}
		case (Ability::TOXIC) : {
			abilityToReturn = new Toxic();
			abilityToReturn->read(stream);
			break;
		}
		default : {
			throw Exception("AbilityCard::readFromFile -- unexpected ability type");
		}
	}
	return shared_ptr<AbilityCard>(abilityToReturn);
}