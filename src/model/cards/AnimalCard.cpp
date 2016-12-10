#include "model/cards/AnimalCard.h"
#include <memory>
#include <string>

using namespace std;

AnimalCard::AnimalCard(shared_ptr<Card> createdFrom) {
	this->createdFrom = createdFrom;
}
vector<shared_ptr<Card>>* AnimalCard::getAbilities() {
	return &abilities;
}

void AnimalCard::addAbility(shared_ptr<Card> newAbility) {
	abilities.push_back(newAbility);
}

string AnimalCard::getStatus() {
	if (abilities.size() == 0) {
		return "Empty animal";
	}
	string status;
	for (auto ibegin = abilities.begin(); ibegin != abilities.end(); ibegin++) {
		shared_ptr<Card> card = (*ibegin);
		AbilityCard* ability = card->getAbilityCard();
		status += ability->getStatus();
	}
	return status;
}