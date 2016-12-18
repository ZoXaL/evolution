#include "controllers/commands/PopFoodCommand.h"
#include "model/GameModel.h"
#include "model/Player.h"
#include "exceptions/Exception.h"

PopFoodCommand::PopFoodCommand(int count) {
	this->count = count;
}

void PopFoodCommand::execute() {
	for (int i = 0; i < count; i++) {
		if(!GameModel::getInstance()->getFoodStore()->getFood()) {
			Exception emptyFoodStore("Cannot get food from empty Food Store");
			emptyFoodStore.log();
			throw emptyFoodStore;
		}
	}	
	undo();
}

void PopFoodCommand::undo() {
	for (int i = 0; i < count; i++) {
		GameModel::getInstance()->getFoodStore()->addFood();
	}	
}