#ifndef ANIMAL_CARD_H
#define ANIMAL_CARD_H
#include <vector>
#include <memory>
using namespace std;

#include "model/cards/Card.h"
#include "model/cards/AbilityCard.h"


class AnimalCard {
	shared_ptr<Card> createdFrom;
	vector<shared_ptr<AbilityCard>> abilities;
public:
	AnimalCard(shared_ptr<Card> createdFrom);
	vector<shared_ptr<AbilityCard>>* getAbilities();
	void addAbility(shared_ptr<AbilityCard> newAbility);
};

#endif