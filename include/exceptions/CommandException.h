#ifndef COMMAND_EXCEPTION
#define COMMAND_EXCEPTION
#include "Exception.h"
#include <string>

class CommandException : public Exception {
public:
	CommandException(std::string);
};
#endif
