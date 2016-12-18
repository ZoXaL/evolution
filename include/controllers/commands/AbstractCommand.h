#ifndef ABSTRACT_COMMAND
#define ABSTRACT_COMMAND

#include "interfaces/Serializable.h"
#include "controllers/commands/CommandType.h"

class AbstractCommand : public Serializable {
protected:
	Command::CommandType type;
public:
	virtual void execute() = 0;
	virtual void undo() = 0;
};
#endif