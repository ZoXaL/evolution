#include "controllers/commands/KillAnimalCommand.h"
#include "model/cards/Card.h"
#include "model/cards/AnimalCard.h"
#include "model/GameModel.h"
#include "model/Player.h"
#include "controllers/commands/CommandType.h"

KillAnimalCommand::KillAnimalCommand(int playerId, int animalId){
	this->playerId = playerId;
	this->animalId = animalId;
	type = Command::KILL_ANIMAL;

	GameModel* model = GameModel::getInstance();
	Player* player = model->getPlayer(playerId);
	animal = player->getAnimal(animalId);
}
KillAnimalCommand::KillAnimalCommand(Player* player,int animalId) {
	this->playerId = (GameModel::getInstance()->getPlayer(0) == player) ? 0 : 1;
	this->animalId = animalId;
	type = Command::KILL_ANIMAL;
	
	animal = player->getAnimal(animalId);
}

void KillAnimalCommand::execute() {
	GameModel* model = GameModel::getInstance();
	Player* player = model->getPlayer(playerId);

	animal = player->deleteAnimal(animalId);
}

void KillAnimalCommand::undo() {
	GameModel* model = GameModel::getInstance();
	Player* player = model->getPlayer(playerId);

	// TODO: save all abilities
	player->addAnimal(animal, animalId);	
}

ostream& KillAnimalCommand::write(ostream& stream) {
	stream << type << endl;
	stream << playerId << ' ' << animalId << endl;
	return stream;
}