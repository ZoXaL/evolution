#ifndef SWITCH_PHAZE_COMMAND
#define SWITCH_PHAZE_COMMAND
#include "controllers/commands/AbstractCommand.h"
#include "model/GamePhaze.h"
#include <iostream>

class SwitchPhazeCommand: public AbstractCommand {
	GamePhaze::Phaze newPhaze;
	int foodCount;
public:
	SwitchPhazeCommand(GamePhaze::Phaze newPhaze);
	void execute();
	void undo();
	std::ostream& write(std::ostream& stream){};
	std::istream& read(std::istream& stream){};
};
#endif