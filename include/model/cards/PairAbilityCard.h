#ifndef PAIR_ABILITY_CARD_H
#define PAIR_ABILITY_CARD_H

#include "model/AbilityCard.h"

class PairAbilityCard : public AbilityCard {
	
private:
AbilityCard::Ability secondAbility;

public:
	Ability getSecondAbility() {
		return secondAbility;
	}
};

#endif