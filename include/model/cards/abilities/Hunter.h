#ifndef HUNTER_H
#define HUNTER_H

#include <string>
#include "model/cards/AbilityCard.h"
#include "model/cards/interfaces/FoodModification.h"
#include "model/cards/interfaces/ActiveAbility.h"
#include <iostream>
#include <string>

class Hunter : public AbilityCard, public FoodModification, public ActiveAbility {
bool reserve;
bool used;
public:
	Hunter();
	virtual ~Hunter() {};

	bool needFood();
	void giveFood();
	void resetFood();
	void decreaseFood();
	bool canGetFood();

	AbilityCard* clone();

	void use();
	bool canUse();
	void resetUse();
	void setUsed(bool);
	
	std::string getStatus();
	int getCost();
	
	std::istream& read(std::istream&);
	std::ostream& write(std::ostream&);
};

#endif