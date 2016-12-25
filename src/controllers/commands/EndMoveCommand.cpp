#include "controllers/commands/EndMoveCommand.h"
#include "model/GameModel.h"
#include "controllers/commands/CommandType.h"
#include "exceptions/CommandException.h"
#include "Logger.h"

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
	try {
		model->decreaseMove();
	} catch (Exception& e) {
		Logger::warn("EndMoveCommand: cannot undo because of "+e.getMessage());
	}
	
	model->switchPlayer();
}

ostream& EndMoveCommand::write(ostream& stream) {
	stream << type << endl;
	return stream;
}

istream& EndMoveCommand::read(istream& stream) {
	return stream;
}