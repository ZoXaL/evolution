#ifndef ABILITY_CARD_H
#define ABILITY_CARD_H


class AbilityCard {
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
};

#endif