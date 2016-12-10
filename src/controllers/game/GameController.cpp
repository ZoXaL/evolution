#include "controllers/game/GameController.h"
#include "controllers/game/EvolveController.h"
#include "controllers/game/FeedController.h"
#include "controllers/menu/MenuController.h"
#include "controllers/AbstractController.h"

#include "controllers/commands/PassCommand.h"
#include "controllers/commands/SwitchPhazeCommand.h"
#include "controllers/commands/KillAnimalCommand.h"
#include "controllers/commands/ClearAnimalFoodCommand.h"

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
	if (model->getCardDeck()->isEmpty()) {	
		// game ends
		cout << "Game over, thanks" << endl;
		return new MenuController();
	}
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