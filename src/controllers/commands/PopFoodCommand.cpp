#include "controllers/commands/PopFoodCommand.h"
#include "model/GameModel.h"
#include "model/Player.h"
#include "controllers/commands/CommandType.h"
#include "exceptions/CommandException.h"
#include "Logger.h"

PopFoodCommand::PopFoodCommand(int count) {
	this->count = count;
	type = Command::POP_FOOD;
}

void PopFoodCommand::execute() {
	for (int i = 0; i < count; i++) {
		if(!GameModel::getInstance()->getFoodStore()->getFood()) {
			throw CommandException("Cannot get food from empty Food Store");;
		}
	}	
}

void PopFoodCommand::undo() {
	for (int i = 0; i < count; i++) {
		GameModel::getInstance()->getFoodStore()->addFood();
	}	
}

ostream& PopFoodCommand::write(ostream& stream) {
	stream << type << ' ' << count << endl;
	return stream;
}
istream& PopFoodCommand::read(istream& stream) {
	stream >> count;
	return stream;
}