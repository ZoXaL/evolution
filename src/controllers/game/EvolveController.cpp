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
	system("clear");
	// cout << "Here will be GameModel view" << endl<< endl<< endl;
	GameModel* model = GameModel::getInstance();
	Player* currentPlayer = model->getCurrentPlayer();

	displayModel();
	cout << endl;

	cout << "Select operation: " << endl;
	int handSize = currentPlayer->handSize();
	for (int i = 1; i <= handSize; i++) {
		cout << i << ") Lay card " << i << endl;
	}
	cout << handSize+1 << ") Undo" << endl;
	cout << handSize+2 << ") Return to menu" << endl;

	int answer = getInt(cin, 1, handSize+2);
	if (checkRange(answer, 1, handSize)) {
		cout << "Ok, lay " << answer << " card" << endl;
		return new GameController();
	} else {
		do {			
			switch (answer-handSize) {
				
				case 1 : {
					cout << "Ok, do undo" << endl;
					return new GameController();
				} 
				case 2 : {
					return new MenuController();
				} 
				default : {
					continue;
				}
			}
		} while (1);
	}
	
	return new GameController();
}
// void EvolveController::printGameModel() {
// 	GameModel* model = GameModel::getInstance();
// 	auto deck = model->getCardDeck();
// 	while(!deck->isEmpty()) {
// 		Card* card = deck->getCard();
// 		cout << "Card in deck:" << card->getAbilityCard()->getAbility() << endl;
// 	}
// }