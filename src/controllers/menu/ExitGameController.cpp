#include "controllers/menu/ExitGameController.h"
#include "controllers/commands/CommandHolder.h"
#include "model/GameModel.h"

AbstractController* ExitGameController::run() {
	CommandHolder::deleteInstance();
	GameModel::deleteInstance();
	return nullptr;
}