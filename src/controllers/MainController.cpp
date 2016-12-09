#include "controllers/MainController.h"
#include "controllers/AbstractController.h"
#include "controllers/menu/MenuController.h"

MainController::MainController() {
	currentController = new MenuController();
}

AbstractController* MainController::run() {
	do {
		AbstractController* tmp = currentController;
		currentController = currentController->run();
		if (tmp != nullptr) {
			delete tmp;
		}
	} while(currentController != nullptr);
}