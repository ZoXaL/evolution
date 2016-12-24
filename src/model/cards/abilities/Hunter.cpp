#include "model/cards/abilities/Hunter.h"
#include "model/cards/abilities/Ability.h"
#include "model/cards/AbilityCard.h"
#include "model/GameModel.h"
#include "controllers/commands/CommandHolder.h"
#include "controllers/commands/UseFatCommand.h"
#include "controllers/commands/KillAnimalCommand.h"
#include "exceptions/Exception.h"
#include "functions.h"
#include <iostream>
#include <string>
using namespace std;

Hunter::Hunter() : AbilityCard(Ability::HUNTER, false) {};

bool Hunter::needFood() {
	return reserve<2;
}

bool Hunter::canGetFood() {
	return reserve<2;
}

void Hunter::resetFood() {
	reserve = 0;
}
void Hunter::decreaseFood() {
	reserve--;
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
	Player* enemy = GameModel::getInstance()->getOpponent(owner->getOwner());
	vector<shared_ptr<Animal>>* enemyAnimals = enemy->getAnimals();
	cout << "Select animal to hunt:" << endl;
	for (auto i = enemyAnimals->begin(); i != enemyAnimals->end(); i++) {
		cout << i - enemyAnimals->begin()+1 << ") " << (*i)->getStatus() << endl;
	}
	int animalToKill = getInt(cin, 1, enemyAnimals->size());
	if (enemyAnimals->at(animalToKill-1)->defend(owner)) {
		return;
	} else {
		CommandHolder::getInstance()->addCommand(new KillAnimalCommand(enemy, animalToKill-1));
		//CommandHolder::getInstance()->addCommand(new FeedComman());
	}	
}

AbilityCard* Hunter::clone() {
	return new Hunter(*this);
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