#include "model/Player.h"
#include "model/cards/Card.h"
#include "exceptions/Exception.h"
#include "exceptions/DeckException.h"
#include <string.h>
#include "functions.h"

Player::Player(const char* name) {
	strcpy(this->name, name);
	passed = false;
}

const char* Player::getName() {
	return this->name;
}

void Player::setName(const char* name) {
	strcpy(this->name, name);
}

void Player::pushCardToHand(shared_ptr<AbilityCard> card) {
	this->hand.push_back(card);
}
shared_ptr<AbilityCard> Player::removeCardFromHand(int cardNum) {
	if(!checkRange(cardNum, 0, hand.size()-1)) {
		throw DeckException("Player::removeCardFromHand -- cardNum is greater then hand size or less then 0");
	}
	shared_ptr<AbilityCard> returnCard = hand[cardNum];
	hand.erase(hand.begin() + cardNum);
	return returnCard;
}
void Player::addCardToHand(shared_ptr<AbilityCard> ability, int index) {
	hand.insert(hand.begin()+index, ability);
}


shared_ptr<AbilityCard> Player::popCardFromHand() {
	if(hand.size() == 0) {
		throw DeckException("Player::popCardFromHand -- hand is empty");
	}
	auto returnCardIt = hand.begin()+hand.size()-1;
	shared_ptr<AbilityCard> returnCard = *returnCardIt;
	hand.pop_back();
	return returnCard;
}
shared_ptr<AbilityCard> Player::getCardFromHand(int cardNum) {
	if(!checkRange(cardNum, 0, hand.size())) {
		throw DeckException("Player::getCardFromHand -- cardNum is greater then hand size or less then 0");
	}
	return hand[cardNum];
}

int Player::handSize() {
	return hand.size();
}
vector<shared_ptr<Animal>>* Player::getAnimals() {
	return &animals;
}
vector<shared_ptr<Animal>> Player::getAnimalsToEvolve(AbilityCard* ability) {
	vector<shared_ptr<Animal>> animalsToEvolve;
	for (auto i = animals.begin(); i != animals.end(); i++) {
		if ((*i)->hasAbility(ability->getAbility()) && !ability->canDuplicate()) {
			continue;
		}
		animalsToEvolve.push_back(*i);
	}
	return animalsToEvolve;
}
void Player::addAnimal(shared_ptr<Animal> newAnimal) {
	animals.push_back(newAnimal);
}
void Player::addAnimal(shared_ptr<Animal> animal, int index) {
	animals.insert(animals.begin()+index, animal);
}
shared_ptr<Animal> Player::deleteAnimal(int animalNum) {
	if(!checkRange(animalNum, 0, animals.size())) {
		throw DeckException("Player::deleteAnimal -- animalNum is greater then animals count or less then 0");
	}
	shared_ptr<Animal> returnAnimal;
	if (animalNum == 0) {
		auto returnAnimalIt = animals.begin();
		returnAnimal = *returnAnimalIt;
		animals.erase(returnAnimalIt);
	} else {
		auto returnAnimalIt = animals.begin()+animalNum;
		returnAnimal = *returnAnimalIt;
		animals.erase(returnAnimalIt);		
	}	
	return returnAnimal;
}

shared_ptr<Animal> Player::getAnimal(int animalNum) {
	if(!checkRange(animalNum, 0, animals.size())) {
		throw DeckException("Cannot get animal from player: no animal with num "+to_string(animalNum));
	}
	return animals[animalNum];
}

int Player::animalsCount() {
	return animals.size();
}

void Player::pass() {
	passed = true;
}
bool Player::isPassed() {
	return passed;
}
void Player::clearPassed() {
	passed = false;
}
int Player::getScore() {
	int totalScore = 0;
	for (auto ibegin = animals.begin(); ibegin != animals.end(); ibegin++) {
		totalScore += (*ibegin)->getCost();
	}
	return totalScore;
}