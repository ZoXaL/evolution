#ifndef ANIMAL_CARD_H
#define ANIMAL_CARD_H
#include <vector>
#include <string>
#include <memory>
using namespace std;

#include "model/Player.h"
#include "model/cards/AbilityCard.h"

class Animal {
	shared_ptr<AbilityCard> createdFrom;
	vector<shared_ptr<AbilityCard>> abilities;
	bool _isHungry;
	bool _needFood;
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

	bool needFood();	// if yes, you can feed it
	bool isHungry();	// if no, animal dies
	int feed();
	void setHungry(bool);
	void setNeedFood(bool);
	Player* getOwner();
};

#endif