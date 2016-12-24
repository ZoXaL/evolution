#ifndef GAME_MANAGER
#define GAME_MANAGER
#include "model/GameModel.h"
#include <iostream>
#include <list>
#include "model/deck/Deck.h"
#include "model/cards/AbilityCard.h"

class GameManager {
	static bool gameInitialized;
	static list<shared_ptr<AbilityCard>> startDeck;
public:
	static GameModel* buildGame(const char* firstPlayerName, const char* secondPlayerName);
	static void saveGame(std::fstream&);
	static bool isGameInitilized();
	static GameModel* loadGame(std::fstream&);
private:
	static void giveCardsToPlayers(Deck<shared_ptr<AbilityCard>>*);
};
#endif