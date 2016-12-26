#ifndef ABILITY_CARD_H
#define ABILITY_CARD_H

#include <string>
#include <iostream>
#include <memory>
#include "model/cards/Animal.h"
#include "model/cards/abilities/Ability.h"
#include "interfaces/Prototype.h"
#include "functions.h"
using namespace std;

class AbilityCard : public Prototype<AbilityCard*> {
protected:
	Ability::AbilityType ability;
	bool duplicated;
	Animal* owner;
public:
	AbilityCard(Ability::AbilityType, bool duplicated);

	Ability::AbilityType getAbility();	

	string getDescription();
	AbilityCard* getAbilityCard();

	virtual ostream& write(ostream&) = 0;
	virtual istream& read(istream&) = 0;

	bool canDuplicate();
	
	virtual int getCost() = 0;

	void setOwner(Animal* owner);
	Animal* getOwner();

	virtual string getStatus() = 0;
	static shared_ptr<AbilityCard> readFromFile(istream&);
};

#endif