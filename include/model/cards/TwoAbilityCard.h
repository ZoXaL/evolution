#ifndef TWO_ABILITY_CARD_H
#define TWO_ABILITY_CARD_H

using namespace std;

class TwoAbilityCard : public Card{
AbilityCard secondAbilityCard;
public:
	AbilityCard getsecondAbilityCard() {
		return secondAbilityCard;
	}
};

#endif