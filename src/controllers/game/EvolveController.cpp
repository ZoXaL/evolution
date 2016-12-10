#include "controllers/game/GameController.h"
#include "controllers/game/EvolveController.h"
#include "controllers/menu/MenuController.h"
#include "controllers/AbstractController.h"
#include "controllers/commands/AbstractCommand.h"
#include "controllers/commands/CreateAnimalCommand.h"
#include "controllers/commands/AddAbilityCommand.h"
#include "controllers/commands/EndMoveCommand.h"
#include "controllers/commands/PassCommand.h"

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
	for (int i = 1; i <= handSize; i++) {
		cout << i << ")" << currentPlayer->getCardFromHand(i-1)->getDescription() << endl;
	}
	
	int answer = getInt(cin, 1, handSize);
	CreateAnimalCommand createAnimal(currentPlayer, answer-1);
	createAnimal.execute();
	EndMoveCommand endMove;
	endMove.execute();
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

	AddAbilityCommand addAbility(currentPlayer, abilityId-1, animalId-1);
	addAbility.execute();
	EndMoveCommand endMove;
	endMove.execute();
}

void EvolveController::pass() {
	GameModel* model = GameModel::getInstance();
	Player* currentPlayer = model->getCurrentPlayer();

	PassCommand pass(currentPlayer);
	pass.execute();
	EndMoveCommand endMove;
	endMove.execute();
}