#include "controllers/commands/AddAbilityCommand.h"
#include "model/cards/Animal.h"
#include "model/GameModel.h"
#include "model/Player.h"
#include "controllers/commands/CommandType.h"
#include "exceptions/CommandException.h"
#include "Logger.h"

AddAbilityCommand::AddAbilityCommand(int playerId, int abilityId, int animalId){
	this->playerId = playerId;
	this->abilityId = abilityId;
	this->animalId = animalId;
	type = Command::ADD_ABILITY;
}
AddAbilityCommand::AddAbilityCommand(Player* player, int abilityId, int animalId) {
	this->playerId = (GameModel::getInstance()->getPlayer(0) == player) ? 0 : 1;
	this->abilityId = abilityId;
	this->animalId = animalId;
	type = Command::ADD_ABILITY;
}

AddAbilityCommand::AddAbilityCommand(Animal* animal, int abilityId) {
	Player* player = animal->getOwner();
	this->playerId = (GameModel::getInstance()->getPlayer(0) == player) ? 0 : 1;
	this->animalId = -1;
	for (auto i = player->getAnimals()->begin(); i != player->getAnimals()->end(); i++) {
		if (animal == i->get()) this->animalId = i-player->getAnimals()->begin();
	}
	if(animalId == -1) {
		throw CommandException("AddAbilityCommand:Cannot feed animal cause it not among player's animals ");
	}
	this->abilityId = abilityId;
	type = Command::ADD_ABILITY;
}

void AddAbilityCommand::execute() {
	GameModel* model = GameModel::getInstance();
	try {
		Player* player = model->getPlayer(playerId);
		shared_ptr<AbilityCard> newAbility = player->getCardFromHand(abilityId);
		player->removeCardFromHand(abilityId);
		shared_ptr<Animal> animal = player->getAnimal(animalId);
		newAbility->setOwner(animal.get());
		animal->pushAbility(newAbility);		
	} catch (Exception& e) {
		Logger::fatal(e.getMessage());
		throw CommandException("AddAbilityCommand: cannot execute because of inner exception");
	}		
}

void AddAbilityCommand::undo() {
	GameModel* model = GameModel::getInstance();
	try {
		Player* player = model->getPlayer(playerId);
		shared_ptr<Animal> animal = player->getAnimal(animalId);
		shared_ptr<AbilityCard> ability = animal->popAbility();	
		ability->setOwner(nullptr);
		player->addCardToHand(ability, abilityId);		
	} catch (Exception& e) {
		Logger::fatal(e.getMessage());
		throw CommandException("AddAbilityCommand: cannot undo because of inner exception");
	}
}
ostream& AddAbilityCommand::write(ostream& stream) {
	stream << type << ' ' << playerId << ' ' << animalId << ' ' << abilityId << endl;
	return stream;
}
istream& AddAbilityCommand::read(istream& stream) {
	stream >> playerId >> animalId >> abilityId;
	return stream;
}