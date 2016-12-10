#ifndef ANIMAL_CARD_H
#define ANIMAL_CARD_H
#include <vector>
#include <string>
#include <memory>
using namespace std;

#include "model/cards/Card.h"
#include "model/cards/AbilityCard.h"


class AnimalCard {
	shared_ptr<Card> createdFrom;
	vector<shared_ptr<Card>> abilities;
	bool _isHungry;
	bool _needFood;
public:
	AnimalCard(shared_ptr<Card> createdFrom);
	vector<shared_ptr<Card>>* getAbilities();
	void addAbility(shared_ptr<Card> newAbility);
	string getStatus();

	bool needFood();	// if yes, you can feed it
	bool isHungry();	// if no, animal dies
	int feed();
};

#endif