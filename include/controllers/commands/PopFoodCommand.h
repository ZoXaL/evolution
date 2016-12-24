#ifndef POP_FOOD_COMMAND
#define POP_FOOD_COMMAND
#include "controllers/commands/AbstractCommand.h"
#include "model/Player.h"
#include "model/cards/Animal.h"
#include <iostream>

class PopFoodCommand: public AbstractCommand {
int count;
public:
	PopFoodCommand(int count);
	void execute();
	void undo();
	std::ostream& write(std::ostream& stream);
	std::istream& read(std::istream& stream);
};
#endif