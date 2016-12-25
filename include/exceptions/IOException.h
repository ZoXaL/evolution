#ifndef IO_EXCEPTION
#define IO_EXCEPTION
#include "Exception.h"
#include <string>

class IOException : public Exception {
public:
	IOException(std::string);
};
#endif