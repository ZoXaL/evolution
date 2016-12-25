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
	stream << type << endl;
	deck.write(stream);
	return stream;
}
istream& TransactionCommand::read(istream& stream) {
	deck.clear();
	int commandsNum;
	stream >> commandsNum;
	cout << commandsNum << endl;
	for (int i = 0; i < commandsNum; i++) {
		int commandType;
		stream >> commandType;
		cout << commandsNum << endl;
		AbstractCommand* command;
		switch (commandType) {
			case (Command::ADD_ABILITY) : {
				cout << "CommandHolder::Reading ADD_ABILITY from file" << endl;
				command = new AddAbilityCommand(-1, -1, -1);
				break;
			}
			case (Command::CLEAR_ANIMAL_FOOD) : {
				cout << "CommandHolder::Reading CLEAR_ANIMAL_FOOD from file" << endl;
				command = new ClearAnimalFoodCommand(-1, -1);
				break;
			}
			case (Command::CREATE_ANIMAL) : {
				cout << "CommandHolder::Reading CREATE_ANIMAL from file" << endl;
				command = new CreateAnimalCommand(-1, -1);
				break;
			}
			case (Command::END_MOVE) : {
				cout << "CommandHolder::Reading END_MOVE from file" << endl;
				command = new EndMoveCommand();
				break;
			}
			case (Command::FEED) : {
				cout << "CommandHolder::Reading FEED from file" << endl;
				command = new FeedCommand(-1, -1);
				break;
			}
			case (Command::GIVE_CARD_TO_PLAYER) : {
				cout << "CommandHolder::Reading GIVE_CARD_TO_PLAYER from file" << endl;
				command = new GiveCardToPlayerCommand(-1);				
				break;
			}
			case (Command::KILL_ANIMAL) : {
				cout << "CommandHolder::Reading KILL_ANIMAL from file" << endl;
				command = new KillAnimalCommand(0, 0);
				break;
			}
			case (Command::PASS) : {
				cout << "CommandHolder::Reading PASS from file" << endl;
				command = new PassCommand(-1);
				break;
			}
			case (Command::POP_FOOD) : {
				cout << "CommandHolder::Reading POP_FOOD from file" << endl;
				command = new PopFoodCommand(-1);
				break;
			}
			case (Command::SWITCH_PHAZE) : {
				cout << "CommandHolder::Reading SWITCH_PHAZE from file" << endl;
				command = new SwitchPhazeCommand(GamePhaze::EVOLVE);
				break;
			}
			case (Command::TRANSACTION) : {
				cout << "CommandHolder::Reading TRANSACTION from file" << endl;
				command = new TransactionCommand();
				break;
			}
			case (Command::USE_FAT) : {
				cout << "CommandHolder::Reading USE_FAT from file" << endl;
				command = new UseFatCommand(nullptr, nullptr, nullptr);
				break;
			}
			case (Command::RESET_USE) : {
				cout << "CommandHolder::Reading RESET_USE from file" << endl;
				command = new ResetUseCommand(nullptr, -1, -1, false);
				break;
			}
			default : {
				throw IOException("Unexpected command type");
			}
		}
		command->read(stream);
		deck.push_back(command);
	}
	return stream;
}