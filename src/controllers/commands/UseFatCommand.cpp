#include "controllers/commands/UseFatCommand.h"
#include "model/GameModel.h"
#include "model/cards/abilities/Fat.h"
#include "exceptions/Exception.h"
#include "functions.h"
#include <vector>
#include <memory>
#include "controllers/commands/CommandType.h"
#include "exceptions/CommandException.h"
#include "Logger.h"
using namespace std;

UseFatCommand::UseFatCommand(Player* player, Animal* animal, AbilityCard* ability) {
	if (player != nullptr && animal != nullptr && ability != nullptr) {
		this->playerId = getPlayerId(player);
		this->animalId = getAnimalId(player, animal);
		this->fatAbilityId = getAbilityId(animal, ability);
	} else {
		this->playerId = -1;
		this->animalId = -1;
		this->fatAbilityId = -1;
	}	
	type = Command::USE_FAT;
}

void UseFatCommand::execute() {
	if (playerId == -1 || animalId == -1 || fatAbilityId == -1) {
		throw CommandException("UseFatCommand: Fields have not been initialized");
	}
	GameModel* model = GameModel::getInstance();
	try {
		Player* player = model->getPlayer(playerId);
		shared_ptr<Animal> animal = player->getAnimal(animalId);
		Fat* fatAbility = (Fat*)(animal->getAbility(fatAbilityId));
		fatAbility->resetFood();
		fedAbilityId = animal->feed();
	} catch (Exception& e) {
		Logger::fatal(e.getMessage());
		throw CommandException("UseFatCommand: cannot execute because of inner exception");
	}
}

void UseFatCommand::undo() {
	GameModel* model = GameModel::getInstance();
	try {
		Player* player = model->getPlayer(playerId);
		shared_ptr<Animal> animal = player->getAnimal(animalId);
		Fat* fatAbility = (Fat*)(animal->getAbility(fatAbilityId));
		fatAbility->giveFood();

		if (fedAbilityId == -1) {
			animal->setFed(false);
		} else {
			FoodModification* abilityFed = (FoodModification*)(animal->getAbility(fedAbilityId));
			abilityFed->resetFood();
		}	
	} catch (Exception& e) {
		Logger::fatal(e.getMessage());
		throw CommandException("UseFatCommand: cannot undo because of inner exception");
	}
	
}

ostream& UseFatCommand::write(ostream& stream) {
	stream << type << endl;
	stream << playerId << ' ' << animalId << ' ' << fatAbilityId << ' ' << fedAbilityId << endl;
	return stream;
}

istream& UseFatCommand::read(istream& stream) {
	stream >> playerId;
	stream >> animalId;
	stream >> fatAbilityId;
	stream >> fedAbilityId;
	return stream;
}