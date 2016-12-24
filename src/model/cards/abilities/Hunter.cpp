#include "model/cards/abilities/Hunter.h"
#include "model/cards/abilities/Ability.h"
#include "model/cards/AbilityCard.h"
#include "model/GameModel.h"
#include "controllers/commands/CommandHolder.h"
#include "controllers/commands/FeedCommand.h"
#include "controllers/commands/KillAnimalCommand.h"
#include "controllers/commands/ResetUseCommand.h"
#include "exceptions/Exception.h"
#include "functions.h"
#include <iostream>
#include <string>
using namespace std;

Hunter::Hunter() : AbilityCard(Ability::HUNTER, false) {
	reserve = false;
	used = false;
};

bool Hunter::needFood() {
	return !reserve;
}
bool Hunter::canGetFood() {
	return !reserve;
}

void Hunter::resetFood() {
	reserve = false;
}
void Hunter::decreaseFood() {
	reserve = false;
}

void Hunter::giveFood() {
	if (reserve) {
		throw Exception("Cannot fill full reserve for Hunter ability");
	}
	reserve = true;
}

bool Hunter::canUse() {
	return !used;
}
void Hunter::resetUse() {
	used = false;
}
void Hunter::setUsed(bool used) {
	this->used = used;
}


string Hunter::getStatus() {
	string status = abilityToString(ability);
	status += "(";
	status += (reserve)? "f" : "e";
	status += (used)? ", u" : ", n";
	status += ")";
	return status;
}

int Hunter::getCost() {
	return 2;
}

void Hunter::use() {
	used = true;
	Player* enemy = GameModel::getInstance()->getOpponent(owner->getOwner());
	vector<shared_ptr<Animal>>* enemyAnimals = enemy->getAnimals();
	cout << "Select animal to hunt:" << endl;
	for (auto i = enemyAnimals->begin(); i != enemyAnimals->end(); i++) {
		cout << i - enemyAnimals->begin()+1 << ") " << (*i)->getStatus() << endl;
	}
	int animalToKill = getInt(cin, 1, enemyAnimals->size());
	CommandHolder::getInstance()->addCommand(new ResetUseCommand(this, true));
	if (enemyAnimals->at(animalToKill-1)->defend(owner)) {
		return;
	} else {
		CommandHolder::getInstance()->addCommand(new KillAnimalCommand(enemy, animalToKill-1));
		try {
			CommandHolder::getInstance()->addCommand(new FeedCommand(owner));
			CommandHolder::getInstance()->addCommand(new FeedCommand(owner));
		} catch (Exception& e) {

		}
	}	
}

AbilityCard* Hunter::clone() {
	return new Hunter(*this);
}


istream& Hunter::read(istream& stream) {
	cout << "Reading from stream: " << abilityToString(ability) << endl;
	stream >> reserve;
	return stream;
}
ostream& Hunter::write(ostream& stream)  {
	stream << ability << ' ' << reserve << endl;
	return stream;
}