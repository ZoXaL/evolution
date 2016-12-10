#include "controllers/commands/KillAnimalCommand.h"
#include "model/cards/Card.h"
#include "model/cards/AnimalCard.h"
#include "model/GameModel.h"
#include "model/Player.h"

KillAnimalCommand::KillAnimalCommand(int playerId, int animalId){
	this->playerId = playerId;
	this->animalId = animalId;
}
KillAnimalCommand::KillAnimalCommand(Player* player,int animalId) {
	this->playerId = (GameModel::getInstance()->getPlayer(0) == player) ? 0 : 1;
	this->animalId = animalId;
}

void KillAnimalCommand::execute() {
	GameModel* model = GameModel::getInstance();
	Player* player = model->getPlayer(playerId);
	shared_ptr<AnimalCard> animal = player->getAnimal(animalId);

	// TODO: save all abilities
	player->delteAnimal(animalId);
}

void KillAnimalCommand::undo() {
	
}