#include "model/cards/AnimalCard.h"
#include <memory>

using namespace std;

AnimalCard::AnimalCard(shared_ptr<Card> createdFrom) {
	this->createdFrom = createdFrom;
}
vector<shared_ptr<AbilityCard>>* AnimalCard::getAbilities() {
	return &abilities;
}

void AnimalCard::addAbility(shared_ptr<AbilityCard> newAbility) {
	abilities.push_back(newAbility);
}