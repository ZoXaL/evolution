#include "controllers/game/GameController.h"
#include "controllers/game/EvolveController.h"
#include "controllers/game/FeedController.h"
#include "controllers/menu/MenuController.h"
#include "controllers/AbstractController.h"

#include "controllers/commands/PassCommand.h"
#include "controllers/commands/SwitchPhazeCommand.h"
#include "controllers/commands/KillAnimalCommand.h"
#include "controllers/commands/ClearAnimalFoodCommand.h"
#include "controllers/commands/GiveCardToPlayerCommand.h"
#include "controllers/commands/CommandHolder.h"

#include "model/GameModel.h"
#include "model/GamePhaze.h"

AbstractController* GameController::run() {
	// Select right controller
	// TODO:
	// 1) check if game ends
	// 2) check if game must switch phaze
	// 2.1) if so, prepare model for new phaze
	AbstractController* nextController = nullptr;
	GameModel* model = GameModel::getInstance();
	int deckSize = model->getCardDeck()->getSize();
	Player* player1 = model->getPlayer(0);
	Player* player2 = model->getPlayer(1);
	//need change phaze
	if (player1->isPassed() && player2->isPassed()) {
		
		switch (model->getPhaze()) {
			case GamePhaze::EVOLVE : {				

				PassCommand pass1(player1, false);
				pass1.execute();
				PassCommand pass2(player2, false);
				pass2.execute();
				SwitchPhazeCommand switchPhaze(GamePhaze::FEED);
				switchPhaze.execute();

				nextController = new FeedController();
				break;
			};
			case GamePhaze::FEED : {

				PassCommand pass1(player1, false);
				pass1.execute();
				PassCommand pass2(player2, false);
				pass2.execute();
				SwitchPhazeCommand switchPhaze(GamePhaze::EVOLVE);
				switchPhaze.execute();

				//Time to kill and clear animals
				deathPhaze();

				if (deckSize == 0 && model->getPhaze() == GamePhaze::FEED ) {	
					// game ends
					cout << "Game over, thanks" << endl;
					cout << player1->getName() << " score: " << player1->getScore() << endl;
					cout << player2->getName() << " score: " << player2->getScore() << endl;
					return new MenuController();
				}

				// Time to give more cards to players
				int firstPlayerCardsToGive = player1->animalsCount();
				if (firstPlayerCardsToGive == 0) firstPlayerCardsToGive = 6;
				int secondPlayerCardsToGive = player2->animalsCount();
				if (secondPlayerCardsToGive == 0) secondPlayerCardsToGive = 6;
				Player* minCardsPlayer;
				int minCardsGive = 0;
				Player* maxCardsPlayer;
				int maxCardsGive = 0;
				if (firstPlayerCardsToGive < secondPlayerCardsToGive) {
					minCardsPlayer = player1;
					minCardsGive = firstPlayerCardsToGive;
					maxCardsPlayer = player2;
					maxCardsGive = secondPlayerCardsToGive;
				} else {
					minCardsPlayer = player2;
					minCardsGive = secondPlayerCardsToGive;
					maxCardsPlayer = player1;
					maxCardsGive = firstPlayerCardsToGive;
				}
				int tmpDeckSize = deckSize;
				CommandHolder* holder = CommandHolder::getInstance();
				holder->openTransaction();
				for (int i = 0; i < minCardsGive; i++) {
					if (tmpDeckSize <= 0) break;					
					holder->addCommand(new GiveCardToPlayerCommand(minCardsPlayer));
					tmpDeckSize--;

					if (tmpDeckSize <= 0) break;
					holder->addCommand(new GiveCardToPlayerCommand(maxCardsPlayer));
					tmpDeckSize--;
				}
				for (int i = minCardsGive; i < maxCardsGive; i++) {
					if (tmpDeckSize <= 0) break;
					holder->addCommand(new GiveCardToPlayerCommand(maxCardsPlayer));
					tmpDeckSize--;
				}
				holder->commit();

				nextController = new EvolveController();
				break;
			}
		}
	} else {
		if (model->getPhaze() == GamePhaze::EVOLVE) {
		nextController = new EvolveController();
		}
		if (model->getPhaze() == GamePhaze::FEED) {
			nextController = new FeedController();
		}
	}
	return nextController;
}

void GameController::deathPhaze() {
	GameModel* model = GameModel::getInstance();
	Player* player1 = model->getPlayer(0);
	Player* player2 = model->getPlayer(1);

	vector<shared_ptr<AnimalCard>>* animals1 = player1->getAnimals();
	for (auto i = animals1->begin(); i != animals1->end(); i++) {
		if ((*i)->isHungry()) {
			i--;
			KillAnimalCommand kill(player1, i+1-animals1->begin());
			kill.execute();
		} else {
			ClearAnimalFoodCommand clear(player1, i-animals1->begin());
			clear.execute();
		}
	}

	vector<shared_ptr<AnimalCard>>* animals2 = player2->getAnimals();
	for (auto i = animals2->begin(); i != animals2->end(); i++) {
		if ((*i)->isHungry()) {
			i--;
			KillAnimalCommand kill(player2, i+1-animals2->begin());
			kill.execute();
		} else {
			ClearAnimalFoodCommand clear(player2, i-animals2->begin());
			clear.execute();
		}
	}

}