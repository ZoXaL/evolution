#include "controllers/MainController.h"
#include "model/cards/Card.h"
#include "model/cards/AbilityCard.h"
#include "model/deck/Deck.h"
#include "model/deck/DeckIterator.h"
#include "exceptions/Exception.h"
#include <iostream>
#include <memory>
using namespace std;

int main() {
	typedef shared_ptr<Card> cp;
	system("clear");
	// MainController controller;
	// controller.run();
	

	Deck<cp> deck;

	deck.push_front(cp(new AbilityCard(AbilityCard::Ability::FAT)));
	deck.push_front(cp(new AbilityCard(AbilityCard::Ability::FAST)));
	deck.push_front(cp(new AbilityCard(AbilityCard::Ability::FAT)));
	deck.push_front(cp(new AbilityCard(AbilityCard::Ability::FAST)));

	// auto it = deck.begin();
	// auto it2 = deck.end();

	deck.write(cout);
	deck.read(cin);
	// cout << (*it++)->getDescription() << endl;
	// cout << (*it++)->getDescription() << endl;
	// cout << (*it++)->getDescription() << endl;
	// try {
	// 	deck.pop_back();
	// } catch (Exception e) {
	// 	cout << e;
	// }
	return 0;
}