#ifndef PLAYER_H
#define PLAYER_H

#include <vector> 
#include <memory>
using namespace std;

class AbilityCard;
class Animal;

class Player {
	vector<shared_ptr<AbilityCard>> hand;
	vector<shared_ptr<Animal>> animals;
	char name[80];
	bool passed;
public:
	Player(const char* name = "NoName");
	const char* getName();
	void setName(const char*);
	
	void pass();
	bool isPassed();
	void clearPassed();	

	shared_ptr<AbilityCard> getCardFromHand(int cardId);
	void addCardToHand(shared_ptr<AbilityCard> ability, int index);
	void pushCardToHand(shared_ptr<AbilityCard>);
	shared_ptr<AbilityCard> popCardFromHand();
	shared_ptr<AbilityCard> removeCardFromHand(int cardId);

	shared_ptr<Animal> getAnimal(int animalId);
	vector<shared_ptr<Animal>>* getAnimals();
	void addAnimal(shared_ptr<Animal>);
	void addAnimal(shared_ptr<Animal>, int index);
	shared_ptr<Animal> deleteAnimal(int);

	int handSize();
	int animalsCount();
	int getScore();
};

#endif