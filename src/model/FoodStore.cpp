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
void FoodStore::addFood() {
	capacity++;
}
void FoodStore::setFood(int capacity) {
	this->capacity = capacity;
}

bool FoodStore::isEmpty() {
	return capacity > 0;
}

int FoodStore::generateFood() {
	capacity = rand() % (MAX_FOOD - MIN_FOOD) + MIN_FOOD;
	return capacity;
}

int FoodStore::getCapacity() {
	return capacity;
}