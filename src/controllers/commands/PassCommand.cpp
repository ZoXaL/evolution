#include "controllers/commands/PassCommand.h"
#include "model/GameModel.h"
#include "model/Player.h"

PassCommand::PassCommand(int playerId) {
	this->playerId = playerId;
}

PassCommand::PassCommand(Player* player) {
	this->playerId = (GameModel::getInstance()->getPlayer(0) == player) ? 0 : 1;
}

void PassCommand::execute() {
	GameModel* model = GameModel::getInstance();
	Player* player = model->getPlayer(playerId);
	player->pass();
}

void PassCommand::undo() {
	
}