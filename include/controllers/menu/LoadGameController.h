#ifndef LOAD_GAME_CONTROLLER_H
#define LOAD_GAME_CONTROLLER_H

#include "controllers/AbstractController.h"

class LoadGameController : public AbstractController {
	bool newGame;
public:
	AbstractController* run();
};
#endif