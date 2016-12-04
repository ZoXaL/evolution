#ifndef ABILITY_CARD_H
#define ABILITY_CARD_H

class Card;

class AbilityCard : public Card {
public:

	enum Ability {
		FAST, FAT
	};
	
private:
Ability ability;

public:
	Ability getAbility() {
		return ability;
	}
	AbilityCard* getAbilityCard() {
		return this;
	}
	AbilityCard(Ability _ability) : ability(_ability) {};
	~AbilityCard() {	};
};

#endif