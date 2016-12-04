#ifndef CARD_DECK_H
#define CARD_DECK_H

#include <vector>
#include "model/cards/Card.h"
using namespace std;

class CardDeck {
vector<Card*> deck;
vector<Card*>::iterator currentCard;
public:
	CardDeck();
	~CardDeck();
	Card* getCard();
	bool isEmpty();
};

#endif