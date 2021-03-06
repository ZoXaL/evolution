#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include "model/FoodStore.h"
#include "model/Player.h"
#include "model/deck/Deck.h"
#include "model/GamePhaze.h"
#include "model/cards/AbilityCard.h"

#include <vector> 
#include <memory> 
#include <iostream>
using namespace std;

class GameModel {
	FoodStore foodStore;
	Deck<shared_ptr<AbilityCard>>* cardDeck;
	Player players[2];

	Player* currentPlayer;
	Player* firstPlayer;
	int moveNum;
	GamePhaze::Phaze phaze;
	
	static GameModel* instance;
	GameModel();
	~GameModel();
public:
	static const int CARDS_ON_START;

	static GameModel* getInstance();
	static GameModel* initialize();
	static void deleteInstance();
	
	Player* getPlayer(int);
	Player* getCurrentPlayer();
	Player* getFirstPlayer();
	Player* getOpponent(Player* player);
	Player* switchPlayer();
	Player* switchFirstPlayer();

	int getMove();
	void increaseMove();
	void decreaseMove();
	GamePhaze::Phaze switchPhaze(GamePhaze::Phaze newPhaze);
	GamePhaze::Phaze getPhaze();

	Deck<shared_ptr<AbilityCard>>* getCardDeck();
	FoodStore* getFoodStore();

};

#endif