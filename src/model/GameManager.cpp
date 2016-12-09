#include "model/GameManager.h"
#include "model/GameModel.h"
#include "model/cards/AbilityCard.h"
#include "model/cards/Card.h"
#include "model/deck/Deck.h"
#include "memory"
using namespace std;

GameModel* GameManager::buildGame(const char* firstPlayerName, const char* secondPlayerName) {
	GameModel* model = GameModel::initialize();

	Player* player1 = model->getPlayer(0);
	Player* player2 = model->getPlayer(1);

	player1->setName(firstPlayerName);
	player2->setName(secondPlayerName);

	Deck<shared_ptr<Card>>* cardDeck = model->getCardDeck();
	// Create all cards and fill the cardDeck
	for (int i = 0; i < 20; i++) {
		if (i%2) {
			shared_ptr<Card> newCard(new AbilityCard(AbilityCard::Ability::FAT));
			cardDeck->push_back(newCard);
		} else {
			shared_ptr<Card> newCard(new AbilityCard(AbilityCard::Ability::FAST));
			cardDeck->push_back(newCard);
		}	
	}

// 	cout << "Enter first player name: " << endl;
// 	char firstName[80];
// 	cin >> firstName;
// 	player1->setName(firstName);
// 	// Hand initializing
	for (int i = 0; i < GameModel::CARDS_ON_START; i++) {
		player1->addCardToHand(cardDeck->pop_front());
	}
	
// 	// Name initializing
// 	
// 	cout << "Enter second player name: " << endl;
// 	char secondName[80];
// 	cin >> secondName;
// 	player2->setName(secondName);
// 	// Hand initializing
	for (int i = 0; i < GameModel::CARDS_ON_START; i++) {
		player2->addCardToHand(cardDeck->pop_front());
	}
	return model;
}