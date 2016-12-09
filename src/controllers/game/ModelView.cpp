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
	Deck<Card*>* cardDeck = model->getCardDeck();
	// 80
	cout << "--------------------------------------------------------------------------------" <<  endl;
	cout << left << setw(40) << currentPlayer->getName() << left << setw(40) << opponent->getName() << endl << endl << endl << endl;
	// cout << left << setw(40) << currentPlayer->getName() << left << setw(40) << opponent->getName();
	// Player* lessCardPlayer = (currentPlayer->handSize() < opponent->handSize()) ? currentPlayer : opponent;
	// for (int i = 0; i < lessCardPlayer->handSize(); i++) {
	// 	cout << i << ") " << left << setw (37) << currentPlayer->getCard(i)->getDescription()
	// 	 			<< i << ") " << left << setw (37) << opponent->getCard(i)->getDescription();
	// }
	// if (lessCardPlayer == currentPlayer) {
	// 	cout << left << setw (40) << " " << i << ") " << left << setw (37) << opponent->getCard(i)->getDescription();
	// } else {
	// 	cout << i << ") " << left << setw (37) << currentPlayer->getCard(i)->getDescription();
	// }
	// cout << endl;
	cout << "--------------------------------------------------------------------------------" << endl;	
	cout << "Game statistic:" << endl;
	displayStatistic();
	cout << "--------------------------------------------------------------------------------" << endl;	
	for (int i = 1; i <= currentPlayer->handSize(); i++) {
		cout << i << ") " << currentPlayer->getCard(i)->getDescription() << endl;
	}
}
void ModelView::displayStatistic() {
	cout << "sdafasiuhfwakfjndslak" << endl;
}