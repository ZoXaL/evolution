#include "model/cards/Animal.h"
#include "model/cards/abilities/Fat.h"
#include "model/cards/abilities/Ability.h"
#include "model/cards/interfaces/FoodModification.h"
#include "model/cards/interfaces/ActiveAbility.h"
#include "model/cards/interfaces/DefendAbility.h"
#include "exceptions/Exception.h"
#include <memory>
#include <string>
#include <typeinfo>

using namespace std;

Animal::Animal(shared_ptr<AbilityCard> createdFrom, Player* owner) {
	this->createdFrom = createdFrom;
	this->fed = false;
	this->owner = owner;
}
vector<shared_ptr<AbilityCard>>* Animal::getAbilities() {
	return &abilities;
}
Player* Animal::getOwner() {
	return owner;
}
shared_ptr<AbilityCard> Animal::getCreatedFrom() {
	return createdFrom;
}
bool Animal::hasAbility(Ability::AbilityType ability) {
	for (auto ibegin = abilities.begin(); ibegin != abilities.end(); ibegin++) {
		if ((*ibegin)->getAbility() == ability) {
			return true;
		}		
	}
	return false;
}

void Animal::pushAbility(shared_ptr<AbilityCard> newAbility) {
	newAbility->setOwner(this);
	abilities.push_back(newAbility);
}
shared_ptr<AbilityCard> Animal::popAbility() {
	if (abilities.size() == 0) {
		throw Exception("Cannot pop animal ability because there is no one");
	}
	shared_ptr<AbilityCard> abilityToReturn = abilities[abilities.size()-1];
	abilities.pop_back();
	return abilityToReturn;
}

AbilityCard* Animal::getAbility(int index) {
	if (index >= abilities.size() || index < 0) {
		throw Exception("Cannot get ability on illegal index");
	}
	return abilities[index].get();
}

string Animal::getStatus() {
	if (abilities.size() == 0) {
		return "Empty animal";
	}
	string status;
	for (auto ibegin = abilities.begin(); ibegin != abilities.end(); ibegin++) {
		AbilityCard* ability = (*ibegin).get();
		status += ability->getStatus();
		status += " ";
	}
	return status;
}
int Animal::getCost() {
	int totalCost = 3;
	for (auto ibegin = abilities.begin(); ibegin != abilities.end(); ibegin++) {
		totalCost += (*ibegin)->getCost();
	}
	return totalCost;
}

bool Animal::isHungry() {
	if (!fed) return true;
	for (int i = 0; i < abilities.size(); i++) {
		FoodModification* foodModification = dynamic_cast<FoodModification*>(abilities[i].get());
		if (foodModification && foodModification->needFood()) {
			return true;
		}			
	}
	return false;
}

void Animal::setFed(bool newFed) {
	fed = newFed;
}

vector<shared_ptr<AbilityCard>> Animal::getActiveAbilities() {
	vector<shared_ptr<AbilityCard>> activeAbilities;
	for (int i = 0; i < abilities.size(); i++) {
		ActiveAbility* ability = dynamic_cast<ActiveAbility*>(abilities[i].get());
		if (ability && ability->canUse()) {
			activeAbilities.push_back(abilities[i]);
		}			
	}
	return activeAbilities;
}

bool Animal::defend(Animal* hunter) {
	if (hunter->hasAbility(Ability::WATERFOWL) && !this->hasAbility(Ability::WATERFOWL)) {
		return true;
	}
	for (int i = 0; i < abilities.size(); i++) {
		DefendAbility* ability = dynamic_cast<DefendAbility*>(abilities[i].get());
		if (ability && ability->defend(hunter)) {
			return true;
		}			
	}
	return false;
}

bool Animal::canGetFood() {
	if (!fed) return true;
	for (int i = 0; i < abilities.size(); i++) {
		FoodModification* foodModification = dynamic_cast<FoodModification*>(abilities[i].get());
		if (foodModification && foodModification->canGetFood()) {
			return true;
		}			
	}
	return false;
}

int Animal::feed() {
	// -2 if no need food
	// if index = -1, feed animal itself
	// if index > 0, give food to ability
	for (int i = 0; i < abilities.size(); i++) {
		AbilityCard* ability = abilities[i].get();
		FoodModification* foodModification = dynamic_cast<FoodModification*>(ability);
		if (foodModification && foodModification->needFood()) {
			foodModification->giveFood();
			return i;
		}			
	}
	// no ability needs food
	if (!fed) {
		fed = true;
		return -1;
	} 
	for (int i = 0; i < abilities.size(); i++) {
		AbilityCard* ability = abilities[i].get();
		Fat* fat = dynamic_cast<Fat*>(ability);
		if (fat && fat->canGetFood()) {
			fat->giveFood();
			return i;
		}	
	}
	return -2;
}