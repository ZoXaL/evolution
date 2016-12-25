#ifndef TRANSACTION_EXCEPTION
#define TRANSACTION_EXCEPTION
#include "Exception.h"
#include <string>

class TransactionException : public Exception {
public:
	TransactionException(std::string);
};
#endif