#ifndef PLAYER_H
#define PLAYER_H

#include "model/cards/Card.h"
#include "model/cards/AnimalCard.h"
#include <vector> 
#include <memory>
using namespace std;

class Player {
	vector<shared_ptr<Card>> hand;
	vector<shared_ptr<AnimalCard>> animals;
	char name[80];
	bool passed;
public:
	Player(const char* name = "NoName");
	const char* getName();
	void setName(const char*);
	
	void pass();
	bool isPassed();
	void clearPassed();

	shared_ptr<AnimalCard> getAnimal(int animalId);
	vector<shared_ptr<AnimalCard>>* getAnimals();

	shared_ptr<Card> getCardFromHand(int cardId);
	void pushCardToHand(shared_ptr<Card>);
	shared_ptr<Card> popCardFromHand();
	shared_ptr<Card> removeCardFromHand(int cardId);


	void addAnimal(shared_ptr<AnimalCard>);

	int handSize();
	int animalsCount();
};

#endif