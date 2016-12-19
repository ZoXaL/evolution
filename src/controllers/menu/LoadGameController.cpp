#include "controllers/menu/LoadGameController.h"
#include "controllers/menu/MenuController.h"


#include "model/GameModel.h"
#include "model/GameManager.h"
#include "model/Player.h"
#include "model/deck/Deck.h"

#include <fstream>
using namespace std;

AbstractController* LoadGameController::run() {
	cout << "Enter save name: " << endl;
	string saveName;
	cin >> saveName;
	string fullSaveName = "saves/"+saveName;
	fstream loadStream(fullSaveName, ios::in);
	if (!loadStream) {
		cout << "Cannot open file to read data" << endl;
		return new MenuController();
	}	
	GameManager::loadGame(loadStream);
	loadStream.close();
	return new MenuController();
}
