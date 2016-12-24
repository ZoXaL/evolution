#include "controllers/commands/FeedCommand.h"
#include "model/cards/Card.h"
#include "model/cards/Animal.h"
#include "model/GameModel.h"
#include "model/Player.h"
#include "model/cards/interfaces/FoodModification.h"
#include "controllers/commands/CommandType.h"
#include <memory>

using namespace std;


FeedCommand::FeedCommand(int playerId, int animalId){
	this->playerId = playerId;
	this->animalId = animalId;
	this->abilityId = abilityId;
	type = Command::FEED;
}
FeedCommand::FeedCommand(Player* player, int animalId) {
	this->playerId = (GameModel::getInstance()->getPlayer(0) == player) ? 0 : 1;
	this->animalId = animalId;
	this->abilityId = abilityId;
	type = Command::FEED;
}

void FeedCommand::execute() {
	GameModel* model = GameModel::getInstance();
	Player* player = model->getPlayer(playerId);
	shared_ptr<Animal> animal = player->getAnimal(animalId);
	abilityId = animal->feed();
}

void FeedCommand::undo() {
	GameModel* model = GameModel::getInstance();
	Player* player = model->getPlayer(playerId);
	shared_ptr<Animal> animal = player->getAnimal(animalId);
	if (abilityId == -1) {
		animal->setHungry(true);
	} else {
		FoodModification* abilityFed = dynamic_cast<FoodModification*>(animal->getAbility(abilityId));
		abilityFed->resetFood();
		animal->setNeedFood(true);
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