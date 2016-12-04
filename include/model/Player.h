#ifndef PLAYER_H
#define PLAYER_H

//#include "model/cards/Card.h"
//#include "model/cards/AnimalCard.h"
//#include <vector> 
using namespace std;

class Player {
	//vector<Card> hand;
	//vector<AnimalCard> animals;
	char name[80];
public:
	Player(const char* name = "NoName");
	const char* getName();
	void setName(const char*);
};

#endif