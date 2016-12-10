#ifndef FEED_CONTROLLER_H
#define FEED_CONTROLLER_H

#include "controllers/AbstractController.h"
#include "ModelView.h"

class FeedController : public AbstractController, protected ModelView {
public:
	AbstractController* run();
private:
	void feedAnimal();
	void useAnimalAbility();
protected:
	void displayStatistic();
	void pass();
	// getAvailableMoves();
	
};
#endif