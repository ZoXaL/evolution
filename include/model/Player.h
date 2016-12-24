#ifndef PLAYER_H
#define PLAYER_H

#include <vector> 
#include <memory>
using namespace std;

class AbilityCard;
class AnimalCard;

class Player {
	vector<shared_ptr<AbilityCard>> hand;
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

	shared_ptr<AbilityCard> getCardFromHand(int cardId);
	void addCardToHand(shared_ptr<AbilityCard> ability, int index);
	void pushCardToHand(shared_ptr<AbilityCard>);
	shared_ptr<AbilityCard> popCardFromHand();
	shared_ptr<AbilityCard> removeCardFromHand(int cardId);

	shared_ptr<AnimalCard> getAnimal(int animalId);
	vector<shared_ptr<AnimalCard>>* getAnimals();
	void addAnimal(shared_ptr<AnimalCard>);
	void addAnimal(shared_ptr<AnimalCard>, int index);
	shared_ptr<AnimalCard> deleteAnimal(int);

	int handSize();
	int animalsCount();
	int getScore();
};

#endif