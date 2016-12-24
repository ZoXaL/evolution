#ifndef ACTIVE_ABILITY_H
#define ACTIVE_ABILITY_H
#include <iostream>

class ActiveAbility {
public:
	virtual void use() = 0;
	virtual bool canUse() = 0;
	virtual void setUsed(bool) = 0;
	virtual ~ActiveAbility() {};
};
#endif