#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include "model/FoodStore.h"
#include "model/Player.h"
#include "model/cards/CardDeck.h"
#include <vector> 
using namespace std;

class GameModel {
	FoodStore foodStore;
	CardDeck cardDeck;
	Player players[2];

	static GameModel* instance;
	GameModel();
public:
	static GameModel* getInstance();
	static GameModel* initialize();
	Player* getPlayer(int);
	CardDeck* getCardDeck();
};

#endif