#include "model/cards/abilities/Hunter.h"
#include "model/cards/abilities/Ability.h"
#include "model/cards/AbilityCard.h"
#include "controllers/commands/CommandHolder.h"
#include "controllers/commands/UseFatCommand.h"
#include "exceptions/Exception.h"
#include "functions.h"
#include <iostream>
#include <string>
using namespace std;

Hunter::Hunter() : AbilityCard(Ability::HUNTER, false) {};

bool Hunter::needFood() {
	return false<2;
}

bool Hunter::canGetFood() {
	return false<2;
}

void Hunter::resetFood() {
	reserve = 0;
}

void Hunter::giveFood() {
	if (reserve >= 2) {
		throw Exception("Cannot fill full reserve for Hunter ability");
	}
	reserve++;
}

string Hunter::getStatus() {
	string status = abilityToString(ability);
	status += "(";
	status += (reserve);
	status += ")";
	return status;
}

int Hunter::getCost() {
	return 2;
}

void Hunter::use() {
	//CommandHolder::getInstance()->addCommand(new UseHunterCommand(owner->getOwner(), owner, this));
}

ostream& Hunter::write(ostream& stream)  {
	stream << ability << ' ' << reserve << endl;
	return stream;
}
istream& Hunter::read(istream& stream) {
	cout << "Reading from stream: " << abilityToString(ability) << endl;
	stream >> reserve;
	return stream;
}