#include "exceptions/Exception.h"
#include "exceptions/DeckException.h"
#include <string>

DeckException::DeckException(string message) : Exception("DeckException: " + message) {
}