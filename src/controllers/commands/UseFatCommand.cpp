#include "controllers/commands/UseFatCommand.h"
#include "model/GameModel.h"
#include "model/cards/abilities/Fat.h"
#include "exceptions/Exception.h"
#include "functions.h"
#include <vector>
#include <memory>
using namespace std;

UseFatCommand::UseFatCommand(Player* player, AnimalCard* animal, AbilityCard* ability) {
	this->playerId = getPlayerId(player);
	this->animalId = getAnimalId(player, animal);
	this->fatAbilityId = getAbilityId(animal, ability);
}

void UseFatCommand::execute() {
	GameModel* model = GameModel::getInstance();
	Player* player = model->getPlayer(playerId);
	shared_ptr<AnimalCard> animal = player->getAnimal(animalId);
	Fat* fatAbility = (Fat*)(animal->getAbility(fatAbilityId));
	fatAbility->resetFood();
	fedAbilityId = animal->feed();
}

void UseFatCommand::undo() {
	GameModel* model = GameModel::getInstance();
	Player* player = model->getPlayer(playerId);
	shared_ptr<AnimalCard> animal = player->getAnimal(animalId);
	Fat* fatAbility = (Fat*)(animal->getAbility(fatAbilityId));
	fatAbility->giveFood();

	if (fedAbilityId == -1) {
		animal->setHungry(true);
	} else {
		FoodModification* abilityFed = (FoodModification*)(animal->getAbility(fedAbilityId));
		abilityFed->resetFood();
	}	
}