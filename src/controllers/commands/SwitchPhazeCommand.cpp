#include "controllers/commands/SwitchPhazeCommand.h"
#include "model/GameModel.h"
#include "model/GamePhaze.h"
#include "controllers/commands/CommandType.h"

SwitchPhazeCommand::SwitchPhazeCommand(GamePhaze::Phaze newPhaze) {
	this->newPhaze = newPhaze;
	this->foodCount = 0;
	type = Command::SWITCH_PHAZE;
}

void SwitchPhazeCommand::execute() {
	GameModel* model = GameModel::getInstance();
	switch (newPhaze) {
		case GamePhaze::EVOLVE : {
			Player* firstPlayer = model->switchFirstPlayer();
			if (model->getCurrentPlayer() != firstPlayer) {
				model->switchPlayer();
				playerSwitched = true;
			}
			break;
		}
		case GamePhaze::FEED : {
			foodCount = model->getFoodStore()->generateFood();
			Player* firstPlayer = model->getFirstPlayer();
			if (model->getCurrentPlayer() != firstPlayer) {
				model->switchPlayer();
				playerSwitched = true;
			}
			break;
		}
	}
	model->switchPhaze(newPhaze);
}

void SwitchPhazeCommand::undo() {
	GameModel* model = GameModel::getInstance();
	switch (newPhaze) {
		case GamePhaze::EVOLVE : {
			Player* firstPlayer = model->switchFirstPlayer();
			if (playerSwitched) {
				model->switchPlayer();
			}
			model->switchPhaze(GamePhaze::FEED);
			break;
		}
		case GamePhaze::FEED : {
			if (playerSwitched) {
				model->switchPlayer();
			}
			model->switchPhaze(GamePhaze::EVOLVE);
			break;
		}
	}
}

ostream& SwitchPhazeCommand::write(ostream& stream) {
	stream << type << endl;
	stream << newPhaze << ' ' << foodCount << ' ' << playerSwitched << endl;
	return stream;
}