#ifndef FOOD_STORE_H
#define FOOD_STORE_H

class FoodStore {
	int capacity;
	const int MAX_FOOD = 8;
	const int MIN_FOOD = 3;
public:
	FoodStore();
	int generateFood();
	bool isEmpty();
	bool getFood();
};

#endif
