#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include "model/FoodStore.h"
#include "model/Player.h"
#include <vector> 
using namespace std;

class GameModel {
	FoodStore foodStore;
	Player players[2];

	static GameModel* instance;
	GameModel();
public:
	static GameModel* getInstance();
	static GameModel* initialize();
	Player* getPlayer(int);
};

#endif