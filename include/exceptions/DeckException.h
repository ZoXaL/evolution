#ifndef DECK_EXCEPTION
#define DECK_EXCEPTION
#include "Exception.h"
#include <string>

class DeckException : public Exception {
public:
	DeckException(std::string);
};
#endif
