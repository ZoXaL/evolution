#ifndef CREATE_COMMAND
#define CREATE_COMMAND
#include "controllers/commands/AbstractCommand.h"

class CreateAnimalCommand: public AbstractCommand {
int playerId;
int cardId;
public:
	CreateAnimalCommand(int playerId, int cardId);
	void execute();
	void undo();
};
#endif