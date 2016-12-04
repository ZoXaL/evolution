#include "model/cards/CardDeck.h"
#include "model/cards/AbilityCard.h"

#include <algorithm>  
#include <random>
#include <chrono>


CardDeck::CardDeck() {
	for (int i = 0; i < 10; i++) {
		Card* card = new AbilityCard(AbilityCard::Ability::FAT);
		deck.push_back(card);
	}
	for (int i = 0; i < 10; i++) {
		Card* card = new AbilityCard(AbilityCard::Ability::FAST);
		deck.push_back(card);
	}	
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
	currentCard = deck.begin();
}

CardDeck::~CardDeck() {
	for (auto it = deck.begin(); it != deck.end(); it++) {
		delete *it;
	}
	deck.clear();
}

Card* CardDeck::getCard() {
	return *(currentCard++);
}

bool CardDeck::isEmpty() {
	return currentCard == deck.end();
}