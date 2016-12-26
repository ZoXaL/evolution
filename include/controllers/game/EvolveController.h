#ifndef EVOLVE_CONTROLLER_H
#define EVOLVE_CONTROLLER_H

#include "controllers/AbstractController.h"
#include "PhazeController.h"
#include <string>

// Aimed to let player make evolve move
class EvolveController : protected PhazeController {
public:
	AbstractController* run();
private:
	static std::string alert;
	void createNewAnimal();
	void useAbility();	
protected:
	void displayStatistic();
};
#endif