#include "controllers/commands/CreateAnimalCommand.h"
#include "model/GameModel.h"
#include "model/Player.h"

CreateAnimalCommand::CreateAnimalCommand(int playerId, int cardId) {
	this->playerId = playerId;
	this->cardId = cardId;
}

void CreateAnimalCommand::execute() {
	GameModel* model = GameModel::getInstance();
	Player* player = model->getPlayer(playerId);
	// TODO:
	// 1) Take abilityCard and delete from hand
	// 2) Convert to AnimalCard
	// 3) Add animalCard to cards
	// shared_ptr<Card> createFrom = player->get
}

void CreateAnimalCommand::undo() {
	
}