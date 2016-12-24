#ifndef FOOD_MODIFICATION_H
#define FOOD_MODIFICATION_H
#include <iostream>

class FoodModification {
public:
	virtual bool needFood() = 0;
	virtual bool canGetFood() = 0;
	virtual void giveFood() = 0;
	virtual void resetFood() = 0;
	virtual ~FoodModification() {};
	// virtual void takeAwayFood() = 0;
};
#endif