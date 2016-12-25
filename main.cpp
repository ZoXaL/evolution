#include "controllers/MainController.h"
#include <iostream>
#include "Logger.h"
#include <time.h>
#include <stdlib.h>
#include "model/deck/Deck.h"
#include "exceptions/DeckException.h"

void evoliveTerminate() {
	Logger::fatal("Terminate exit");
	exit(1);
}

void evoliveUnexpected() {
	Logger::fatal("Unexpected exception");
	exit(1);
}

int main() {
	set_terminate(evoliveTerminate);
	set_unexpected(evoliveUnexpected);
	std::srand (std::time(NULL));
	Logger::info("Game starts");

	std::system("resize -s 40 150");		
	std::system("clear");		
	MainController controller;
	controller.run();
	return 0;
}