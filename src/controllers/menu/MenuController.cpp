#include "controllers/menu/MenuController.h"
#include "controllers/menu/StartGameController.h"
#include "controllers/AbstractController.h"

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
	cout << "Welcome to evolive!" << endl;
	cout << "1) Start new game" << endl;
	cout << "2) Continue game" << endl;
	cout << "3) Load game" << endl;
	cout << "4) Save game" << endl;
	cout << "5) Read instructions" << endl;
	cout << "6) Exit" << endl;
	do {
		int answer = getInt(cin, 1, 6);
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
				cout << "Ok, go save game" << endl;
				return new MenuController();
			}
			case 5 : {
				cout << "Ok, go read instructions" << endl;
				return new MenuController();
			}
			case 6 : {
				cout << "Good bye!" << endl;
				return nullptr;
			} 
			default : {
				continue;
			}
		}
	} while (1);
	
}