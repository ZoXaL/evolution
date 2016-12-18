#ifndef END_MOVE_COMMAND
#define END_MOVE_COMMAND
#include "controllers/commands/AbstractCommand.h"
#include <iostream>

class EndMoveCommand: public AbstractCommand {
public:
	EndMoveCommand();
	void execute();
	void undo();
	std::ostream& write(std::ostream& stream);
	std::istream& read(std::istream& stream){};
};
#endif