#ifndef FEED_CONTROLLER_H
#define FEED_CONTROLLER_H

#include "controllers/AbstractController.h"
#include "ModelView.h"
#include <memory>
#include <string>

class FeedController : public AbstractController, protected ModelView {
public:
	AbstractController* run();
private:
	static std::string alert;

	void feedAnimal();
	void useAnimalAbility();
protected:
	void displayStatistic();
	string displayAnimal(std::shared_ptr<AnimalCard>);
	void displayAlert();
	void pass();
	// getAvailableMoves();
	
};
#endif