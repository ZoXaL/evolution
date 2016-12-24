#include "controllers/MainController.h"
#include <iostream>
#include "Logger.h"
#include <time.h>
#include <stdlib.h>
#include "model/deck/Deck.h"

int main() {
	std::srand (std::time(NULL));
	std::system("clear");
	Logger::log("Game start", Logger::TRACE);
	MainController controller;
	controller.run();
	return 0;
}