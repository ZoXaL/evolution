#include "exceptions/Exception.h"
#include "exceptions/CommandException.h"
#include <string>

CommandException::CommandException(string message) : Exception("CommandException: " + message) {
}