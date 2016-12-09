#ifndef PLAYER_H
#define PLAYER_H

#include "model/cards/Card.h"
//#include "model/cards/AnimalCard.h"
#include <vector> 
#include <memory>
using namespace std;

class Player {
	vector<shared_ptr<Card>> hand;
	//vector<AnimalCard> animals;
	char name[80];
public:
	Player(const char* name = "NoName");
	const char* getName();
	void setName(const char*);
	void addCardToHand(shared_ptr<Card>);
	shared_ptr<Card> removeCardFromHand(int);
	shared_ptr<Card> getCard(int);
	int handSize();
};

#endif