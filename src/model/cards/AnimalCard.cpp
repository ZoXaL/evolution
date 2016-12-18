#include "model/cards/AnimalCard.h"
#include "model/cards/abilities/Fat.h"
#include "model/cards/abilities/Ability.h"
#include "model/cards/interfaces/FoodModification.h"
#include <memory>
#include <string>
#include <typeinfo>

using namespace std;

AnimalCard::AnimalCard(shared_ptr<Card> createdFrom) {
	this->createdFrom = createdFrom;
	this->_isHungry = true;
	this->_needFood = true;
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
		status += " ";
	}
	return status;
}
int AnimalCard::getCost() {
	int totalCost = 3;
	for (auto ibegin = abilities.begin(); ibegin != abilities.end(); ibegin++) {
		totalCost += (*ibegin)->getCost();
	}
	return totalCost;
}

bool AnimalCard::needFood() {
	return _needFood;
}
bool AnimalCard::isHungry() {
	return _isHungry;
}
void AnimalCard::clearHungry() {
	this->_isHungry = true;
	this->_needFood = true;
}

int AnimalCard::feed() {
	bool abilitiesNeedFood = false;
	int abilityToFeed = -1;
	for (int i = 0; i < abilities.size(); i++) {
		shared_ptr<Card> card = abilities[i];
		AbilityCard* ability = card->getAbilityCard();
		// 2) check if ability needs food
		switch (ability->getAbility()) {
			case (Ability::FAT) : {
				// feed fat only if animal is not hungry				
				Fat* fatCard = (Fat*)ability;
				// feed only if fat is empty
				if (fatCard->needFood()) {
					if (!this->_isHungry) {	// if animal is hungry, you cannot fill fat
						if (abilityToFeed != -1) {	// some fat has been filled earlier
							abilitiesNeedFood = true;	// mark that there is empty fat
							break;
						}
						fatCard->giveFood();
						abilityToFeed = i;
					} else {
						abilitiesNeedFood = true;//mark that there is empty fat
					}		
				}
				break;
			}
		}		
	}
	// no ability needs food
	if (abilityToFeed == -1) {
		_isHungry = false;
	} 
	if (!abilitiesNeedFood) {
		_needFood = false;
	}
	return -1;
}