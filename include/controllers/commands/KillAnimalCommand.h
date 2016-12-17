//Should memorize ALL animal abilities by value

#ifndef KILL_ANIMAL_COMMAND
#define KILL_ANIMAL_COMMAND
#include "controllers/commands/AbstractCommand.h"
#include "model/Player.h"
#include <memory>
#include <iostream>

class KillAnimalCommand: public AbstractCommand {
int playerId;
int animalId;
shared_ptr<AnimalCard> animal;
//list<Card> -- list of all abilities cards for undo
public:
	KillAnimalCommand(int playerId, int animalId);
	KillAnimalCommand(Player* player, int animalId);
	void execute();
	void undo();
	std::ostream& write(std::ostream& stream){};
	std::istream& read(std::istream& stream){};
};
#endif