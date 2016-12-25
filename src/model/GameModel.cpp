#include "model/GameModel.h"
#include "model/GamePhaze.h"
#include "model/FoodStore.h"
#include "exceptions/Exception.h"
#include "functions.h"

template<typename T>
class Deck;

GameModel* GameModel::instance = nullptr;
const int GameModel::CARDS_ON_START = 4;

GameModel::GameModel() {
	//init game	
	firstPlayer = &players[0];
	currentPlayer = firstPlayer;
	moveNum = 1;
	phaze = GamePhaze::EVOLVE;
	cardDeck = new Deck<shared_ptr<AbilityCard>>;
}

GameModel::~GameModel() {
	delete cardDeck;
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
	return cardDeck;
}

FoodStore* GameModel::getFoodStore() {
	return &foodStore;
}

Player* GameModel::getPlayer(int playerNum) {
	if (!checkRange(playerNum, 0, 1)) {
		throw Exception("GameModel::getPlayer: playerNum is not in 0..1");
	}
	return &players[playerNum];
}

Player* GameModel::getCurrentPlayer() {
	return currentPlayer;
}
Player* GameModel::getFirstPlayer() {
	return firstPlayer;
}
Player* GameModel::getOpponent(Player* player) {
	return (player==&players[0]) ? &players[1] : &players[0];
}
Player* GameModel::switchPlayer() {
	Player* next = (currentPlayer == &players[1]) ? &players[0] : &players[1];
	currentPlayer = next;
	return currentPlayer;
}
Player* GameModel::switchFirstPlayer() {
	Player* next = (firstPlayer == &players[1]) ? &players[0] : &players[1];
	firstPlayer = next;
	return firstPlayer;
}
int GameModel::getMove() {
	return moveNum;
}
void GameModel::increaseMove() {
	moveNum++;
}
void GameModel::decreaseMove() {
	if (moveNum < 0) {
		throw Exception("GameModel::decreaseMove: Cannot decrease moveNum below zero");;
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