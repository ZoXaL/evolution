#include "controllers/menu/MenuController.h"
#include "controllers/menu/StartGameController.h"
#include "controllers/menu/SaveGameController.h"
#include "controllers/menu/LoadGameController.h"
#include "controllers/menu/ExitGameController.h"
#include "controllers/AbstractController.h"
#include "model/GameManager.h"
#include "model/GameModel.h"
#include "model/Player.h"
#include "exceptions/IOException.h"

#include <iostream>
using namespace std;

#include "functions.h"

string MenuController::alert = "";

MenuController::MenuController() {
	this->firstPlayerScore = -1;
	this->secondPlayerScore = -1;
}

MenuController::MenuController(int firstPlayerScore, int secondPlayerScore) {
	this->firstPlayerScore = firstPlayerScore;
	this->secondPlayerScore = secondPlayerScore;
}

AbstractController* MenuController::run() {
	return showMainMenu();
}

AbstractController* MenuController::showMainMenu() {
	system("clear");
	if (alert != "") {
		cout << alert << endl;
		alert = "";
	}
	Player* player1 = GameModel::getInstance()->getPlayer(0);
	Player* player2 = GameModel::getInstance()->getPlayer(1);
	if (firstPlayerScore != -1 && secondPlayerScore != -1) {
		cout << "Game over, thanks" << endl;
		cout << player1->getName() << " score: " << firstPlayerScore << endl;
		cout << player2->getName() << " score: " << secondPlayerScore << endl;
	}	
	if (GameManager::isGameInitilized()) {
		cout << "Welcome to evolive!" << endl;
		cout << "1) Start new game" << endl;
		cout << "2) Continue game" << endl;
		cout << "3) Load game" << endl;
		cout << "4) Save game" << endl;
		cout << "5) Exit" << endl;
		do {
			int answer = getInt(cin, 1, 5);
			switch (answer) {
				case 1 : {
					return new StartGameController(true);
				} 
				case 2 : {
					return new StartGameController(false);
				}
				case 3 : {
					AbstractController* loadGame = new LoadGameController();
					try {
						return loadGame->run();
					} catch (IOException& e) {
						alert = e.getMessage();
						return new MenuController();
					}
				}
				case 4 : {
					AbstractController* saveGame = new SaveGameController();
					try {
						return saveGame->run();
					} catch (IOException& e) {
						alert = e.getMessage();
						return new MenuController();
					}
				}
				case 5 : {
					cout << "Good bye!" << endl;
					return new ExitGameController();
				} 
				default : {
					continue;
				}
			}
		} while (1);
	} else {
		cout << "Welcome to evolive!" << endl;
		cout << "1) Start new game" << endl;
		cout << "2) Load game" << endl;
		cout << "3) Exit" << endl;
		do {
			int answer = getInt(cin, 1, 3);
			switch (answer) {
				case 1 : {
					return new StartGameController(true);
				} 
				case 2 : {
					AbstractController* loadGame = new LoadGameController();
					try {
						return loadGame->run();
					} catch (IOException& e) {
						alert = e.getMessage();
						return new MenuController();
					}
				}
				case 3 : {
					cout << "Good bye!" << endl;
					return new ExitGameController();
				} 
				default : {
					continue;
				}
			}
		} while (1);
	}
	
	
}