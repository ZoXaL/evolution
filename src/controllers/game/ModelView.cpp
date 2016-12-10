#include "controllers/game/ModelView.h"
#include "model/GameModel.h"
#include "model/Player.h"
#include "model/deck/Deck.h"
#include "model/cards/Card.h"

#include "functions.h"
#include <iomanip>
using namespace std;

void ModelView::displayModel() {
	GameModel* model = GameModel::getInstance();
	Player* currentPlayer = model->getCurrentPlayer();
	Player* opponent = (model->getPlayer(1) == currentPlayer) ? model->getPlayer(0) : model->getPlayer(1);
	Deck<shared_ptr<Card>>* cardDeck = model->getCardDeck();
	// 80
	cout << "--------------------------------------------------------------------------------" <<  endl;
	cout << left << setw(40) << currentPlayer->getName() << left << setw(40) << opponent->getName();
	Player* lessCardPlayer = (currentPlayer->animalsCount() < opponent->animalsCount()) ? currentPlayer : opponent;
	int i = 0;
	for (; i < lessCardPlayer->animalsCount(); i++) {
		cout << i+1 << ") " << left << setw (36) << currentPlayer->getAnimal(i)->getStatus() << '|'
		 			<< i+1 << ") " << left << setw (37) << opponent->getAnimal(i)->getStatus() << endl;
	}
	if (lessCardPlayer == currentPlayer) {
		for (; i < opponent->animalsCount(); i++) {
			cout << left << setw (39) << " " << '|' << i+1 << ") " << left << setw (37) << opponent->getAnimal(i)->getStatus() << endl;
		}
		
	} else {
		for (; i < currentPlayer->animalsCount(); i++) {
			cout << i+1 << ") " << setw (36) << left << currentPlayer->getAnimal(i)->getStatus() << '|' << endl;
		}
	}
	cout << endl;
	cout << "--------------------------------------------------------------------------------" << endl;	
	cout << "Game statistic:" << endl;
	cout << "Current player: " << currentPlayer->getName() << endl;
	cout << "Current move: " << model->getMove() << endl;
	cout << "Current phaze: " << phazeToString(model->getPhaze()) << endl;
	displayStatistic();
	cout << "--------------------------------------------------------------------------------" << endl;	
	//Player hand
	cout << "Your cards:" << endl;
	for (int i = 0; i < currentPlayer->handSize(); i++) {
		cout << i+1 << ") " << currentPlayer->getCardFromHand(i)->getDescription() << endl;
	}
}
void ModelView::displayStatistic() {
	//cout << "" << endl;
}