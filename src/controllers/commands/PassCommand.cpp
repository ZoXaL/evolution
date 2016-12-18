#include "controllers/commands/PassCommand.h"
#include "model/GameModel.h"
#include "model/Player.h"
#include "controllers/commands/CommandType.h"

PassCommand::PassCommand(int playerId, bool pass) {
	this->playerId = playerId;
	this->pass = pass;
	type = Command::PASS;
}

PassCommand::PassCommand(Player* player, bool pass) {
	this->playerId = (GameModel::getInstance()->getPlayer(0) == player) ? 0 : 1;
	this->pass = pass;
	type = Command::PASS;
}

void PassCommand::execute() {
	GameModel* model = GameModel::getInstance();
	Player* player = model->getPlayer(playerId);
	if (pass) {
		player->pass();
	} else {
		player->clearPassed();
	}	
}

void PassCommand::undo() {
	GameModel* model = GameModel::getInstance();
	Player* player = model->getPlayer(playerId);
	if (!pass) {
		player->pass();
	} else {
		player->clearPassed();
	}
}

ostream& PassCommand::write(ostream& stream) {
	stream << type << endl;
	stream << playerId << ' ' << pass << endl;
	return stream;
}