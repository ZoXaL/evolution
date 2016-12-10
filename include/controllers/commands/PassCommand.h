#ifndef PASS_COMMAND
#define PASS_COMMAND
#include "controllers/commands/AbstractCommand.h"

class PassCommand: public AbstractCommand {
	int playerId;
public:
	PassCommand(int playerId);
	void execute();
	void undo();
};
#endif