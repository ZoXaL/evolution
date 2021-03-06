#include "model/cards/abilities/Fat.h"
#include "model/cards/abilities/Ability.h"
#include "model/cards/AbilityCard.h"
#include "controllers/commands/CommandHolder.h"
#include "controllers/commands/UseFatCommand.h"
#include "exceptions/Exception.h"
#include "functions.h"
#include <iostream>
#include <string>
using namespace std;

Fat::Fat() : AbilityCard(Ability::FAT, true) {};

bool Fat::needFood() {
	return false;
}
bool Fat::canGetFood() {
	return !reserve;
}

void Fat::resetFood() {
	reserve = false;
}
void Fat::decreaseFood() {
	reserve = false;
}

void Fat::giveFood() {
	if (reserve) {
		throw Exception("Cannot fill full reserve for Fat ability");
	}
	reserve = true;
}

bool Fat::canUse() {
	return true;
}
void Fat::resetUse() {}

void Fat::setUsed(bool used) {}


string Fat::getStatus() {
	string status = abilityToString(ability);
	status += "(";
	status += (reserve)? "f" : "e";
	status += ")";
	return status;
}

int Fat::getCost() {
	return (reserve) ? 2 : 1;
}

void Fat::use() {
	if (!reserve) {
		return;
	}
	CommandHolder::getInstance()->addCommand(new UseFatCommand(owner->getOwner(), owner, this));
}


AbilityCard* Fat::clone() {
	return new Fat(*this);
}

ostream& Fat::write(ostream& stream)  {
	stream << ability << ' ' << reserve << endl;
	return stream;
}
istream& Fat::read(istream& stream) {
	cout << "Reading from stream: " << abilityToString(ability) << endl;
	stream >> reserve;
	return stream;
}