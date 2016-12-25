#include "controllers/commands/ClearAnimalFoodCommand.h"
#include "model/cards/Card.h"
#include "model/cards/Animal.h"
#include "model/cards/abilities/Fat.h"
#include "model/cards/interfaces/FoodModification.h"
#include "model/GameModel.h"
#include "model/Player.h"
#include "controllers/commands/CommandType.h"
#include "exceptions/CommandException.h"
#include "Logger.h"

ClearAnimalFoodCommand::ClearAnimalFoodCommand(int playerId, int animalId){
	this->playerId = playerId;
	this->animalId = animalId;
	type = Command::CLEAR_ANIMAL_FOOD;
}
ClearAnimalFoodCommand::ClearAnimalFoodCommand(Player* player,int animalId) {
	this->playerId = (GameModel::getInstance()->getPlayer(0) == player) ? 0 : 1;
	this->animalId = animalId;
	type = Command::CLEAR_ANIMAL_FOOD;
}

void ClearAnimalFoodCommand::execute() {
	GameModel* model = GameModel::getInstance();
	try {
		Player* player = model->getPlayer(playerId);
		shared_ptr<Animal> animal = player->getAnimal(animalId);
		animal->setFed(false);
		for (auto i = animal->getAbilities()->begin(); i != animal->getAbilities()->end(); i++) {
			FoodModification* foodModification = dynamic_cast<FoodModification*>(i->get());
			if (foodModification && !dynamic_cast<Fat*>(foodModification)) {
				foodModification->resetFood();
			}			
		}
	} catch (Exception& e) {
		Logger::fatal(e.getMessage());
		throw CommandException("ClearAnimalFoodCommand: cannot execute because of inner exception");
	}		
}

void ClearAnimalFoodCommand::undo() {
	GameModel* model = GameModel::getInstance();
	try {
		Player* player = model->getPlayer(playerId);
		shared_ptr<Animal> animal = player->getAnimal(animalId);
		animal->setFed(true);
		for (auto i = animal->getAbilities()->begin(); i != animal->getAbilities()->end(); i++) {
			FoodModification* foodModification = dynamic_cast<FoodModification*>(i->get());
			if (foodModification && !dynamic_cast<Fat*>(foodModification)) {
				while (foodModification->needFood()) {
					foodModification->giveFood();
				}			
			}			
		}
	} catch (Exception& e) {
		Logger::fatal(e.getMessage());
		throw CommandException("ClearAnimalFoodCommand: cannot undo because of inner exception");
	}		
}

ostream& ClearAnimalFoodCommand::write(ostream& stream) {
	stream << type << endl;
	stream << playerId << ' ' << animalId << ' ' << neededFood << endl;
	return stream;
}

istream& ClearAnimalFoodCommand::read(istream& stream) {
	stream >> playerId;
	stream >> animalId;
	stream >> neededFood;
	return stream;
}