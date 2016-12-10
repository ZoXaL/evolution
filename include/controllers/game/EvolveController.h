#ifndef EVOLVE_CONTROLLER_H
#define EVOLVE_CONTROLLER_H

#include "controllers/AbstractController.h"
#include "ModelView.h"

// Aimed to let player make evolve move
class EvolveController : public AbstractController, public ModelView {
public:
	AbstractController* run();
private:
	void createNewAnimal();
	void useAbility();
	void pass();
};
#endif