#ifndef COMMAND_HOLDER_H
#define COMMAND_HOLDER_H
#include "controllers/commands/AbstractCommand.h"
#include "controllers/commands/TransactionCommand.h"
#include "model/deck/Deck.h"
#include <iostream>

class CommandHolder : public Serializable {
	Deck<AbstractCommand*> deck;
	static CommandHolder* instance;
	TransactionCommand* currentTransaction;
	CommandHolder(){};
	~CommandHolder();
public:
	static CommandHolder* getInstance();
	static void deleteInstance();

	void addCommand(AbstractCommand*);

	TransactionCommand* openTransaction();
	void commit();
	void rollback();
	bool isTransactionOpened();
	void undo();
	std::ostream& write(std::ostream& stream){};
	std::istream& read(std::istream& stream){};
};
#endif