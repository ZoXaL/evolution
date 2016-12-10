#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>
#include <memory>
using namespace std;
#include "interfaces/Serializable.h"

class AbilityCard;

class Card : public Serializable {
public:
	virtual std::string getDescription() = 0;
	virtual AbilityCard* getAbilityCard() = 0;
	virtual ostream& write(ostream&) = 0;
	virtual istream& read(istream&) = 0;
};

#endif