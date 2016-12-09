#include "controllers/commands/GiveCardToPlayerCommand.h"
#include "model/GameModel.h"
#include "model/Player.h"
#include "model/deck/Deck.h"


GiveCardToPlayerCommand::GiveCardToPlayerCommand(int playerId) {
	this->playerId = playerId;
}

void GiveCardToPlayerCommand::execute() {
	GameModel* model = GameModel::getInstance();
	Player* player = model->getPlayer(playerId);
	Deck<shared_ptr<Card>>* cardDeck = model->getCardDeck();

	player->pushCardToHand(cardDeck->pop_back());
}

void GiveCardToPlayerCommand::undo() {

}