#include "controllers/menu/SaveGameController.h"
#include "controllers/menu/MenuController.h"


#include "model/GameModel.h"
#include "model/GameManager.h"
#include "model/Player.h"
#include "model/deck/Deck.h"

#include <fstream>
using namespace std;

AbstractController* SaveGameController::run() {
	cout << "Enter save name: " << endl;
	string saveName;
	cin >> saveName;
	string fullSaveName = "saves/"+saveName;
	fstream saveStream(fullSaveName, ios::out | ios::trunc);
	if (!saveStream) {
		cout << "Cannot open file to write data" << endl;
		Logger::warn("Cannot open "+saveName+" to write data");
		return new MenuController();
	}	
	GameManager::saveGame(saveStream);
	saveStream.close();
	return new MenuController();
}
