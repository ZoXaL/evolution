#include "controllers/commands/EndMoveCommand.h"
#include "model/GameModel.h"
#include "controllers/commands/CommandType.h"

EndMoveCommand::EndMoveCommand() {
	type = type = Command::END_MOVE;
}

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

ostream& EndMoveCommand::write(ostream& stream) {
	stream << type << endl;
	return stream;
}