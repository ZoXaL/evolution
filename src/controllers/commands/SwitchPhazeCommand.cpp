#include "controllers/commands/SwitchPhazeCommand.h"
#include "model/GameModel.h"
#include "model/GamePhaze.h"

SwitchPhazeCommand::SwitchPhazeCommand(GamePhaze::Phaze newPhaze) {
	this->newPhaze = newPhaze;
	this->foodCount = 0;
}

void SwitchPhazeCommand::execute() {
	GameModel* model = GameModel::getInstance();
	switch (newPhaze) {
		case GamePhaze::EVOLVE : {

			break;
		}
		case GamePhaze::FEED : {
			foodCount = model->getFoodStore()->generateFood();
			break;
		}
	}
	model->switchPhaze(newPhaze);
}

void SwitchPhazeCommand::undo() {
	
}