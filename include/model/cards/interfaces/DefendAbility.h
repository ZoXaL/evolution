#ifndef DEFEND_ABILITY_H
#define DEFEND_ABILITY_H
#include <iostream>

class DefendAbility {
public:
	virtual bool defend(Animal* hunter) = 0;
};
#endif