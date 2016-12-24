#ifndef RESET_USE_COMMAND
#define RESET_USE_COMMAND
#include "controllers/commands/AbstractCommand.h"
#include "model/Player.h"
#include "model/cards/AbilityCard.h"
#include <iostream>

class ResetUseCommand: public AbstractCommand {
int playerId;
int animalId;
int abilityId;
bool used;
public:
	ResetUseCommand(AbilityCard* ability, bool used);
	ResetUseCommand(Player* player, int animalId, int abilityId, bool used);
	void execute();
	void undo();
	std::ostream& write(std::ostream& stream);
	std::istream& read(std::istream& stream);
};
#endif