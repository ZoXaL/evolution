#include "controllers/menu/MenuController.h"
#include "controllers/menu/StartGameController.h"
#include "controllers/menu/SaveGameController.h"
#include "controllers/menu/ExitGameController.h"
#include "controllers/AbstractController.h"
#include "model/GameManager.h"

#include <iostream>
using namespace std;

#include "functions.h"

MenuController::MenuController() {

}

AbstractController* MenuController::run() {
	return showMainMenu();
}

AbstractController* MenuController::showMainMenu() {
	//system("clear");
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
					cout << "Ok, go load game" << endl;
					return new MenuController();
				}
				case 4 : {
					return new SaveGameController();
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
					cout << "Ok, go load game" << endl;
					return new MenuController();
				}
				case 4 : {
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