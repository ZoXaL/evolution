#include "controllers/commands/FeedCommand.h"
#include "model/cards/Card.h"
#include "model/cards/Animal.h"
#include "model/GameModel.h"
#include "model/Player.h"
#include "model/cards/interfaces/FoodModification.h"
#include "controllers/commands/CommandType.h"
#include "exceptions/Exception.h"
#include <memory>

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

void FeedCommand::execute() {
	GameModel* model = GameModel::getInstance();
	Player* player = model->getPlayer(playerId);
	shared_ptr<Animal> animal = player->getAnimal(animalId);
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
	if (abilityId == -2) throw Exception("Animal doesn't need food");
}

void FeedCommand::undo() {
	GameModel* model = GameModel::getInstance();
	Player* player = model->getPlayer(playerId);
	shared_ptr<Animal> animal = player->getAnimal(animalId);
	if (abilityId == -1) {
		animal->setFed(false);
	} else {
		FoodModification* abilityFed = dynamic_cast<FoodModification*>(animal->getAbility(abilityId));
		abilityFed->decreaseFood();
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