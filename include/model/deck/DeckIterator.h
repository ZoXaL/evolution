#ifndef DECK_ITERATOR_H
#define DECK_ITERATOR_H

#include "exceptions/DeckException.h"

template<typename T>
class Deck;

template<typename T>
class DeckIterator {	
public:
	typedef typename Deck<T>::Node* pointer_t;
	DeckIterator(pointer_t);

	DeckIterator<T> operator++();
	DeckIterator<T> operator++(int);
	DeckIterator<T> operator--();
	DeckIterator<T> operator--(int);
	bool operator==(const DeckIterator<T>&);
	bool operator!=(const DeckIterator<T>&);
	T operator*();
	T* operator->();
private:
	pointer_t current;
};

template<typename T>
DeckIterator<T>::DeckIterator(pointer_t current) {
	this->current = current;
}
template<typename T>
DeckIterator<T> DeckIterator<T>::operator++() {
	if (current->next == nullptr) {
		throw DeckException("Illegal DeckIterator state: cannot ++");
	} else {
		current = current->next;
	}
	return *this;
}
template<typename T>
DeckIterator<T> DeckIterator<T>::operator--() {
	if (current->previous == nullptr) {
		throw DeckException("Illegal DeckIterator state: cannot --");
	} else {
		current = current->previous;
	}
	return *this;
}
template<typename T>
DeckIterator<T> DeckIterator<T>::operator++(int a) {
	if (current->next == nullptr) {
		throw DeckException("Illegal DeckIterator state: cannot ++");
	} else {
		current = current->next;
	}
	return *this;
}
template<typename T>
DeckIterator<T> DeckIterator<T>::operator--(int a) {
	if (current->previous == nullptr) {
		throw DeckException("Illegal DeckIterator state: cannot --");
	} else {
		current = current->previous;
	}
	return *this;
}
template<typename T>
T DeckIterator<T>::operator*() {
	if (current == nullptr) {
		throw DeckException("DeckIterator: Cannot * iterator because it points to nullptr");
	}
	return current->data;	
}
template<typename T>
T* DeckIterator<T>::operator->() {
	if (current == nullptr) {
		throw DeckException("DeckIterator: Cannot -> iterator because it points to nullptr");
	}
	return &(current->data);
}
template<typename T>
bool DeckIterator<T>::operator==(const DeckIterator<T>& comp) {
	return this->current == comp.current;
}
template<typename T>
bool DeckIterator<T>::operator!=(const DeckIterator<T>& comp) {
	return this->current != comp.current;
}
#endif