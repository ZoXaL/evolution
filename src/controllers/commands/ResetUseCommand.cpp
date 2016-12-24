#include "controllers/commands/ResetUseCommand.h"
#include "model/cards/Card.h"
#include "model/cards/Animal.h"
#include "model/cards/interfaces/ActiveAbility.h"
#include "model/cards/AbilityCard.h"
#include "model/GameModel.h"
#include "model/Player.h"
#include "controllers/commands/CommandType.h"

ResetUseCommand::ResetUseCommand(Player* player,int animalId, int abilityId, bool used) {
	this->playerId = (GameModel::getInstance()->getPlayer(0) == player) ? 0 : 1;
	this->animalId = animalId;
	this->abilityId = abilityId;
	this->used = used;
	type = Command::RESET_USE;
}

ResetUseCommand::ResetUseCommand(AbilityCard* ability, bool used) {
	Animal* animal = ability->getOwner();
	Player* player = animal->getOwner();

	this->playerId = (GameModel::getInstance()->getPlayer(0) == player) ? 0 : 1;
	this->animalId = -1;
	for (auto i = player->getAnimals()->begin(); i != player->getAnimals()->end(); i++) {
		if (animal == i->get()) this->animalId = i-player->getAnimals()->begin();
	}
	if(animalId == -1) {
		throw Exception("Cannot reset animal ability usage cause it not among player's animals ");
	}

	this->abilityId = -1;
	for (auto i = animal->getAbilities()->begin(); i != animal->getAbilities()->end(); i++) {
		if (ability == i->get()) this->abilityId = i-animal->getAbilities()->begin();
	}
	if(abilityId == -1) {
		throw Exception("Cannot reset animal ability usage cause ability is not among animal's abilities");
	}
	this->used = used;
	type = Command::RESET_USE;
}

void ResetUseCommand::execute() {
	GameModel* model = GameModel::getInstance();
	Player* player = model->getPlayer(playerId);
	shared_ptr<Animal> animal = player->getAnimal(animalId);
	ActiveAbility* activeAbility = dynamic_cast<ActiveAbility*>(animal->getAbility(abilityId));
	activeAbility->setUsed(used);
}

void ResetUseCommand::undo() {
	GameModel* model = GameModel::getInstance();
	Player* player = model->getPlayer(playerId);
	shared_ptr<Animal> animal = player->getAnimal(animalId);
	ActiveAbility* activeAbility = dynamic_cast<ActiveAbility*>(animal->getAbility(abilityId));
	activeAbility->setUsed(!used);
}

ostream& ResetUseCommand::write(ostream& stream) {
	stream << type << endl;
	stream << playerId << ' ' << animalId << ' ' << abilityId << ' ' << used << endl;
	return stream;
}

istream& ResetUseCommand::read(istream& stream) {
	stream >> playerId;
	stream >> animalId;
	stream >> abilityId;
	stream >> used;
	return stream;
}