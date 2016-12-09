#include "model/cards/abilities/Fat.h"
#include "exceptions/Exception.h"

bool Fat::hasReserve() {
	return reserve;
}

void Fat::useReserve() {
	reserve = false;
}

void Fat::fillReserve() {
	if (reserve) {
		throw Exception("Cannot fill full reserve for Fat ability");
	}
	reserve = true;
}