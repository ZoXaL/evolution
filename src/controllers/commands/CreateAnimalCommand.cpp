#include "controllers/commands/CreateAnimalCommand.h"
#include "model/cards/AbilityCard.h"
#include "model/cards/Animal.h"
#include "model/GameModel.h"
#include "model/Player.h"
#include "controllers/commands/CommandType.h"
#include "exceptions/CommandException.h"
#include "Logger.h"

CreateAnimalCommand::CreateAnimalCommand(int playerId, int cardId) {
	this->playerId = playerId;
	this->cardId = cardId;
	type = Command::CREATE_ANIMAL;
}
CreateAnimalCommand::CreateAnimalCommand(Player* player, int cardId) {
	this->playerId = (GameModel::getInstance()->getPlayer(0) == player) ? 0 : 1;
	this->cardId = cardId;
	type = Command::CREATE_ANIMAL;
}

void CreateAnimalCommand::execute() {
	GameModel* model = GameModel::getInstance();
	try {
		Player* player = model->getPlayer(playerId);
		shared_ptr<AbilityCard> createFrom = player->getCardFromHand(cardId);
		player->removeCardFromHand(cardId);
		shared_ptr<Animal> newAnimal(new Animal(createFrom, player));
		player->addAnimal(newAnimal);
	} catch (Exception& e) {
		Logger::fatal(e.getMessage());
		throw CommandException("CreateAnimalCommand: cannot execute because of inner exception");
	}	
}

void CreateAnimalCommand::undo() {
	GameModel* model = GameModel::getInstance();
	try {
		Player* player = model->getPlayer(playerId);

		shared_ptr<Animal> animal = player->deleteAnimal(player->animalsCount()-1);
		shared_ptr<AbilityCard> createdFrom = animal->getCreatedFrom();
		player->addCardToHand(createdFrom, cardId);
	} catch (Exception& e) {
		Logger::fatal(e.getMessage());
		throw CommandException("CreateAnimalCommand: cannot undo because of inner exception");
	}
}

ostream& CreateAnimalCommand::write(ostream& stream) {
	stream << type << ' '<< playerId << ' ' << cardId << ' ' << endl;
	return stream;
}
istream& CreateAnimalCommand::read(istream& stream) {
	stream >> playerId >> cardId;
	return stream;
}