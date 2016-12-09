#ifndef GAME_MANAGER
#define GAME_MANAGER
#include "model/GameModel.h"

class GameManager {
public:
	static GameModel* buildGame(const char* firstPlayerName, const char* secondPlayerName);
	// GameModel* saveGame(const char* filePath);
	// GameModel* loadGame(const char* filePath);
};
#endif