#include "controllers/game/GameController.h"
#include "controllers/game/FeedController.h"
#include "controllers/menu/MenuController.h"
#include "controllers/AbstractController.h"
#include "controllers/commands/AbstractCommand.h"
#include "controllers/commands/CreateAnimalCommand.h"
#include "controllers/commands/AddAbilityCommand.h"
#include "controllers/commands/EndMoveCommand.h"
#include "controllers/commands/PassCommand.h"
#include "controllers/commands/FeedCommand.h"
#include "controllers/commands/PopFoodCommand.h"

#include "model/GameModel.h"
#include "model/Player.h"
#include "model/cards/AbilityCard.h"

#include "functions.h"

#include <iostream>
#include <list>
#include <memory>
#include <string>
using namespace std;

string FeedController::alert = "";

AbstractController* FeedController::run() {
	system("clear");
	GameModel* model = GameModel::getInstance();
	Player* currentPlayer = model->getCurrentPlayer();
	// cout << "Here will be GameModel view" << endl<< endl<< endl;

	displayModel(false);
	cout << endl;
	cout << "Select operation: " << endl;

	cout << 1 << ") Feed animal" << endl;
	cout << 2 << ") Use animal ability" << endl;
	cout << 3 << ") Pass" << endl;
	cout << 4 << ") Undo" << endl;
	cout << 5 << ") Return to menu" << endl;

	int answer = getInt(cin, 1, 5);
	AbstractController* nextController = nullptr;
	switch (answer) {
		case 1 : {
			feedAnimal();
			nextController = new GameController();
			break;
		} 
		case 2 : {
			useAnimalAbility();
			nextController = new GameController();
			break;
		} 
		case 3 : {
			pass();
			nextController = new GameController();
			break;
		} 
		case 4 : {
			cout << "Ok, do undo" << endl;
			nextController = new GameController();
			break;
		} 
		case 5 : {
			nextController = new MenuController();
			break;
		} 
	}
	return nextController;
}

void FeedController::feedAnimal() {
	GameModel* model = GameModel::getInstance();
	Player* currentPlayer = model->getCurrentPlayer();
	FoodStore* foodStore = model->getFoodStore();

	if (foodStore->getCapacity() == 0) {
		alert = "FoodStore is empty";
		return;
	}
	vector<int> hungryAnimals;

	for (int i = 0; i < currentPlayer->animalsCount(); i++) {
		shared_ptr<AnimalCard> animal = currentPlayer->getAnimal(i);
		if (animal->needFood()) {
			hungryAnimals.push_back(i);
			cout << hungryAnimals.size() << ") " << currentPlayer->getAnimal(i)->getStatus() << endl;
		}		
	}

	int cancelOption = hungryAnimals.size()+1;
	cout << cancelOption << ") Cancel" << endl;
	int answer = getInt(cin, 1, cancelOption);
	if (answer == cancelOption) {
		return;
	}
	FeedCommand feed(currentPlayer, hungryAnimals[answer-1]);
	feed.execute();
	PopFoodCommand popFood(1);
	popFood.execute();
	EndMoveCommand endMove;
	endMove.execute();

}
void FeedController::useAnimalAbility() {

}
void FeedController::displayStatistic() {
	FoodStore* foodStore = GameModel::getInstance()->getFoodStore();
	cout << "Food Store capacity: " << foodStore->getCapacity() << endl;
}

string FeedController::displayAnimal(shared_ptr<AnimalCard> animal) {
	string animalStatus;
	if (animal->isHungry()) {
		animalStatus += "Hungry: ";
	} else {
		animalStatus += "Full: ";
	}
	animalStatus += animal->getStatus();
	return animalStatus;
}

void FeedController::displayAlert() {
	if (alert != "") {
		cout << alert << endl;
	}
	alert = "";
}

void FeedController::pass() {
	GameModel* model = GameModel::getInstance();
	Player* currentPlayer = model->getCurrentPlayer();

	PassCommand pass(currentPlayer);
	pass.execute();
	EndMoveCommand endMove;
	endMove.execute();
}

