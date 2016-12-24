#ifndef ANIMAL_CARD_H
#define ANIMAL_CARD_H
#include <vector>
#include <string>
#include <memory>
#include <list>
using namespace std;

#include "model/Player.h"
#include "model/cards/AbilityCard.h"

class Animal {
	shared_ptr<AbilityCard> createdFrom;
	vector<shared_ptr<AbilityCard>> abilities;
	bool fed;
	Player* owner;
public:
	Animal(shared_ptr<AbilityCard> createdFrom, Player* owner);
	vector<shared_ptr<AbilityCard>>* getAbilities();
	void pushAbility(shared_ptr<AbilityCard> newAbility);
	shared_ptr<AbilityCard> popAbility();
	AbilityCard* getAbility(int index);
	string getStatus();
	int getCost();
	shared_ptr<AbilityCard> getCreatedFrom();

	bool isHungry();	// if no, animal dies
	int feed();
	bool canGetFood();
	// list<pair<int, shared_ptr<AbilityCard>>> getAbilitiesToFeed();
	void setFed(bool);
	Player* getOwner();
};

#endif