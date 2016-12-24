#ifndef PASS_COMMAND
#define PASS_COMMAND
#include "controllers/commands/AbstractCommand.h"
#include "model/Player.h"
#include <iostream>

class PassCommand: public AbstractCommand {
	int playerId;
	bool pass;
public:
	PassCommand(int playerId, bool pass = true);
	PassCommand(Player* player, bool pass = true);
	void execute();
	void undo();
	std::ostream& write(std::ostream& stream);
	std::istream& read(std::istream& stream);
};
#endif