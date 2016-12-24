#include "controllers/commands/GiveCardToPlayerCommand.h"
#include "model/GameModel.h"
#include "model/Player.h"
#include "model/deck/Deck.h"
#include "controllers/commands/CommandType.h"

GiveCardToPlayerCommand::GiveCardToPlayerCommand(int playerId) {
	this->playerId = playerId;
	type = Command::GIVE_CARD_TO_PLAYER;
}
GiveCardToPlayerCommand::GiveCardToPlayerCommand(Player* player) {
	this->playerId = (GameModel::getInstance()->getPlayer(0) == player) ? 0 : 1;
	type = Command::GIVE_CARD_TO_PLAYER;
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
ostream& GiveCardToPlayerCommand::write(ostream& stream) {
	stream << type << endl;
	stream << playerId << endl;
	return stream;
}
istream& GiveCardToPlayerCommand::read(istream& stream) {
	stream >> playerId;
	return stream;
}