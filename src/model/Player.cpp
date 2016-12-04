#include "model/Player.h"
#include <string.h>

Player::Player(const char* name) {
	strcpy(this->name, name);
}

const char* Player::getName() {
	return this->name;
}

void Player::setName(const char* name) {
	strcpy(this->name, name);
}