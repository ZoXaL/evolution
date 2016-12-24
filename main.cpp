#include "controllers/MainController.h"
#include <iostream>
#include "Logger.h"

int main() {
	std::system("clear");
	Logger::log("Game start", Logger::TRACE);
	MainController controller;
	controller.run();
	return 0;
}