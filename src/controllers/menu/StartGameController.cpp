#include "controllers/menu/StartGameController.h"
#include "controllers/menu/MenuController.h"
#include "controllers/game/GameController.h"
#include "controllers/AbstractController.h"

#include "model/GameModel.h"
#include "model/GameManager.h"
#include "model/Player.h"
#include "model/deck/Deck.h"

#include <iostream>
using namespace std;

StartGameController::StartGameController(bool newGame) {
	this->newGame = newGame;
}

AbstractController* StartGameController::run() {
	if (newGame) {
		cout << "Enter first player name: " << endl;
		char firstPlayerName[80];
		cin >> firstPlayerName;

		cout << "Enter second player name: " << endl;
		char secondPlayerName[80];
		cin >> secondPlayerName;
		
		GameManager::buildGame(firstPlayerName, secondPlayerName);
	} else if (GameModel::getInstance() == nullptr) {
		cout << "Game hasn't been started" << endl;
		return new MenuController();
	}
	return new GameController();
}
