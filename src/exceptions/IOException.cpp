#include "exceptions/Exception.h"
#include "exceptions/IOException.h"
#include <string>

IOException::IOException(string message) : Exception("IOException: " + message) {
}