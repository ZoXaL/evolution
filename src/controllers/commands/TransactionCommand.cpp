#include "controllers/commands/TransactionCommand.h"

TransactionCommand::TransactionCommand() {

}
TransactionCommand::~TransactionCommand() {
	for (auto i = deck.begin(); i != deck.end(); i++) {
		delete *i;
	}
	delete *(deck.end());
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
	AbstractCommand* lastCommand = deck.pop_back();
	if (lastCommand != nullptr) {
		lastCommand->undo();
		delete lastCommand;
	}
}
