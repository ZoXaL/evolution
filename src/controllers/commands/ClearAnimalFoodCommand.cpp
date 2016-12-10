#include "controllers/commands/ClearAnimalFoodCommand.h"
#include "model/cards/Card.h"
#include "model/cards/AnimalCard.h"
#include "model/GameModel.h"
#include "model/Player.h"

ClearAnimalFoodCommand::ClearAnimalFoodCommand(int playerId, int animalId){
	this->playerId = playerId;
	this->animalId = animalId;
}
ClearAnimalFoodCommand::ClearAnimalFoodCommand(Player* player,int animalId) {
	this->playerId = (GameModel::getInstance()->getPlayer(0) == player) ? 0 : 1;
	this->animalId = animalId;
}

void ClearAnimalFoodCommand::execute() {
	GameModel* model = GameModel::getInstance();
	Player* player = model->getPlayer(playerId);
	shared_ptr<AnimalCard> animal = player->getAnimal(animalId);

	// vector<shared_ptr<Card>>* abilities = animal->getAbilities();

	// for (int i = 0; i < abilities->size(); i++) {
	// 	shared_ptr<Card> card = abilities->[i];
	// 	AbilityCard* ability = card->getAbilityCard();
	// 	// 2) check if ability needs food
	// 	switch (ability->getAbility()) {
	// 		case (Ability::FAT) : {
	// 			// feed fat only if animal is not hungry				
	// 			Fat* fatCard = (Fat*)ability;
	// 			// feed only if fat is empty
	// 			if (fatCard->needFood()) {
	// 				if (!this->_isHungry) {	// if animal is hungry, you cannot fill fat
	// 					if (abilityToFeed != -1) {	// some fat has been filled earlier
	// 						abilitiesNeedFood = true;	// mark that there is empty fat
	// 						break;
	// 					}
	// 					fatCard->giveFood();
	// 					abilityToFeed = i;
	// 				} else {
	// 					abilitiesNeedFood = true;//mark that there is empty fat
	// 				}		
	// 			}
	// 			break;
	// 		}
	// 	}		
	// }
	animal->clearHungry();
}

void ClearAnimalFoodCommand::undo() {
	
}