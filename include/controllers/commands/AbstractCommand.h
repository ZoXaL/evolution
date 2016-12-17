#ifndef ABSTRACT_COMMAND
#define ABSTRACT_COMMAND

#include "interfaces/Serializable.h"

class AbstractCommand : public Serializable {
public:
	virtual void execute() = 0;
	virtual void undo() = 0;
};
#endif