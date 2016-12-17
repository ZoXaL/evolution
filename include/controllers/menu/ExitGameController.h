#ifndef EXIT_GAME_CONTROLLER_H
#define EXIT_GAME_CONTROLLER_H

#include "controllers/AbstractController.h"

class ExitGameController : public AbstractController {
public:
	AbstractController* run();
};
#endif