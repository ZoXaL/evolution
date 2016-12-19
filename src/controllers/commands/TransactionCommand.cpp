#include "controllers/commands/TransactionCommand.h"
#include "controllers/commands/CommandType.h"

TransactionCommand::TransactionCommand() {
	type = Command::TRANSACTION;
}
TransactionCommand::~TransactionCommand() {
	if (deck.getSize() > 0) {
		for (auto i = deck.begin(); i != deck.end(); i++) {
			delete *i;
		}
		delete *(deck.end());
	}
}

void TransactionCommand::addCommand(AbstractCommand* newCommand) {
	deck.push_back(newCommand);
}
void TransactionCommand::execute() {
	if (deck.getSize() > 0) {
		auto i = deck.begin();
		for (; i != deck.end(); i++) {
			(*i)->execute();
		}
		(*i)->execute();
	}	
}
void TransactionCommand::undo() {
	if (deck.getSize() > 0) {
		auto i = deck.begin();
		for (; i != deck.end(); i++) {
			(*i)->undo();
		}
		(*i)->undo();
	}
}

int TransactionCommand::getSize() {
	return deck.getSize();
}

ostream& TransactionCommand::write(ostream& stream) {
	stream << type << endl;
	deck.write(stream);
	return stream;
}
istream& TransactionCommand::read(istream& stream) {
	// deck.read(stream);
	return stream;
}