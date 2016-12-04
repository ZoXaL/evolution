#include "controllers/game/GameController.h"
#include "controllers/game/EvolveController.h"
#include "controllers/menu/MenuController.h"
#include "controllers/AbstractController.h"

#include "model/GameModel.h"
#include "model/Player.h"
#include "model/cards/AbilityCard.h"

#include "functions.h"

#include <iostream>
using namespace std;

AbstractController* EvolveController::run() {
	// cout << "Here will be GameModel view" << endl<< endl<< endl;
	GameModel* model = GameModel::getInstance();
	cout << "The players now are " << model->getPlayer(0)->getName() << " and " << model->getPlayer(1)->getName() << endl;
	printGameModel();
	cout << "Select operation: " << endl;
	cout << "1) Lay card 1" << endl;
	cout << "2) Lay card 2" << endl;
	cout << "3) Lay card 3" << endl;
	cout << "4) Undo" << endl;
	cout << "5) Return to menu" << endl;
	do {
		int answer = getInt(cin, 1, 5);
		switch (answer) {
			case 1 : {
				cout << "Ok, lay 1 card" << endl;
				return new GameController();
			} 
			case 2 : {
				cout << "Ok, lay 2 card" << endl;
				return new GameController();
			} 
			case 3 : {
				cout << "Ok, lay 3 card" << endl;
				return new GameController();
			} 
			case 4 : {
				cout << "Ok, do undo" << endl;
				return new GameController();
			} 

			case 5 : {
				return new MenuController();
			} 
			default : {
				continue;
			}
		}
	} while (1);
	return new GameController();
}
void EvolveController::printGameModel() {
	GameModel* model = GameModel::getInstance();
	auto deck = model->getCardDeck();
	while(!deck->isEmpty()) {
		Card* card = deck->getCard();
		cout << "Card in deck:" << card->getAbilityCard()->getAbility() << endl;
	}
}