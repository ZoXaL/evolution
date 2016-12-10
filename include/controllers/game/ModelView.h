#ifndef MODEL_VIEW_H
#define MODEL_VIEW_H

#include "model/cards/AnimalCard.h"
#include <memory>


// Aimed to share displayModel functionality
class ModelView {
protected:
	virtual void displayModel(bool showHand = true);
	virtual string displayAnimal(std::shared_ptr<AnimalCard>);
	virtual void displayStatistic();
	virtual void displayAlert();
};
#endif