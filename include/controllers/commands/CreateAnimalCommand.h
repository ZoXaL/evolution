#ifndef CREATE_COMMAND
#define CREATE_COMMAND
#include "controllers/commands/AbstractCommand.h"
#include "model/Player.h"
#include <iostream>

class CreateAnimalCommand: public AbstractCommand {
int playerId;
int cardId;
public:
	CreateAnimalCommand(int playerId, int cardId);
	CreateAnimalCommand(Player* player, int cardId);
	void execute();
	void undo();
	std::ostream& write(std::ostream& stream);
	std::istream& read(std::istream& stream);
};
#endif