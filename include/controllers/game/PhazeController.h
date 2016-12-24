#ifndef PHAZE_CONTROLLER_H
#define PHAZE_CONTROLLER_H

#include "model/cards/Animal.h"
#include <memory>


// Aimed to share phaze controllers functionality
class PhazeController {
protected:
	virtual void displayModel(bool showHand = true);
	virtual string displayAnimal(std::shared_ptr<Animal>);
	virtual void displayStatistic();
	virtual void displayAlert();
};
#endif