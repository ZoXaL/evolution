#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <climits>
#include "model/cards/abilities/Ability.h"
#include "model/cards/AnimalCard.h"
#include "model/cards/AbilityCard.h"
#include "model/GamePhaze.h"
#include "model/Player.h"
#include "controllers/commands/CommandType.h"

int getInt(std::istream&, int min=INT_MIN, int max=INT_MAX);
bool checkRange(int, int, int);
int abilityToInt(Ability::AbilityType);
string abilityToString(Ability::AbilityType);
string phazeToString(GamePhaze::Phaze);
int getPlayerId(Player*);
int getAnimalId(Player*, AnimalCard*);
int getAbilityId(AnimalCard*, AbilityCard*);

#endif