#include "controllers/commands/AddAbilityCommand.h"
#include "model/cards/Card.h"
#include "model/cards/Animal.h"
#include "model/GameModel.h"
#include "model/Player.h"
#include "controllers/commands/CommandType.h"

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
		throw Exception("Cannot feed animal cause it not among player's animals ");
	}
	this->abilityId = abilityId;
}

void AddAbilityCommand::execute() {
	GameModel* model = GameModel::getInstance();
	Player* player = model->getPlayer(playerId);
	// TODO:
	// 1) Take abilityCard and delete from hand
	// 2) Add abilityCard to animal abilities
	shared_ptr<AbilityCard> newAbility = player->getCardFromHand(abilityId);
	player->removeCardFromHand(abilityId);
	shared_ptr<Animal> animal = player->getAnimal(animalId);
	newAbility->setOwner(animal.get());
	animal->pushAbility(newAbility);
}

void AddAbilityCommand::undo() {
	GameModel* model = GameModel::getInstance();
	Player* player = model->getPlayer(playerId);
	shared_ptr<Animal> animal = player->getAnimal(animalId);

	shared_ptr<AbilityCard> ability = animal->popAbility();
	ability->setOwner(nullptr);
	player->addCardToHand(ability, abilityId);	
}
ostream& AddAbilityCommand::write(ostream& stream) {
	stream << type << endl;
	stream << playerId << ' ' << animalId << ' ' << abilityId << endl;
	return stream;
}
istream& AddAbilityCommand::read(istream& stream) {
	stream >> playerId;
	stream >> animalId;
	stream >> abilityId;
	return stream;
}