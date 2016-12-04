#ifndef EVOLVE_CONTROLLER_H
#define EVOLVE_CONTROLLER_H

#include "controllers/AbstractController.h"

// Aimed to let player make evolve move
class EvolveController : public AbstractController {
public:
	AbstractController* run();
};
#endif