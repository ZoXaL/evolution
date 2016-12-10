#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include "model/FoodStore.h"
#include "model/Player.h"
#include "model/deck/Deck.h"
#include <vector> 
#include <memory> 
using namespace std;

class GameModel {
	FoodStore foodStore;
	Deck<shared_ptr<Card>> cardDeck;
	Player players[2];
	Player* currentPlayer;
	int moveNum;
	
	static GameModel* instance;
	GameModel();
public:
	static const int CARDS_ON_START;


	static GameModel* getInstance();
	static GameModel* initialize();
	
	Player* getPlayer(int);
	Player* getCurrentPlayer();
	Player* switchPlayer();

	int getMove();
	void increaseMove();
	void decreaseMove();

	Deck<shared_ptr<Card>>* getCardDeck();

};

#endif