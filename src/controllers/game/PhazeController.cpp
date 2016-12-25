#include "controllers/game/PhazeController.h"
#include "model/GameModel.h"
#include "model/Player.h"
#include "model/deck/Deck.h"
#include "model/cards/AbilityCard.h"
#include "model/cards/Animal.h"

#include "functions.h"
#include <iomanip>
#include <memory>
using namespace std;

void PhazeController::displayModel(bool showHand) {
	GameModel* model = GameModel::getInstance();
	Player* currentPlayer = model->getCurrentPlayer();
	Player* opponent = (model->getPlayer(1) == currentPlayer) ? model->getPlayer(0) : model->getPlayer(1);
	Deck<shared_ptr<AbilityCard>>* cardDeck = model->getCardDeck();
	// 80
	cout << "---------------------------------------------------------------------------";
	cout << "---------------------------------------------------------------------------" << endl;
	cout << left << setw(75) << currentPlayer->getName() << left << setw(75) << opponent->getName();
	Player* lessCardPlayer = (currentPlayer->animalsCount() < opponent->animalsCount()) ? currentPlayer : opponent;
	int i = 0;
	for (; i < lessCardPlayer->animalsCount(); i++) {
		cout << i+1 << ") " << left << setw (71) << displayAnimal(currentPlayer->getAnimal(i)) << '|'
		 			<< i+1 << ") " << left << setw (72) << displayAnimal(opponent->getAnimal(i)) << endl;
	}
	if (lessCardPlayer == currentPlayer) {
		for (; i < opponent->animalsCount(); i++) {
			cout << left << setw (74) << " " << '|' << i+1 << ") " << left << setw (72) << displayAnimal(opponent->getAnimal(i)) << endl;
		}
		
	} else {
		for (; i < currentPlayer->animalsCount(); i++) {
			cout << i+1 << ") " << setw (71) << left << displayAnimal(currentPlayer->getAnimal(i)) << '|' << endl;
		}
	}
	cout << endl;
	cout << "---------------------------------------------------------------------------";	
	cout << "---------------------------------------------------------------------------" << endl;	
	cout << "Game statistic:" << endl;
	cout << "Current player: " << currentPlayer->getName() << endl;
	cout << "Current move: " << model->getMove() << endl;
	cout << "Current phaze: " << phazeToString(model->getPhaze()) << endl;
	cout << "Deck size: " << cardDeck->getSize() << endl;
	displayStatistic();
	displayAlert();
	cout << "---------------------------------------------------------------------------";	
	cout << "---------------------------------------------------------------------------" << endl;		
	//Player hand
	if (showHand) {
		cout << "Your cards:" << endl;
		for (int i = 0; i < currentPlayer->handSize(); i++) {
			cout << i+1 << ") " << currentPlayer->getCardFromHand(i)->getDescription() << endl;
		}
	}	
}
void PhazeController::displayStatistic() {
	
}

string PhazeController::displayAnimal(shared_ptr<Animal> animal) {
	return animal->getStatus();
}
void PhazeController::displayAlert() {

}