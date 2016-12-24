#ifndef SAVE_GAME_CONTROLLER_H
#define SAVE_GAME_CONTROLLER_H

#include "controllers/AbstractController.h"

class SaveGameController : public AbstractController {
	bool newGame;
public:
	AbstractController* run();
};
#endif