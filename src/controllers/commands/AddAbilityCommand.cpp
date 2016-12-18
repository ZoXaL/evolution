#include "controllers/commands/AddAbilityCommand.h"
#include "model/cards/Card.h"
#include "model/cards/AnimalCard.h"
#include "model/GameModel.h"
#include "model/Player.h"

AddAbilityCommand::AddAbilityCommand(int playerId, int abilityId, int animalId){
	this->playerId = playerId;
	this->abilityId = abilityId;
	this->animalId = animalId;
}
AddAbilityCommand::AddAbilityCommand(Player* player, int abilityId, int animalId) {
	this->playerId = (GameModel::getInstance()->getPlayer(0) == player) ? 0 : 1;
	this->abilityId = abilityId;
	this->animalId = animalId;
}

void AddAbilityCommand::execute() {
	GameModel* model = GameModel::getInstance();
	Player* player = model->getPlayer(playerId);
	// TODO:
	// 1) Take abilityCard and delete from hand
	// 2) Add abilityCard to animal abilities
	shared_ptr<AbilityCard> newAbility = player->getCardFromHand(abilityId);
	player->removeCardFromHand(abilityId);
	shared_ptr<AnimalCard> animal = player->getAnimal(animalId);
	animal->pushAbility(newAbility);
}

void AddAbilityCommand::undo() {
	GameModel* model = GameModel::getInstance();
	Player* player = model->getPlayer(playerId);
	shared_ptr<AnimalCard> animal = player->getAnimal(animalId);

	shared_ptr<AbilityCard> ability = animal->popAbility();
	player->addCardToHand(ability, abilityId);	
}