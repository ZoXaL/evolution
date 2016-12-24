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
#include "controllers/commands/CommandHolder.h"

#include "model/GameModel.h"
#include "model/Player.h"
#include "model/cards/AbilityCard.h"
#include "model/cards/interfaces/ActiveAbility.h"

#include "functions.h"

#include <iostream>
#include <list>
#include <memory>
#include <algorithm>
#include <string>
using namespace std;

string FeedController::alert = "";

AbstractController* FeedController::run() {
	CommandHolder* holder = CommandHolder::getInstance();
	if (holder->isTransactionOpened()) {
		holder->commit();
	}
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
			nextController = new GameController();
			if (currentPlayer->animalsCount() <= 0) {
				alert = "You have no animals";				
				break;
			}
			feedAnimal();
			break;
		} 
		case 2 : {
			nextController = new GameController();
			if (currentPlayer->animalsCount() <= 0) {
				alert = "You have no animals";
				break;
			}
			shared_ptr<Animal> animalToUse = selectAnimalToUse();
			useAnimalAbility(animalToUse);
			break;
		}
		case 3 : {
			pass();
			nextController = new GameController();
			break;
		}
		case 4 : {
			if (holder->canUndo()) {
				CommandHolder::getInstance()->undo();	
			} else {
				alert = "Cannot undo";
			}
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
		shared_ptr<Animal> animal = currentPlayer->getAnimal(i);
		if (animal->canGetFood()) {
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

	// shared_ptr<Animal> hungryAnimal = currentPlayer->getAnimal(hungryAnimals[answer-1]);

	// list<pair<int, shared_ptr<AbilityCard>>> abilitiesToFeed = hungryAnimal->getAbilitiesToFeed();
	// for (auto i = abilitiesToFeed.begin(); i != abilitiesToFeed.end(); i++) {
	// 	cout << distance(abilitiesToFeed.begin(), i)+1 << ") " << i->second->getDescription() << endl;
	// }
	// cancelOption = abilitiesToFeed.size()+1;
	// cout << cancelOption << ") Cancel" << endl;
	// answer = getInt(cin, 1, cancelOption);
	// if (answer == cancelOption) {
	// 	return;
	// }

	CommandHolder* holder = CommandHolder::getInstance();
	holder->openTransaction();
	try {
		holder->addCommand(new FeedCommand(currentPlayer, hungryAnimals[answer-1]));
	} catch (Exception& e) {
		alert = e.getMessage();
		holder->rollback();
		return;
	}	
	holder->addCommand(new PopFoodCommand(1));
	holder->addCommand(new EndMoveCommand());
}
shared_ptr<Animal> FeedController::selectAnimalToUse() {
	//Todo:
	//Check every animal ability
	//Let player choose
	//USE IT!!!
	GameModel* model = GameModel::getInstance();
	Player* currentPlayer = model->getCurrentPlayer();

	cout << "Select animal to use it's ability:" << endl;
	vector<shared_ptr<Animal>>* animals = currentPlayer->getAnimals();
	for (auto i = animals->begin(); i != animals->end(); i++) {
		cout << (i-animals->begin()+1) << ") " << (*i)->getStatus() << endl;
	}
	cout << (animals->size()+1) << ") Cancel" << endl;
	int answer = getInt(cin, 1, animals->size()+1);
	if (answer == (animals->size()+1)) {
		return nullptr;
	}
	return animals->at(answer-1);
}

void FeedController::useAnimalAbility(shared_ptr<Animal> animal) {
	if (animal == nullptr) {
		return;
	}
	cout << "Select animal ability to use:" << endl;
	vector<shared_ptr<AbilityCard>> abilities = animal->getActiveAbilities();
	for (auto i = abilities.begin(); i != abilities.end(); i++) {
		cout << (i-abilities.begin()+1) << ") " << (*i)->getDescription() << endl;
	}
	cout << (abilities.size()+1) << ") Cancel" << endl;
	int answer = getInt(cin, 1, abilities.size()+1);
	if (answer == (abilities.size()+1)) {
		return;
	}
	ActiveAbility* abilityToUse = dynamic_cast<ActiveAbility*>(abilities.at(answer-1).get());
	CommandHolder* holder = CommandHolder::getInstance();
	holder->openTransaction();
	abilityToUse->use();
	holder->addCommand(new EndMoveCommand());
	return;
}

void FeedController::displayStatistic() {
	FoodStore* foodStore = GameModel::getInstance()->getFoodStore();
	cout << "Food Store capacity: " << foodStore->getCapacity() << endl;
	if (alert != "") {
		cout << "Alert: " << alert << endl;
		alert = "";
	}
}

string FeedController::displayAnimal(shared_ptr<Animal> animal) {
	string animalStatus;
	if (animal->isHungry()) {
		animalStatus += "Hungry: ";
	} else {
		animalStatus += "Full: ";
	}
	animalStatus += animal->getStatus();
	return animalStatus;
}


void FeedController::pass() {
	GameModel* model = GameModel::getInstance();
	Player* currentPlayer = model->getCurrentPlayer();

	CommandHolder* holder = CommandHolder::getInstance();
	holder->openTransaction();
	holder->addCommand(new PassCommand(currentPlayer));
	holder->addCommand(new EndMoveCommand());	
}

