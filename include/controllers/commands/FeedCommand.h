#ifndef FEED_COMMAND
#define FEED_COMMAND
#include "controllers/commands/AbstractCommand.h"
#include "model/Player.h"
#include "model/cards/AnimalCard.h"

class FeedCommand: public AbstractCommand {
int playerId;
int animalId;
int abilityId;
public:
	FeedCommand(int playerId, int animalId);
	FeedCommand(Player* player, int animalId);
	void execute();
	void undo();
};
#endif