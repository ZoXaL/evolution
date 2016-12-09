#ifndef GIVE_CARD_TO_PLAYER_COMMAND_H
#define GIVE_CARD_TO_PLAYER_COMMAND_H

#include "controllers/commands/AbstractCommand.h"

class GiveCardToPlayerCommand: public AbstractCommand {
int playerId;
public:
	GiveCardToPlayerCommand(int playerId);
	void execute();
	void undo();
};
#endif