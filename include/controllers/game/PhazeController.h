#ifndef PHAZE_CONTROLLER_H
#define PHAZE_CONTROLLER_H

#include "model/cards/Animal.h"
#include "controllers/AbstractController.h"
#include <memory>

// Aimed to share phaze controllers functionality
class PhazeController : public AbstractController {
protected:
	virtual void displayModel(bool showHand = true);
	virtual string displayAnimal(std::shared_ptr<Animal>);
	virtual void displayStatistic();
	virtual void displayAlert();
	virtual void pass();
};
#endif