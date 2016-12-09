#include "model/cards/AbilityCard.h"
#include "model/cards/abilities/Ability.h"

AbilityCard::AbilityCard(Ability::AbilityType _ability) : ability(_ability) {};

Ability::AbilityType AbilityCard::getAbility() {
	return ability;
}
string AbilityCard::getDescription() {
	return abilityToString(ability);
}