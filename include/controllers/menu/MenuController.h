#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include <string>
#include "controllers/AbstractController.h"

class MenuController : public AbstractController {
	int firstPlayerScore;
	int secondPlayerScore;
	static std::string alert;
public:
	MenuController();
	MenuController(int, int);
	AbstractController* run();
private:
	AbstractController* showMainMenu();
};
#endif