#include "controllers/commands/KillAnimalCommand.h"
#include "model/cards/Animal.h"
#include "model/GameModel.h"
#include "model/Player.h"
#include "controllers/commands/CommandType.h"
#include "exceptions/CommandException.h"
#include "Logger.h"

KillAnimalCommand::KillAnimalCommand(int playerId, int animalId){
	this->playerId = playerId;
	this->animalId = animalId;
	type = Command::KILL_ANIMAL;

	GameModel* model = GameModel::getInstance();
	Player* player = model->getPlayer(playerId);
	if (player == nullptr) throw CommandException("KillAnimalCommand: player is null");
	animal = player->getAnimal(animalId);
}
KillAnimalCommand::KillAnimalCommand(Player* player,int animalId) {
	if (player == nullptr) throw CommandException("KillAnimalCommand: player is null");
	this->playerId = (GameModel::getInstance()->getPlayer(0) == player) ? 0 : 1;
	this->animalId = animalId;
	type = Command::KILL_ANIMAL;
	
	animal = player->getAnimal(animalId);
}
KillAnimalCommand::KillAnimalCommand(Animal* animal) {
	Player* player = animal->getOwner();
	if (player == nullptr) throw CommandException("KillAnimalCommand: player is null");
	this->playerId = (GameModel::getInstance()->getPlayer(0) == player) ? 0 : 1;
	this->animalId = -1;
	for (auto i = player->getAnimals()->begin(); i != player->getAnimals()->end(); i++) {
		if (animal == i->get()) this->animalId = i-player->getAnimals()->begin();
	}
	if(animalId == -1) {
		throw Exception("Cannot feed animal cause it not among player's animals ");
	}
	type = Command::KILL_ANIMAL;
	
	this->animal = player->getAnimal(animalId);
}

void KillAnimalCommand::execute() {
	GameModel* model = GameModel::getInstance();
	try {
		Player* player = model->getPlayer(playerId);
		animal = player->deleteAnimal(animalId);
	} catch (Exception& e) {
		Logger::fatal(e.getMessage());
		throw CommandException("KillAnimalCommand: cannot execute because of inner exception");
	}
}

void KillAnimalCommand::undo() {
	GameModel* model = GameModel::getInstance();
	try {
		Player* player = model->getPlayer(playerId);
		player->addAnimal(animal, animalId);	
	} catch (Exception& e) {
		Logger::fatal(e.getMessage());
		throw CommandException("KillAnimalCommand: cannot undo because of inner exception");
	}
}

ostream& KillAnimalCommand::write(ostream& stream) {
	stream << type << ' ' << playerId << ' ' << animalId << endl;
	return stream;
}
istream& KillAnimalCommand::read(istream& stream) {
	stream >> playerId >> animalId;
	return stream;
}