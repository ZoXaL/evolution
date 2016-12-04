#ifndef START_GAME_CONTROLLER_H
#define START_GAME_CONTROLLER_H

#include "controllers/AbstractController.h"

class StartGameController : public AbstractController {
	bool newGame;
public:
	AbstractController* run();
	StartGameController(bool newGame = false);
private:	
	void initPlayers();
	void initGameModel();
};
#endif