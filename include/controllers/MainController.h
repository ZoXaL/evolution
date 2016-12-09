#ifndef MAIN_CONTROLLER_H
#define MAIN_CONTROLLER_H

#include "controllers/AbstractController.h"

class MainController : public AbstractController {
	AbstractController* currentController;
public:
	MainController();
	AbstractController* run();
};

#endif