#ifndef EVOLVE_CONTROLLER_H
#define EVOLVE_CONTROLLER_H

#include "controllers/AbstractController.h"
#include "ModelView.h"
#include <string>

// Aimed to let player make evolve move
class EvolveController : public AbstractController, protected ModelView {
public:
	AbstractController* run();
private:
	std::string alert;
	void createNewAnimal();
	void useAbility();
	void pass();
};
#endif