#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <climits>
#include "model/cards/abilities/Ability.h"
#include "model/GamePhaze.h"

int getInt(std::istream&, int min=INT_MIN, int max=INT_MAX);
int checkRange(int, int, int);
int abilityToInt(Ability::AbilityType);
string abilityToString(Ability::AbilityType);
string phazeToString(GamePhaze::Phaze);

#endif