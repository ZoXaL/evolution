#include "model/cards/AbilityCard.h"
#include "model/cards/abilities/Ability.h"

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
void AbilityCard::setOwner(AnimalCard* owner) {
	this->owner = owner;
}