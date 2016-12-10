#ifndef SWITCH_PHAZE_COMMAND
#define SWITCH_PHAZE_COMMAND
#include "controllers/commands/AbstractCommand.h"
#include "model/GamePhaze.h"

class SwitchPhazeCommand: public AbstractCommand {
	GamePhaze::Phaze newPhaze;
	int foodCount;
public:
	SwitchPhazeCommand(GamePhaze::Phaze newPhaze);
	void execute();
	void undo();
};
#endif