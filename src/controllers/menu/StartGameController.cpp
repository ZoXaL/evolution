#include "controllers/menu/StartGameController.h"
#include "controllers/menu/MenuController.h"
#include "controllers/game/GameController.h"
#include "controllers/AbstractController.h"

#include "model/GameModel.h"
#include "model/Player.h"
#include "model/deck/Deck.h"

#include <iostream>
using namespace std;

StartGameController::StartGameController(bool newGame) {
	this->newGame = newGame;
}

AbstractController* StartGameController::run() {
	if (newGame) {
		initGameModel();
		initPlayers();
	} else if (GameModel::getInstance() == nullptr) {
		cout << "Game hasn't been started" << endl;
		return new MenuController();
	}
	return new GameController();
}

void StartGameController::initGameModel() {
	GameModel::initialize();
}

void StartGameController::initPlayers() {
	GameModel* model = GameModel::getInstance();
	Deck<Card*>* cardDeck = model->getCardDeck();
	// Name initializing
	Player* player1 = model->getPlayer(0);
	cout << "Enter first player name: " << endl;
	char firstName[80];
	cin >> firstName;
	player1->setName(firstName);
	// Hand initializing
	for (int i = 0; i < GameModel::CARDS_ON_START; i++) {
		player1->addCardToHand(cardDeck->getCard());
	}
	
	// Name initializing
	Player* player2 = model->getPlayer(1);
	cout << "Enter second player name: " << endl;
	char secondName[80];
	cin >> secondName;
	player2->setName(secondName);
	// Hand initializing
	for (int i = 0; i < GameModel::CARDS_ON_START; i++) {
		player2->addCardToHand(cardDeck->getCard());
	}

}