#include "controllers/commands/PassCommand.h"
#include "model/GameModel.h"

PassCommand::PassCommand(int playerId) {
	this->playerId = playerId;
}

void PassCommand::execute() {
	GameModel* model = GameModel::getInstance();
	Player* player = model->getPlayer(playerId);
	player->pass();
}

void PassCommand::undo() {
	
}