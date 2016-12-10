#ifndef ADD_ABILITY_COMMAND
#define ADD_ABILITY_COMMAND
#include "controllers/commands/AbstractCommand.h"
#include "model/Player.h"

class AddAbilityCommand: public AbstractCommand {
	int playerId;
	int abilityId;
	int animalId;
public:
	AddAbilityCommand(int playerId, int abilityId, int animalId);
	AddAbilityCommand(Player* player, int abilityId, int animalId);
	void execute();
	void undo();
};
#endif