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
#include "controllers/commands/ResetUseCommand.h"
#include "controllers/commands/EndMoveCommand.h"
#include "controllers/commands/CommandHolder.h"
#include "model/cards/interfaces/ActiveAbility.h"
#include "Logger.h"

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
				CommandHolder* holder = CommandHolder::getInstance();
				try {
					holder->addCommand(new PassCommand(player1, false));
					holder->addCommand(new PassCommand(player2, false));
					holder->addCommand(new SwitchPhazeCommand(GamePhaze::FEED));
				} catch (Exception& e) {
					Logger::warn("GameController: "+e.getMessage());
					throw e;
				}			

				nextController = new FeedController();
				break;
			};
			case GamePhaze::FEED : {
				//Time to kill and clear animals
				deathPhaze();

				if (deckSize == 0) {	
					// game ends
					cout << "Game over, thanks" << endl;
					cout << player1->getName() << " score: " << player1->getScore() << endl;
					cout << player2->getName() << " score: " << player2->getScore() << endl;

					return new MenuController();
				}
				
				CommandHolder* holder = CommandHolder::getInstance();
				try {
					holder->addCommand(new PassCommand(player1, false));
					holder->addCommand(new PassCommand(player2, false));
					holder->addCommand(new SwitchPhazeCommand(GamePhaze::EVOLVE));	
				} catch (Exception& e) {
					Logger::warn("GameController: "+e.getMessage());
					throw e;
				}	
											

				// Time to give more cards to players
				int firstPlayerCardsToGive = player1->animalsCount();
				if (player1->handSize() == 0) firstPlayerCardsToGive = 6;
				int secondPlayerCardsToGive = player2->animalsCount();
				if (player2->handSize() == 0) secondPlayerCardsToGive = 6;
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
				nextController = new EvolveController();
				break;
			}
		}
		return nextController;
	} 
	// Initiate pass event if player has passed
	if (model->getCurrentPlayer()->isPassed()) {
		CommandHolder* holder = CommandHolder::getInstance();
		if (holder->isTransactionOpened()) {
			holder->commit();
		}
		try {
			holder->openTransaction();
			holder->addCommand(new EndMoveCommand());
		} catch (Exception& e) {
			Logger::warn("Exception in passing");
		}		
	}	
	if (model->getPhaze() == GamePhaze::EVOLVE) {
		nextController = new EvolveController();
	}
	if (model->getPhaze() == GamePhaze::FEED) {
		nextController = new FeedController();
	}
	
	return nextController;
}

void GameController::deathPhaze() {
	GameModel* model = GameModel::getInstance();
	Player* player1 = model->getPlayer(0);
	Player* player2 = model->getPlayer(1);
	CommandHolder* holder = CommandHolder::getInstance();

	vector<shared_ptr<Animal>>* animals1 = player1->getAnimals();
	for (auto i = animals1->begin(); i != animals1->end(); i++) {
		if ((*i)->isHungry()) {
			i--;
			holder->addCommand(new KillAnimalCommand(player1, i+1-animals1->begin()));
		} else {
			holder->addCommand(new ClearAnimalFoodCommand(player1, i-animals1->begin()));
		}
		for (auto j = (*i)->getAbilities()->begin(); j != (*i)->getAbilities()->end(); j++) {
			ActiveAbility* activeAbility = dynamic_cast<ActiveAbility*>(j->get());
			if (activeAbility && !activeAbility->canUse()) {
				holder->addCommand(new ResetUseCommand(player1, i+1-animals1->begin(), j-(*i)->getAbilities()->begin(), false));
			}
		}
	}

	vector<shared_ptr<Animal>>* animals2 = player2->getAnimals();
	for (auto i = animals2->begin(); i != animals2->end(); i++) {
		if ((*i)->isHungry()) {
			i--;
			holder->addCommand(new KillAnimalCommand(player2, i+1-animals2->begin()));
		} else {
			holder->addCommand(new ClearAnimalFoodCommand(player2, i-animals2->begin()));
		}
		for (auto j = (*i)->getAbilities()->begin(); j != (*i)->getAbilities()->end(); j++) {
			ActiveAbility* activeAbility = dynamic_cast<ActiveAbility*>(j->get());
			if (activeAbility && !activeAbility->canUse()) {
				holder->addCommand(new ResetUseCommand(player2, i+1-animals2->begin(), j-(*i)->getAbilities()->begin(), false));
			}
		}
	}

}