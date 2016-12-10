#ifndef CLEAR_ANIMAL_FOOD_COMMAND
#define CLEAR_ANIMAL_FOOD_COMMAND
#include "controllers/commands/AbstractCommand.h"
#include "model/Player.h"

class ClearAnimalFoodCommand: public AbstractCommand {
int playerId;
int animalId;
public:
	ClearAnimalFoodCommand(int playerId, int animalId);
	ClearAnimalFoodCommand(Player* player, int animalId);
	void execute();
	void undo();
};
#endif