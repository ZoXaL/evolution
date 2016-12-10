#ifndef SWITCH_PHAZE_COMMAND
#define SWITCH_PHAZE_COMMAND
#include "controllers/commands/AbstractCommand.h"

class SwitchPhazeCommand: public AbstractCommand {
public:
	void execute();
	void undo();
};
#endif