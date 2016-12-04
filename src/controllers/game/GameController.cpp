#include "controllers/game/GameController.h"
#include "controllers/game/EvolveController.h"
#include "controllers/AbstractController.h"

#include "model/GameModel.h"

AbstractController* GameController::run() {
	// Select right controller
	return new EvolveController();
}