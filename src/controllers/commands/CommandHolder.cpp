#include "controllers/commands/CommandHolder.h"
#include "controllers/commands/AbstractCommand.h"
#include "controllers/commands/TransactionCommand.h"
#include "model/deck/Deck.h"
#include <iostream>

CommandHolder* CommandHolder::instance = new CommandHolder();

CommandHolder* CommandHolder::getInstance() {
	if (instance == nullptr) {
		instance = new CommandHolder();
	}
	return instance;
}
void CommandHolder::deleteInstance() {
	if (instance != nullptr) {
		delete instance;
	}
}
CommandHolder::~CommandHolder() {
	if (deck.getSize() > 0) {
		auto i = deck.begin();
		for (; i != deck.end(); i++) {
			delete (*i);
		}
		delete *(deck.end());
	}
}
void CommandHolder::addCommand(AbstractCommand* command) {
	if (currentTransaction == nullptr) {
		command->execute();
		deck.push_back(command);
	} else {
		currentTransaction->addCommand(command);
	}	
}
TransactionCommand* CommandHolder::openTransaction() {
	if (currentTransaction != nullptr) {
		// TODO: throw exception
		return nullptr;
	}
	currentTransaction = new TransactionCommand();
	return currentTransaction;
}
void CommandHolder::commit() {
	if (currentTransaction == nullptr) {
		// TODO: throw exception
		return;
	}
	currentTransaction->execute();
	deck.push_back(currentTransaction);
	currentTransaction = nullptr;
}

void CommandHolder::rollback() {
	if (currentTransaction == nullptr) {
		// TODO: throw exception
		return;
	}
	delete currentTransaction;
}

void CommandHolder::undo() {
	AbstractCommand* commandToUndo = deck.pop_back();
	commandToUndo->undo();
}