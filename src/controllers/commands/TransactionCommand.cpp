#include "controllers/commands/TransactionCommand.h"
#include "controllers/commands/CommandType.h"
#include "model/GamePhaze.h"

#include "controllers/commands/AddAbilityCommand.h"
#include "controllers/commands/ClearAnimalFoodCommand.h"
#include "controllers/commands/CreateAnimalCommand.h"
#include "controllers/commands/EndMoveCommand.h"
#include "controllers/commands/FeedCommand.h"
#include "controllers/commands/GiveCardToPlayerCommand.h"
#include "controllers/commands/KillAnimalCommand.h"
#include "controllers/commands/PassCommand.h"
#include "controllers/commands/PopFoodCommand.h"
#include "controllers/commands/SwitchPhazeCommand.h"
#include "controllers/commands/TransactionCommand.h"
#include "controllers/commands/UseFatCommand.h"
#include "controllers/commands/ResetUseCommand.h"
#include "exceptions/CommandException.h"
#include "exceptions/IOException.h"
#include "Logger.h"

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
		try {
			for (; i != deck.end(); i++) {
				(*i)->execute();
			}
			(*i)->execute();
		} catch (CommandException& e) {
			Logger::fatal("TransactionCommand: " + e.getMessage());
			throw e;
		}	
	}
}
void TransactionCommand::undo() {
	if (deck.getSize() > 0) {
		auto i = deck.end();
		try {
			for (; i != deck.begin(); i--) {
				(*i)->undo();
			}
			(*i)->undo();
		} catch (CommandException& e) {
			Logger::fatal("TransactionCommand: " + e.getMessage());
			throw e;
		}			
	}
}

int TransactionCommand::getSize() {
	return deck.getSize();
}

ostream& TransactionCommand::write(ostream& stream) {
	stream << type << ' ';
	deck.write(stream);
	return stream;
}
istream& TransactionCommand::read(istream& stream) {
	deck.clear();
	int commandsNum;
	stream >> commandsNum;
	for (int i = 0; i < commandsNum; i++) {
		int commandType;
		stream >> commandType;
		AbstractCommand* command;
		switch (commandType) {
			case (Command::ADD_ABILITY) : {
				Logger::trace("CommandHolder::Reading ADD_ABILITY from file");
				command = new AddAbilityCommand(-1, -1, -1);
				break;
			}
			case (Command::CLEAR_ANIMAL_FOOD) : {
				Logger::trace("CommandHolder::Reading CLEAR_ANIMAL_FOOD from file");
				command = new ClearAnimalFoodCommand(-1, -1);
				break;
			}
			case (Command::CREATE_ANIMAL) : {
				Logger::trace("CommandHolder::Reading CREATE_ANIMAL from file");
				command = new CreateAnimalCommand(-1, -1);
				break;
			}
			case (Command::END_MOVE) : {
				Logger::trace("CommandHolder::Reading END_MOVE from file");
				command = new EndMoveCommand();
				break;
			}
			case (Command::FEED) : {
				Logger::trace("CommandHolder::Reading FEED from file");
				command = new FeedCommand(-1, -1);
				break;
			}
			case (Command::GIVE_CARD_TO_PLAYER) : {
				Logger::trace("CommandHolder::Reading GIVE_CARD_TO_PLAYER from file");
				command = new GiveCardToPlayerCommand(-1);				
				break;
			}
			case (Command::KILL_ANIMAL) : {
				Logger::trace("CommandHolder::Reading KILL_ANIMAL from file");
				command = new KillAnimalCommand(0, 0);
				break;
			}
			case (Command::PASS) : {
				Logger::trace("CommandHolder::Reading PASS from file");
				command = new PassCommand(-1);
				break;
			}
			case (Command::POP_FOOD) : {
				Logger::trace("CommandHolder::Reading POP_FOOD from file");
				command = new PopFoodCommand(-1);
				break;
			}
			case (Command::SWITCH_PHAZE) : {
				Logger::trace("CommandHolder::Reading SWITCH_PHAZE from file");
				command = new SwitchPhazeCommand(GamePhaze::EVOLVE);
				break;
			}
			case (Command::TRANSACTION) : {
				Logger::trace("CommandHolder::Reading TRANSACTION from file");
				command = new TransactionCommand();
				break;
			}
			case (Command::USE_FAT) : {
				Logger::trace("CommandHolder::Reading USE_FAT from file");
				command = new UseFatCommand(nullptr, nullptr, nullptr);
				break;
			}
			case (Command::RESET_USE) : {
				Logger::trace("CommandHolder::Reading RESET_USE from file");
				command = new ResetUseCommand(nullptr, -1, -1, false);
				break;
			}
			default : {
				Logger::fatal("TransactionCommand::read: Unexpected command type");
				throw IOException("Unexpected command type");
			}
		}
		command->read(stream);
		deck.push_back(command);
	}
	return stream;
}