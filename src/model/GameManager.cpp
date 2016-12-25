#include "model/GameManager.h"
#include "model/GameModel.h"
#include "model/cards/AbilityCard.h"
#include "model/cards/Card.h"
#include "model/cards/abilities/Fat.h"
#include "model/cards/abilities/Waterfowl.h"
#include "model/cards/abilities/Hunter.h"
#include "model/cards/abilities/Grant.h"
#include "model/cards/abilities/Fast.h"
#include "model/cards/abilities/Ability.h"
#include "model/deck/Deck.h"
#include "controllers/commands/GiveCardToPlayerCommand.h"
#include "controllers/commands/CommandHolder.h"
#include "exceptions/Exception.h"
#include <memory>
#include <fstream>
#include <string.h>
#include <algorithm>
using namespace std;

bool GameManager::gameInitialized = false;
list<AbilityCard*> GameManager::startDeck;

GameModel* GameManager::buildGame(const char* firstPlayerName, const char* secondPlayerName) {
	gameInitialized = true;
	GameModel* model = GameModel::initialize();

	Player* player1 = model->getPlayer(0);
	Player* player2 = model->getPlayer(1);

	player1->setName(firstPlayerName);
	player2->setName(secondPlayerName);

	Deck<shared_ptr<AbilityCard>>* cardDeck = model->getCardDeck();
	startDeck.clear();
	// for (int i = 0; i < 5; i++) {
	// 	shared_ptr<AbilityCard> newCard(new Fat());
	// 	cardDeck->push_back(newCard);
	// }
	// for (int i = 0; i < 5; i++) {
	// 	shared_ptr<AbilityCard> newCard(new Waterfowl());
	// 	cardDeck->push_back(newCard);
	// }
	for (int i = 0; i < 10; i++) {
		shared_ptr<AbilityCard> newCard(new Hunter());
		cardDeck->push_back(newCard);
	}
	// for (int i = 0; i < 5; i++) {
	// 	shared_ptr<AbilityCard> newCard(new Grant());
	// 	cardDeck->push_back(newCard);
	// }
	for (int i = 0; i < 10; i++) {
		shared_ptr<AbilityCard> newCard(new Fast());
		cardDeck->push_back(newCard);
	}
	cardDeck->shuffle();
	for (auto i = cardDeck->begin(); i != cardDeck->end(); i++) {
		startDeck.push_back((*i)->clone());
	}
	startDeck.push_back((*(cardDeck->end()))->clone());
	giveCardsToPlayers(model->getCardDeck());
	return model;
}

void GameManager::saveGame(fstream& stream) {
	if (!gameInitialized) {
		throw Exception("Game is not initialized");
	}
	GameModel* model = GameModel::getInstance();
	Player* player1 = model->getPlayer(0);
	Player* player2 = model->getPlayer(1);
	Deck<shared_ptr<AbilityCard>>* cardDeck = model->getCardDeck();

	stream << player1->getName() << ' ';
	stream << player2->getName() << endl;
	stream << startDeck.size() << endl;
	for (auto it = startDeck.begin(); it != startDeck.end(); it++) {
		(*it)->write(stream);
	}
	CommandHolder::getInstance()->write(stream);
}

GameModel* GameManager::loadGame(fstream& stream) {
	cout << "Loading game ..." << endl;

	GameModel* model = GameModel::initialize();	
	Player* player1 = model->getPlayer(0);
	Player* player2 = model->getPlayer(1);
	Deck<shared_ptr<AbilityCard>>* cardDeck = model->getCardDeck();

	char firstPlayerName[80];
	char secondPlayerName[80];
	stream >> firstPlayerName;
	stream >> secondPlayerName;
	player1->setName(firstPlayerName);
	player2->setName(secondPlayerName);
	//Reading card deck
	int deckSize;
	stream >> deckSize;
	startDeck.clear();
	for (int i = 0; i< deckSize; i++) {
		shared_ptr<AbilityCard> newCard = AbilityCard::readFromFile(stream);
		cardDeck->push_back(newCard);
		startDeck.push_back(newCard.get()->clone());
	}
	giveCardsToPlayers(model->getCardDeck());
	// cardDeck->read(stream);
	CommandHolder::getInstance()->read(stream);
	gameInitialized = true;
	return model;
}

bool GameManager::isGameInitilized() {
	return gameInitialized;
}

void GameManager::giveCardsToPlayers(Deck<shared_ptr<AbilityCard>>* cardDeck) {
	for (int i = 0; i < GameModel::CARDS_ON_START; i++) {
		GiveCardToPlayerCommand giveCard(0);
		giveCard.execute();
	}

	for (int i = 0; i < GameModel::CARDS_ON_START; i++) {
		GiveCardToPlayerCommand giveCard(1);
		giveCard.execute();
	}
}