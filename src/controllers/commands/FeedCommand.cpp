#include "controllers/commands/FeedCommand.h"
#include "model/cards/Card.h"
#include "model/cards/Animal.h"
#include "model/GameModel.h"
#include "model/Player.h"
#include "model/cards/interfaces/FoodModification.h"
#include "controllers/commands/CommandType.h"
#include "exceptions/Exception.h"
#include <memory>
#include "exceptions/CommandException.h"
#include "Logger.h"

using namespace std;


FeedCommand::FeedCommand(int playerId, int animalId){
	this->playerId = playerId;
	this->animalId = animalId;
	this->abilityId = -3;
	type = Command::FEED;
}
FeedCommand::FeedCommand(Player* player, int animalId) {
	this->playerId = (GameModel::getInstance()->getPlayer(0) == player) ? 0 : 1;
	this->animalId = animalId;
	this->abilityId = -3;
	type = Command::FEED;
}
FeedCommand::FeedCommand(Animal* animal) {
	if (animal == nullptr) throw CommandException("FeedCommand: animal is null");
	Player* player = animal->getOwner();
	if (player == nullptr) throw CommandException("FeedCommand: player is null");
	this->playerId = (GameModel::getInstance()->getPlayer(0) == player) ? 0 : 1;
	this->animalId = -1;
	for (auto i = player->getAnimals()->begin(); i != player->getAnimals()->end(); i++) {
		if (animal == i->get()) this->animalId = i-player->getAnimals()->begin();
	}
	if(animalId == -1) {
		throw Exception("Cannot feed animal cause it not among player's animals ");
	}
	this->abilityId = -3;
	type = Command::FEED;
}

void FeedCommand::execute() {
	GameModel* model = GameModel::getInstance();
	try {
		Player* player = model->getPlayer(playerId);
		shared_ptr<Animal> animal = player->getAnimal(animalId);
		if (abilityId == -2) {
			Logger::info("FeedCommand: Animal doesn't need food");
			return;
		}
		if (abilityId == -3) {
			abilityId = animal->feed();
		} else {
			if (abilityId == -1) {
				animal->setFed(true);
			} else {
				FoodModification* abilityFed = dynamic_cast<FoodModification*>(animal->getAbility(abilityId));
				abilityFed->giveFood();
			}	
		}			
	} catch (Exception& e) {
		Logger::fatal(e.getMessage());
		throw CommandException("FeedCommand: cannot execute because of inner exception");
	}
}

void FeedCommand::undo() {
	GameModel* model = GameModel::getInstance();
	try {
		Player* player = model->getPlayer(playerId);
		shared_ptr<Animal> animal = player->getAnimal(animalId);
		if (abilityId == -1) {
			animal->setFed(false);
		} else {
			FoodModification* abilityFed = dynamic_cast<FoodModification*>(animal->getAbility(abilityId));
			abilityFed->decreaseFood();
		}	
	} catch (Exception& e) {
		Logger::fatal(e.getMessage());
		throw CommandException("FeedCommand: cannot undo because of inner exception");
	}
}
ostream& FeedCommand::write(ostream& stream) {
	stream << type << endl;
	stream << playerId << ' ' << animalId << ' ' << abilityId << endl;
	return stream;
}
istream& FeedCommand::read(istream& stream) {
	stream >> playerId;
	stream >> animalId;
	stream >> abilityId;
	return stream;
}