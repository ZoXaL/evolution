#include "controllers/commands/GiveCardToPlayerCommand.h"
#include "model/GameModel.h"
#include "model/Player.h"
#include "model/deck/Deck.h"


GiveCardToPlayerCommand::GiveCardToPlayerCommand(int playerId) {
	this->playerId = playerId;
}
GiveCardToPlayerCommand::GiveCardToPlayerCommand(Player* player) {
	this->playerId = (GameModel::getInstance()->getPlayer(0) == player) ? 0 : 1;
}

void GiveCardToPlayerCommand::execute() {
	GameModel* model = GameModel::getInstance();
	Player* player = model->getPlayer(playerId);
	Deck<shared_ptr<AbilityCard>>* cardDeck = model->getCardDeck();

	player->pushCardToHand(cardDeck->pop_back());
}

void GiveCardToPlayerCommand::undo() {
	GameModel* model = GameModel::getInstance();
	Player* player = model->getPlayer(playerId);
	Deck<shared_ptr<AbilityCard>>* cardDeck = model->getCardDeck();

	shared_ptr<AbilityCard> card = player->popCardFromHand();
	cardDeck->push_back(card);
}