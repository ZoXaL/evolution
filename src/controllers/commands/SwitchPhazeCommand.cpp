#include "controllers/commands/SwitchPhazeCommand.h"
#include "model/GameModel.h"
#include "model/GamePhaze.h"
#include "controllers/commands/CommandType.h"
#include "exceptions/CommandException.h"
#include "Logger.h"

SwitchPhazeCommand::SwitchPhazeCommand(GamePhaze::Phaze newPhaze) {
	this->newPhaze = newPhaze;
	this->foodCount = -1;
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
			if (this->foodCount == -1) {
				this->foodCount = model->getFoodStore()->generateFood();
			} else {
				model->getFoodStore()->setFood(this->foodCount);
			}			
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
	stream << type << ' ' << newPhaze << ' ' << foodCount << ' ' << playerSwitched << endl;
	return stream;
}

istream& SwitchPhazeCommand::read(istream& stream) {
	int nextPhaze = -1;
	stream >> nextPhaze >> foodCount >> playerSwitched;
	newPhaze = static_cast<GamePhaze::Phaze>(nextPhaze);
	return stream;
}