#ifndef PASS_COMMAND
#define PASS_COMMAND
#include "controllers/commands/AbstractCommand.h"
#include "model/Player.h"

class PassCommand: public AbstractCommand {
	int playerId;
public:
	PassCommand(int playerId);
	PassCommand(Player* player);
	void execute();
	void undo();
};
#endif