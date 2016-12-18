#include "model/GameModel.h"
#include "model/GamePhaze.h"
#include "model/FoodStore.h"
#include "exceptions/Exception.h"
#include "functions.h"

template<typename T>
class Deck;

GameModel* GameModel::instance = nullptr;
const int GameModel::CARDS_ON_START = 2;

GameModel::GameModel() {
	//init game
	currentPlayer = &players[0];
	moveNum = 1;
	phaze = GamePhaze::EVOLVE;
}


GameModel* GameModel::initialize() {
	if (instance != nullptr) {
		delete GameModel::instance;
	} 
	GameModel::instance = new GameModel();
	return GameModel::instance;
}

GameModel* GameModel::getInstance() {
	if(GameModel::instance == nullptr) {
		return initialize();
	}
	return GameModel::instance;
}
void GameModel::deleteInstance() {
	if (instance != nullptr) {
		delete GameModel::instance;
	} 
}

Deck<shared_ptr<AbilityCard>>* GameModel::getCardDeck() {
	return &cardDeck;
}

FoodStore* GameModel::getFoodStore() {
	return &foodStore;
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
	Player* next = (currentPlayer == &players[1]) ? &players[0] : &players[1];
	if (!next->isPassed()) {
		currentPlayer = next;
	}
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
GamePhaze::Phaze GameModel::switchPhaze(GamePhaze::Phaze newPhaze) {
	phaze = newPhaze;
	return phaze;
}
GamePhaze::Phaze GameModel::getPhaze() {
	return phaze;
}