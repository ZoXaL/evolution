#include "controllers/commands/FeedCommand.h"
#include "model/cards/Card.h"
#include "model/cards/AnimalCard.h"
#include "model/GameModel.h"
#include "model/Player.h"

#include <memory>

using namespace std;


FeedCommand::FeedCommand(int playerId, int animalId){
	this->playerId = playerId;
	this->animalId = animalId;
	this->abilityId = abilityId;
}
FeedCommand::FeedCommand(Player* player, int animalId) {
	this->playerId = (GameModel::getInstance()->getPlayer(0) == player) ? 0 : 1;
	this->animalId = animalId;
	this->abilityId = abilityId;
}

void FeedCommand::execute() {
	GameModel* model = GameModel::getInstance();
	Player* player = model->getPlayer(playerId);
	shared_ptr<AnimalCard> animal = player->getAnimal(animalId);
	abilityId = animal->feed();
	// TODO:
	// 1) Take food
	// 2) Feed animal
	// shared_ptr<Card> newAbility = player->getCardFromHand(abilityId);
	// player->removeCardFromHand(abilityId);
	// shared_ptr<AnimalCard> animal = player->getAnimal(animalId);
	// animal->addAbility(newAbility);
}

void FeedCommand::undo() {
	
}