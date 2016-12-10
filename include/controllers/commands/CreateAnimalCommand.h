#ifndef CREATE_COMMAND
#define CREATE_COMMAND
#include "controllers/commands/AbstractCommand.h"
#include "model/Player.h"

class CreateAnimalCommand: public AbstractCommand {
int playerId;
int cardId;
public:
	CreateAnimalCommand(int playerId, int cardId);
	CreateAnimalCommand(Player* player, int cardId);
	void execute();
	void undo();
};
#endif