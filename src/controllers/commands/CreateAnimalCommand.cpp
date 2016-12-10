#include "controllers/commands/CreateAnimalCommand.h"
#include "model/cards/Card.h"
#include "model/cards/AnimalCard.h"
#include "model/GameModel.h"
#include "model/Player.h"

CreateAnimalCommand::CreateAnimalCommand(int playerId, int cardId) {
	this->playerId = playerId;
	this->cardId = cardId;
}
CreateAnimalCommand::CreateAnimalCommand(Player* player, int cardId) {
	this->playerId = (GameModel::getInstance()->getPlayer(0) == player) ? 0 : 1;
	this->cardId = cardId;
}

void CreateAnimalCommand::execute() {
	GameModel* model = GameModel::getInstance();
	Player* player = model->getPlayer(playerId);
	// TODO:
	// 1) Take abilityCard and delete from hand
	// 2) Convert to AnimalCard
	// 3) Add animalCard to cards
	shared_ptr<Card> createFrom = player->getCardFromHand(cardId);
	player->removeCardFromHand(cardId);
	shared_ptr<AnimalCard> newAnimal(new AnimalCard(createFrom));
	player->addAnimal(newAnimal);
}

void CreateAnimalCommand::undo() {
	
}