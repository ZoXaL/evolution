#ifndef ANIMAL_CARD_H
#define ANIMAL_CARD_H
#include <vector>
#include <string>
#include <memory>
using namespace std;

#include "model/cards/Card.h"
#include "model/Player.h"
#include "model/cards/AbilityCard.h"


class AnimalCard {
	shared_ptr<Card> createdFrom;
	vector<shared_ptr<AbilityCard>> abilities;
	bool _isHungry;
	bool _needFood;
	Player* owner;
public:
	AnimalCard(shared_ptr<Card> createdFrom, Player* owner);
	vector<shared_ptr<AbilityCard>>* getAbilities();
	void addAbility(shared_ptr<AbilityCard> newAbility);
	AbilityCard* getAbility(int index);
	string getStatus();
	int getCost();

	bool needFood();	// if yes, you can feed it
	bool isHungry();	// if no, animal dies
	int feed();
	void clearHungry();
	Player* getOwner();
};

#endif