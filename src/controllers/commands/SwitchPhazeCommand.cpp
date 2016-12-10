#include "controllers/commands/SwitchPhazeCommand.h"
#include "model/GameModel.h"

void SwitchPhazeCommand::execute() {
	GameModel* model = GameModel::getInstance();
	model->switchPhaze();
}

void SwitchPhazeCommand::undo() {
	
}