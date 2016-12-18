#ifndef TRANSACTION_COMMAND
#define TRANSACTION_COMMAND
#include "controllers/commands/AbstractCommand.h"
#include "model/GamePhaze.h"
#include "model/deck/Deck.h"
#include <iostream>

class TransactionCommand: public AbstractCommand {
	Deck<AbstractCommand*> deck;
public:
	TransactionCommand();
	~TransactionCommand();
	void addCommand(AbstractCommand*);
	void execute();
	void undo();
	int getSize();
	std::ostream& write(std::ostream& stream){};
	std::istream& read(std::istream& stream){};
};
#endif