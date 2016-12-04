#include "model/GameModel.h"
#include "functions.h"

class CardDeck;

GameModel* GameModel::instance = nullptr;

GameModel::GameModel() {
	//init game
}

GameModel* GameModel::initialize() {
	if (instance == nullptr) {
		delete instance;
	} 
	instance = new GameModel();
	return instance;
}

GameModel* GameModel::getInstance() {
	return instance;
}

CardDeck* GameModel::getCardDeck() {
	return &cardDeck;
}

Player* GameModel::getPlayer(int playerNum) {
	if (!checkRange(playerNum, 0, 1)) {
		throw 1;
	}
	return &players[playerNum];
}