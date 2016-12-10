#include <iostream>
#include <climits>
#include "exceptions/Exception.h"
#include "model/cards/abilities/Ability.h"
#include "model/GamePhaze.h"

using namespace std;

int getInt(istream& stream, int min=INT_MIN, int max=INT_MAX) {
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

int abilityToInt(Ability::AbilityType ability) {
	int result = -1;
	switch (ability) {
		case Ability::FAT : {
			result = 1;
			break;
		}
		case Ability::FAST : {
			result = 2;
			break;
		}
		default : {
			throw Exception("Unsupported ability type");
		}
	}
	return result;
}

string abilityToString(Ability::AbilityType ability) {
	string result = "";
	switch (ability) {
		case Ability::FAT : {
			result = "FAT";
			break;
		}
		case Ability::FAST : {
			result = "FAST";
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