#ifndef FEED_CONTROLLER_H
#define FEED_CONTROLLER_H

#include "controllers/AbstractController.h"
#include "model/cards/AnimalCard.h"
#include "ModelView.h"
#include <memory>
#include <string>

class FeedController : public AbstractController, protected ModelView {
public:
	AbstractController* run();
private:
	static std::string alert;

	void feedAnimal();
	void useAnimalAbility(std::shared_ptr<AnimalCard>);
	shared_ptr<AnimalCard> selectAnimalToUse();
protected:
	void displayStatistic();
	string displayAnimal(std::shared_ptr<AnimalCard>);
	void pass();
	// getAvailableMoves();
	
};
#endif