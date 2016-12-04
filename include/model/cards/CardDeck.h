#ifndef CARD_DECK_H
#define CARD_DECK_H
#include <vector>;
using namespace std;

class CardDeck {
vector<Card> deck;
public:
	CardDeck();
	void shuffleDeck();
	Card getCard();
	bool isEmpty();
};

#endif