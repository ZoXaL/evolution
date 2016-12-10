#include "controllers/game/GameController.h"
#include "controllers/game/FeedController.h"
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

AbstractController* FeedController::run() {
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
		cout << 1 << ") Feed animal" << endl;
		cout << 2 << ") Use ability" << endl;
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
	cout << "Go feed" << endl;
	int answer = getInt(cin);

	Player* player1 = model->getPlayer(0);
	Player* player2 = model->getPlayer(1);

	PassCommand pass1(player1, true);
	pass1.execute();
	PassCommand pass2(player2, true);
	pass2.execute();
	
	AbstractController* nextController = new GameController();

	return nextController;
}

void FeedController::feedAnimal() {

}
void FeedController::useAnimalAbility() {

}
void FeedController::displayStatistic() {
	FoodStore* foodStore = GameModel::getInstance()->getFoodStore();
	cout << "Food Store capacity: " << foodStore->getCapacity() << endl;
}

void FeedController::pass() {
	GameModel* model = GameModel::getInstance();
	Player* currentPlayer = model->getCurrentPlayer();

	PassCommand pass(currentPlayer);
	pass.execute();
	EndMoveCommand endMove;
	endMove.execute();
}