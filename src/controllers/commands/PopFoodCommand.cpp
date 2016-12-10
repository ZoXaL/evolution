#include "controllers/commands/PopFoodCommand.h"
#include "model/GameModel.h"
#include "model/Player.h"
#include "exceptions/Exception.h"

PopFoodCommand::PopFoodCommand(int count) {
	this->count = count;
}

void PopFoodCommand::execute() {
	if(!GameModel::getInstance()->getFoodStore()->getFood()) {
		Exception emptyFoodStore("Cannot get food from empty Food Store");
		emptyFoodStore.log();
		throw emptyFoodStore;
	}
}

void PopFoodCommand::undo() {
	
}