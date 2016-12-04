#ifndef CARD_H
#define CARD_H

class AbilityCard;

class Card {
public:
	virtual ~Card() {};
	virtual AbilityCard* getAbilityCard() = 0;
};

#endif