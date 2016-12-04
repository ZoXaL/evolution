#ifndef CARD_H
#define CARD_H
#include "model/cards/AbilityCard"

class Card {
AbilityCard abilityCard;
public:
	AbilityCard getAbilityCard() {
		return abilityCard;
	}
};

#endif