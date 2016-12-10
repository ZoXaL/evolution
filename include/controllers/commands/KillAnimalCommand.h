//Should memorize ALL animal abilities by value

#ifndef KILL_ANIMAL_COMMAND
#define KILL_ANIMAL_COMMAND
#include "controllers/commands/AbstractCommand.h"
#include "model/Player.h"

class KillAnimalCommand: public AbstractCommand {
int playerId;
int animalId;
//list<Card> -- list of all abilities cards for undo
public:
	KillAnimalCommand(int playerId, int animalId);
	KillAnimalCommand(Player* player, int animalId);
	void execute();
	void undo();
};
#endif