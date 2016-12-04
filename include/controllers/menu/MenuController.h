#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include "controllers/AbstractController.h"

class MenuController : public AbstractController {
public:
	MenuController();
	AbstractController* run();
private:
	AbstractController* showMainMenu();
};
#endif