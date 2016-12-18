#ifndef GAME_MANAGER
#define GAME_MANAGER
#include "model/GameModel.h"
#include <iostream>

class GameManager {
	static bool gameInitialized;
public:
	static GameModel* buildGame(const char* firstPlayerName, const char* secondPlayerName);
	static void saveGame(std::fstream&);
	static bool isGameInitilized();
	// GameModel* loadGame(const char* filePath);
};
#endif