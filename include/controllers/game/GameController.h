#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "controllers/AbstractController.h"

// Aimed to select right type of controller
class GameController : public AbstractController {
public:
	AbstractController* run();
};
#endif