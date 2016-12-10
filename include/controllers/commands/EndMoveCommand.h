#ifndef END_MOVE_COMMAND
#define END_MOVE_COMMAND
#include "controllers/commands/AbstractCommand.h"

class EndMoveCommand: public AbstractCommand {
public:
	void execute();
	void undo();
};
#endif