#include "controllers/commands/PopFoodCommand.h"
#include "model/GameModel.h"
#include "model/Player.h"
#include "exceptions/Exception.h"
#include "controllers/commands/CommandType.h"

PopFoodCommand::PopFoodCommand(int count) {
	this->count = count;
	type = Command::POP_FOOD;
}

void PopFoodCommand::execute() {
	for (int i = 0; i < count; i++) {
		if(!GameModel::getInstance()->getFoodStore()->getFood()) {
			Exception emptyFoodStore("Cannot get food from empty Food Store");
			emptyFoodStore.log();
			throw emptyFoodStore;
		}
	}	
}

void PopFoodCommand::undo() {
	for (int i = 0; i < count; i++) {
		GameModel::getInstance()->getFoodStore()->addFood();
	}	
}

ostream& PopFoodCommand::write(ostream& stream) {
	stream << type << endl;
	stream << count << endl;
	return stream;
}