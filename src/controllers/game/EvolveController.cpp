#include "controllers/game/GameController.h"
#include "controllers/game/EvolveController.h"
#include "controllers/menu/MenuController.h"
#include "controllers/AbstractController.h"
#include "controllers/commands/AbstractCommand.h"
#include "controllers/commands/CreateAnimalCommand.h"
#include "controllers/commands/AddAbilityCommand.h"
#include "controllers/commands/EndMoveCommand.h"
#include "controllers/commands/PassCommand.h"
#include "controllers/commands/TransactionCommand.h"
#include "controllers/commands/CommandHolder.h"

#include "model/GameModel.h"
#include "model/Player.h"
#include "model/cards/AbilityCard.h"

#include "functions.h"

#include <iostream>
#include <list>
#include <memory>
using namespace std;
/*
	TODO:
		* Get move
		* Dialog for move
		* Create command
 */
AbstractController* EvolveController::run() {
	//Здесь закончился предыдущий ход
	CommandHolder* holder = CommandHolder::getInstance();
	if (holder->isTransactionOpened()) {
		holder->commit();
	}
	system("clear");
	GameModel* model = GameModel::getInstance();
	Player* currentPlayer = model->getCurrentPlayer();
	// cout << "Here will be GameModel view" << endl<< endl<< endl;

	displayModel();
	cout << endl;

	cout << "Select operation: " << endl;
	if (currentPlayer->handSize() <= 0) {
		cout << 1 << ") Pass" << endl;
		cout << 2 << ") Undo" << endl;
		cout << 3 << ") Return to menu" << endl;

		int answer = getInt(cin, 1, 3);
		AbstractController* nextController = nullptr;
		switch (answer) {
			case 1 : {
				pass();
				nextController = new GameController();
				break;
			} 
			case 2 : {
				cout << "Ok, do undo" << endl;
				if (holder->canUndo()) {
					CommandHolder::getInstance()->undo();	
				}				
				nextController = new GameController();
				break;
			} 
			case 3 : {
				nextController = new MenuController();
				break;
			} 
		}
		return nextController;
	} else {
		cout << 1 << ") Create animal" << endl;
		cout << 2 << ") Use ability" << endl;
		cout << 3 << ") Pass" << endl;
		cout << 4 << ") Undo" << endl;
		cout << 5 << ") Return to menu" << endl;

		int answer = getInt(cin, 1, 5);
		AbstractController* nextController = nullptr;
		switch (answer) {
			case 1 : {
				createNewAnimal();
				nextController = new GameController();
				break;
			} 
			case 2 : {
				if (currentPlayer->animalsCount() <= 0) {
					alert = "You have no animals";
					nextController = new GameController();
					break;
				}
				useAbility();
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
				if (holder->canUndo()) {
					CommandHolder::getInstance()->undo();	
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
}
void EvolveController::createNewAnimal() {
	GameModel* model = GameModel::getInstance();
	Player* currentPlayer = model->getCurrentPlayer();
	int handSize = currentPlayer->handSize();
	
	cout << "Create animal from: " << endl;
	int i = 1;
	for (; i <= handSize; i++) {
		cout << i << ") " << currentPlayer->getCardFromHand(i-1)->getDescription() << endl;
	}
	cout << i << ") Cancel" << endl;
	int answer = getInt(cin, 1, i);
	if (answer == i) {
		return;
	}
	CommandHolder* holder = CommandHolder::getInstance();
	holder->openTransaction();
	holder->addCommand(new CreateAnimalCommand(currentPlayer, answer-1));
	holder->addCommand(new EndMoveCommand());
	return;
}

void EvolveController::useAbility() {	
	GameModel* model = GameModel::getInstance();
	Player* currentPlayer = model->getCurrentPlayer();
	int handSize = currentPlayer->handSize();
	int animalsCount = currentPlayer->animalsCount();
	
	cout << "Select ability to use: " << endl;
	int i = 1;
	for (; i <= handSize; i++) {
		cout << i << ") " << currentPlayer->getCardFromHand(i-1)->getDescription() << endl;
	}
	int abilityId = getInt(cin, 1, handSize);

	cout << "Select animal to evolve: " << endl;
	i = 1;
	for (; i <= animalsCount; i++) {
		cout << i << ") " << currentPlayer->getAnimal(i-1)->getStatus() << endl;
	}
	cout << i << ") Cancel" << endl;
	int animalId = getInt(cin, 1, i);
	if (animalId == i) {
		return;
	}
	CommandHolder* holder = CommandHolder::getInstance();
	holder->openTransaction();
	holder->addCommand(new AddAbilityCommand(currentPlayer, abilityId-1, animalId-1));
	holder->addCommand(new EndMoveCommand());
}

void EvolveController::pass() {
	GameModel* model = GameModel::getInstance();
	Player* currentPlayer = model->getCurrentPlayer();

	CommandHolder* holder = CommandHolder::getInstance();
	holder->openTransaction();
	holder->addCommand(new PassCommand(currentPlayer));
	holder->addCommand(new EndMoveCommand());
}