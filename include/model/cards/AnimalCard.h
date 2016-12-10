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
public:
	AnimalCard(shared_ptr<Card> createdFrom);
	vector<shared_ptr<Card>>* getAbilities();
	void addAbility(shared_ptr<Card> newAbility);
	string getStatus();
};

#endif