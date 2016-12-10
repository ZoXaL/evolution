#include "controllers/commands/EndMoveCommand.h"
#include "model/GameModel.h"

void EndMoveCommand::execute() {
	GameModel* model = GameModel::getInstance();
	model->increaseMove();
	model->switchPlayer();
}

void EndMoveCommand::undo() {
	GameModel* model = GameModel::getInstance();
	model->decreaseMove();
	model->switchPlayer();
}