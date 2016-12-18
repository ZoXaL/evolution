#include "model/GameManager.h"
#include "model/GameModel.h"
#include "model/cards/AbilityCard.h"
#include "model/cards/Card.h"
#include "model/cards/abilities/Fat.h"
#include "model/deck/Deck.h"
#include "controllers/commands/GiveCardToPlayerCommand.h"
#include "controllers/commands/CommandHolder.h"
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
	for (int i = 0; i < 10; i++) {
		if (i%2) {
			shared_ptr<Card> newCard(new Fat());
			cardDeck->push_back(newCard);
		} else {
			shared_ptr<Card> newCard(new Fat());
			cardDeck->push_back(newCard);
		}	
	}

	for (int i = 0; i < GameModel::CARDS_ON_START; i++) {
		CommandHolder::getInstance()->addCommand(new GiveCardToPlayerCommand(0));
	}

	for (int i = 0; i < GameModel::CARDS_ON_START; i++) {
		CommandHolder::getInstance()->addCommand(new GiveCardToPlayerCommand(1));
	}
	return model;
}