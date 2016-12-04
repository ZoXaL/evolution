#include "controllers/menu/StartGameController.h"
#include "controllers/game/GameController.h"
#include "controllers/AbstractController.h"

#include "model/GameModel.h"
#include "model/Player.h"

#include <iostream>
using namespace std;

StartGameController::StartGameController(bool newGame) {
	this->newGame = newGame;
}

AbstractController* StartGameController::run() {
	if (newGame) {
		initGameModel();
		initPlayers();
	}
	return new GameController();
}

void StartGameController::initGameModel() {
	GameModel::initialize();
}

void StartGameController::initPlayers() {
	GameModel* model = GameModel::getInstance();

	cout << "Enter first player name: " << endl;
	char firstName[80];
	cin >> firstName;
	model->getPlayer(0)->setName(firstName);

	cout << "Enter second player name: " << endl;
	char secondName[80];
	cin >> secondName;
	model->getPlayer(1)->setName(secondName);
}