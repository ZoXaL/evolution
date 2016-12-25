#include "exceptions/Exception.h"
#include "exceptions/TransactionException.h"
#include <string>

TransactionException::TransactionException(string message) : Exception("TransactionException: " + message) {
}