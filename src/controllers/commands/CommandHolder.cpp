#include "controllers/commands/CommandHolder.h"
#include "controllers/commands/AbstractCommand.h"
#include "controllers/commands/TransactionCommand.h"
#include "exceptions/Exception.h"
#include "model/deck/Deck.h"
#include "model/GameModel.h"
#include "model/Player.h"
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
		throw Exception("Transaction is not opened");
	} else {
		currentTransaction->addCommand(command);
		command->execute();
	}	
}
TransactionCommand* CommandHolder::openTransaction() {
	if (currentTransaction != nullptr) {
		throw Exception("Transaction is already opened");
	}
	currentTransaction = new TransactionCommand();
	return currentTransaction;
}
void CommandHolder::commit() {
	if (currentTransaction == nullptr) {
		throw Exception("Transaction is not opened");
	}
	if (currentTransaction->getSize() > 0) {
		deck.push_back(currentTransaction);
	} else {
		delete currentTransaction;
	}	
	currentTransaction = nullptr;
}

void CommandHolder::rollback() {
	if (currentTransaction == nullptr) {
		throw Exception("Transaction is not opened");
	}
	currentTransaction->undo();
	delete currentTransaction;
}

bool CommandHolder::isTransactionOpened() {
	return currentTransaction != nullptr;
}

void CommandHolder::undo() {
	if (currentTransaction != nullptr) {
		throw Exception("Cannot undo because there is opened transaction");
	}
	Player* undoPlayer = GameModel::getInstance()->getCurrentPlayer();
	AbstractCommand* commandToUndo = deck.pop_back();
	commandToUndo->undo();
	if (undoPlayer == GameModel::getInstance()->getCurrentPlayer()) {
		return;
	}
	commandToUndo = deck.pop_back();
	commandToUndo->undo();
}

bool CommandHolder::canUndo() {
	return deck.getSize() >= 2;
}

ostream& CommandHolder::write(ostream& stream) {
	deck.write(stream);
	return stream;
}

istream& CommandHolder::read(istream& stream) {
	//deck.read(stream);
	return stream;
}
