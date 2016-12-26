#ifndef ANIMAL_CARD_H
#define ANIMAL_CARD_H
#include <vector>
#include <string>
#include <memory>
#include <list>
using namespace std;

#include "model/Player.h"
#include "model/cards/AbilityCard.h"
#include "model/cards/abilities/Ability.h"

class Animal {
	shared_ptr<AbilityCard> createdFrom;
	vector<shared_ptr<AbilityCard>> abilities;
	bool fed;
	Player* owner;
public:
	Animal(shared_ptr<AbilityCard> createdFrom, Player* owner);
	vector<shared_ptr<AbilityCard>>* getAbilities();
	vector<shared_ptr<AbilityCard>> getActiveAbilities();
	bool hasAbility(Ability::AbilityType ability);
	void pushAbility(shared_ptr<AbilityCard> newAbility);
	shared_ptr<AbilityCard> popAbility();
	AbilityCard* getAbility(int index);
	string getStatus();
	int getCost();
	shared_ptr<AbilityCard> getCreatedFrom();

	bool isHungry();	// if no, animal dies
	int feed();
	bool canGetFood();
	bool defend(Animal* hunter);
	void setFed(bool);
	Player* getOwner();
};

#endif