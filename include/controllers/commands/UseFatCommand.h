#ifndef USE_FAT_COMMAND
#define USE_FAT_COMMAND
#include "controllers/commands/AbstractCommand.h"
#include "model/Player.h"
#include "model/cards/AnimalCard.h"
#include "model/cards/AbilityCard.h"
#include <iostream>

class UseFatCommand: public AbstractCommand {
	int playerId;	
	int animalId;
	int fatAbilityId;
	int fedAbilityId;
public:
	UseFatCommand(Player*, AnimalCard*, AbilityCard*);
	void execute();
	void undo();
	std::ostream& write(std::ostream& stream){};
	std::istream& read(std::istream& stream){};
};
#endif