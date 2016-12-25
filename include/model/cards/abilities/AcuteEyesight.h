#ifndef ACUTE_EYESIGHT_H
#define ACUTE_EYESIGHT_H

#include "model/cards/AbilityCard.h"
#include <iostream>
#include <string>

class AcuteEyesight : public AbilityCard {
int reserve;
public:
	AcuteEyesight();
	virtual ~AcuteEyesight() {};

	AbilityCard* clone();

	std::string getStatus();
	int getCost();

	std::ostream& write(std::ostream&);
	std::istream& read(std::istream&);
};

#endif