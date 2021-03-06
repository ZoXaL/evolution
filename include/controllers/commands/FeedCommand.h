#ifndef FEED_COMMAND
#define FEED_COMMAND
#include "controllers/commands/AbstractCommand.h"
#include "model/Player.h"
#include "model/cards/Animal.h"
#include <iostream>

class FeedCommand: public AbstractCommand {
int playerId;
int animalId;
int abilityId;
public:
	FeedCommand(int playerId, int animalId);
	FeedCommand(Player* player, int animalId);
	FeedCommand(Animal* animal);
	void execute();
	void undo();
	std::ostream& write(std::ostream& stream);
	std::istream& read(std::istream& stream);
};
#endif