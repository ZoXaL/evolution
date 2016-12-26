#ifndef FEED_CONTROLLER_H
#define FEED_CONTROLLER_H

#include "controllers/AbstractController.h"
#include "model/cards/Animal.h"
#include "PhazeController.h"
#include <memory>
#include <string>

class FeedController : protected PhazeController {
public:
	AbstractController* run();
private:
	static std::string alert;
	void feedAnimal();
	void useAnimalAbility(std::shared_ptr<Animal>);
	shared_ptr<Animal> selectAnimalToUse();
protected:
	void displayStatistic();
	string displayAnimal(std::shared_ptr<Animal>);
};
#endif