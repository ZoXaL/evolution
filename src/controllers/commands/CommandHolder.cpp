#include "controllers/commands/CommandHolder.h"
#include "controllers/commands/AbstractCommand.h"
#include "controllers/commands/TransactionCommand.h"
#include "exceptions/Exception.h"
#include "exceptions/CommandException.h"
#include "exceptions/TransactionException.h"
#include "exceptions/IOException.h"
#include "model/deck/Deck.h"
#include "model/GameModel.h"
#include "model/Player.h"
#include <iostream>
#include "Logger.h"

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
		throw TransactionException("Exception during adding command: Transaction is not opened");
	} else {
		currentTransaction->addCommand(command);
		command->execute();
	}	
}
TransactionCommand* CommandHolder::openTransaction() {
	if (currentTransaction != nullptr) {
		throw TransactionException("Exception during opening transaction: Transaction is already opened");
	}
	currentTransaction = new TransactionCommand();
	return currentTransaction;
}
void CommandHolder::commit() {
	if (currentTransaction == nullptr) {
		throw TransactionException("Exception during commit: Transaction is not opened");
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
		throw TransactionException("Exception during rollback: Transaction is not opened");
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
	AbstractCommand* commandToUndo;
	do {
		try {
			commandToUndo = deck.pop_back();
			commandToUndo->undo();
		} catch (Exception& e) {
			Logger::fatal("CommandHolder: " + e.getMessage());
			throw e;
		}		
	} while(GameModel::getInstance()->getCurrentPlayer() != undoPlayer || undoPlayer->isPassed());
}

bool CommandHolder::canUndo() {
	return (deck.getSize() >= 2 && currentTransaction == nullptr);
}

ostream& CommandHolder::write(ostream& stream) {
	deck.write(stream);
	return stream;
}

istream& CommandHolder::read(istream& stream) {
	int commandsNum;
	deck.clear();
	stream >> commandsNum;
	for (int i = 0; i < commandsNum; i++) {
		int commandType;
		stream >> commandType;
		switch (commandType) {
			case (Command::TRANSACTION) : {
				AbstractCommand* transaction = new TransactionCommand();
				transaction->read(stream);
				deck.push_back(transaction);
				try {
					transaction->execute();
				} catch (CommandException& e) {
					Logger::fatal("CommandHolder: " + e.getMessage());
					throw e;
				}
				break;
			}
			default : {
				throw IOException("Unexpected command type during reading CommandHolder from file");
			}
		}
	}
	return stream;
}
