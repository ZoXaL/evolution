#ifndef GIVE_CARD_TO_PLAYER_COMMAND_H
#define GIVE_CARD_TO_PLAYER_COMMAND_H

#include "controllers/commands/AbstractCommand.h"
#include "model/Player.h"
#include <iostream>

class GiveCardToPlayerCommand: public AbstractCommand {
int playerId;
public:
	GiveCardToPlayerCommand(int playerId);
	GiveCardToPlayerCommand(Player* player);
	void execute();
	void undo();
	std::ostream& write(std::ostream& stream);
	std::istream& read(std::istream& stream){};
};
#endif