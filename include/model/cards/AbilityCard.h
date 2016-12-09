#ifndef ABILITY_CARD_H
#define ABILITY_CARD_H

#include <string>
#include <iostream>
using namespace std;
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
	string getDescription() {
		string desc = "Ability card: type: ";
		desc += std::to_string(ability);;
		return desc;
	}
	AbilityCard(Ability _ability) : ability(_ability) {};
	~AbilityCard() {	};

	ostream& write(ostream& stream)  {
		stream << getDescription() << endl;
		return stream;
	}
	istream& read(istream& stream) {
		cout << "Writing to stream: " << getDescription() << endl;
		return stream;
	}
};

#endif