#include "model/GameModel.h"
#include "exceptions/Exception.h"
#include "functions.h"

template<typename T>
class Deck;

GameModel* GameModel::instance = nullptr;
const int GameModel::CARDS_ON_START = 2;

GameModel::GameModel() {
	//init game
	currentPlayer = &players[0];
}

GameModel* GameModel::initialize() {
	if (instance == nullptr) {
		delete instance;
	} 
	instance = new GameModel();
	return instance;
}

GameModel* GameModel::getInstance() {
	if(instance == nullptr) {
		return initialize();
	}
	return instance;
}

Deck<shared_ptr<Card>>* GameModel::getCardDeck() {
	return &cardDeck;
}

Player* GameModel::getPlayer(int playerNum) {
	if (!checkRange(playerNum, 0, 1)) {
		throw 1;
	}
	return &players[playerNum];
}

Player* GameModel::getCurrentPlayer() {
	return currentPlayer;
}

Player* GameModel::switchPlayer() {
	currentPlayer = (currentPlayer == &players[1]) ? &players[0] : &players[1];
	return currentPlayer;
}
int GameModel::getMove() {
	return moveNum;
}
void GameModel::increaseMove() {
	moveNum++;
}
void GameModel::decreaseMove() {
	if (moveNum < 0) {
		Exception illegalModelState("Cannot decrease moveNum below zero");
		illegalModelState.log();
		throw illegalModelState;
	}
	moveNum--;
}
