#include <iostream>
#include <climits>
#include "model/cards/abilities/Ability.h"
#include "model/cards/Animal.h"
#include "model/cards/AbilityCard.h"
#include "model/GamePhaze.h"
#include "model/GameModel.h"
#include "model/Player.h"

using namespace std;

int getInt(istream& stream, int min, int max) {
	int result = 0;	
	bool correctInput;
	do {
		correctInput = true;
		stream >> result;
		if(stream.ios::fail() || stream.peek() != 10) {
			stream.ios::clear();
			stream.ignore(80, '\n');
			correctInput = false;			
		} else {
			if (result > max || result < min) {
				correctInput = false;
			}
		}
		if (!correctInput) {
			cout << "Incorrect input, repeat please: ";
		}
	} while(!correctInput);		
	stream.ignore(80, '\n');
	return result;
}	

bool checkRange(int check, int min, int max) {
	return (check <= max && check >= min);
}


string abilityToString(Ability::AbilityType ability) {
	string result = "";
	switch (ability) {
		case Ability::FAT : {
			result = "FAT";
			break;
		}
		case Ability::HUNTER : {
			result = "HUNTER";
			break;
		}
		case Ability::WATERFOWL : {
			result = "WATERFOWL";
			break;
		}
		case Ability::GRANT : {
			result = "GRANT";
			break;
		}
		case Ability::FAST : {
			result = "FAST";
			break;
		}
		case Ability::ACUTE_EYESIGHT : {
			result = "EYE";
			break;
		}
		case Ability::CAMOUFLAGE : {
			result = "CAMOUFLAGE";
			break;
		}
		case Ability::TOXIC : {
			result = "TOXIC";
			break;
		}
		default : {
			throw Exception("Unsupported ability type");
		}
	}
	return result;
}
string phazeToString(GamePhaze::Phaze phaze) {
	string result = "";
	switch (phaze) {
		case GamePhaze::FEED : {
			result = "FEED";
			break;
		}
		case GamePhaze::EVOLVE : {
			result = "EVOLVE";
			break;
		}
		default : {
			throw Exception("Unsupported phaze type");
		}
	}
	return result;
}

int getPlayerId(Player* player) {
	return (GameModel::getInstance()->getPlayer(0) == player) ? 0 : 1;
}

int getAnimalId(Player* player, Animal* animal) {
	vector<shared_ptr<Animal>>* animals = player->getAnimals();
	for (auto i = animals->begin(); i != animals->end(); i++) {
		if (i->get() == animal) {
			return distance(animals->begin(), i);
		}
	}
	return -1;
}
int getAbilityId(Animal* animal, AbilityCard* ability) {
	vector<shared_ptr<AbilityCard>>* abilities = animal->getAbilities();
	for (auto i = abilities->begin(); i != abilities->end(); i++) {
		if (i->get() == ability) {
			return distance(abilities->begin(), i);
		}
	}
	return -1;
}