#include "model/FoodStore.h"
#include <stdlib.h>

FoodStore::FoodStore() {
	this->capacity = 0;
}

bool FoodStore::getFood() {
	if (capacity > 0) {
		capacity--;
		return true;
	}
	return false;
}

bool FoodStore::isEmpty() {
	return capacity > 0;
}

int FoodStore::generateFood() {
	capacity = rand() % (MAX_FOOD - MIN_FOOD) + MIN_FOOD;
	return false;
}
int FoodStore::getCapacity() {
	return capacity;
}