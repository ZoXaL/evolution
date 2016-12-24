#include "controllers/commands/ClearAnimalFoodCommand.h"
#include "model/cards/Card.h"
#include "model/cards/AnimalCard.h"
#include "model/GameModel.h"
#include "model/Player.h"
#include "controllers/commands/CommandType.h"

ClearAnimalFoodCommand::ClearAnimalFoodCommand(int playerId, int animalId){
	this->playerId = playerId;
	this->animalId = animalId;
	type = Command::CLEAR_ANIMAL_FOOD;
}
ClearAnimalFoodCommand::ClearAnimalFoodCommand(Player* player,int animalId) {
	this->playerId = (GameModel::getInstance()->getPlayer(0) == player) ? 0 : 1;
	this->animalId = animalId;
	type = Command::CLEAR_ANIMAL_FOOD;
}

void ClearAnimalFoodCommand::execute() {
	GameModel* model = GameModel::getInstance();
	Player* player = model->getPlayer(playerId);
	shared_ptr<AnimalCard> animal = player->getAnimal(animalId);
	wasHungry = animal->isHungry();
	neededFood = animal->needFood();
	animal->setHungry(true);
}

void ClearAnimalFoodCommand::undo() {
	GameModel* model = GameModel::getInstance();
	Player* player = model->getPlayer(playerId);
	shared_ptr<AnimalCard> animal = player->getAnimal(animalId);
	animal->setHungry(wasHungry);
	animal->setNeedFood(neededFood);
}

ostream& ClearAnimalFoodCommand::write(ostream& stream) {
	stream << type << endl;
	stream << playerId << ' ' << animalId << ' ' << wasHungry << ' ' << neededFood << endl;
	return stream;
}

istream& ClearAnimalFoodCommand::read(istream& stream) {
	stream >> playerId;
	stream >> animalId;
	stream >> wasHungry;
	stream >> neededFood;
	return stream;
}