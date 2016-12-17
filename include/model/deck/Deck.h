#ifndef DECK_H
#define DECK_H

#include <memory>
#include "exceptions/Exception.h"
#include "interfaces/Serializable.h"
#include "DeckIterator.h"

class Card;

using namespace std;

template<typename T>
class Deck : public Serializable {
	struct Node {
		T data;
		Node* previous;
		Node* next;

		Node (const T& _data) : data(_data) {
			next = nullptr;
			previous = nullptr;
		};
	};
	Node* first;
	Node* last;
	int size;
public:
	typedef DeckIterator<T> iterator_t;
	friend iterator_t;
	iterator_t begin();
	iterator_t end();

	Deck();
	~Deck();
	void push_back(const T&);
	void push_front(const T&);

	T pop_back();
	T pop_front();

	bool isEmpty();
	int getSize();

	ostream& write(ostream&);
	istream& read(istream&);

	template<typename T1>
	friend ostream& operator<<(ostream& stream, Deck<T1> deck);
};

template<typename T> 
Deck<T>::Deck() {
	size = 0;
	first = nullptr;
	last = nullptr;
}
template<typename T> 
Deck<T>::~Deck() {
	Node* tmp = last;
	while(last!=first) {
		last = last->previous;
		delete tmp;
		tmp = last;
	}
	delete tmp;
}

template<typename T> 
void Deck<T>::push_back(const T& data) {
	Node* newNode = new Node(data);
	newNode->previous = nullptr;
	newNode->next = first;
	if (first != nullptr) {
		first->previous = newNode;	
	} 
	first = newNode;	
	if (last == nullptr) {
		last = first;
	}
	size++;
}
template<typename T> 
void Deck<T>::push_front(const T& data) {
	Node* newNode = new Node(data);
	newNode->previous = last;
	newNode->next = nullptr;
	if (last != nullptr) {
		last->next = newNode;
	}	
	last = newNode;
	if (first == nullptr) {
		first = last;
	}
	size++;
}

template<typename T> 
T Deck<T>::pop_back() {
	if (first == nullptr) {
		throw Exception("Cannot pop_back from Deck: there is no elements");
	}
	T returnData = first->data;
	Node* tmp = first;
	first = first->next;
	delete tmp;
	size--;
	if (size == 0) {
		first = nullptr;
		last = nullptr;
	}
	return returnData;
}
template<typename T> 
T Deck<T>::pop_front() {
	if (last == nullptr) {
		throw Exception("Cannot pop_front from Deck: there is no elements");
	}
	T returnData = last->data;
	Node* tmp = last;
	last = last->previous;
	delete tmp;
	size--;
	if (size == 0) {
		first = nullptr;
		last = nullptr;
	}
	return returnData;
}
template<typename T>
typename Deck<T>::iterator_t Deck<T>::begin() {
	return iterator_t(first);
}
template<typename T>
typename Deck<T>::iterator_t Deck<T>::end() {
	return iterator_t(last);
}
template<typename T>
ostream& operator<<(ostream& stream, Deck<T> deck) {
	stream << "kk";
}

template<typename T>
ostream& Deck<T>::write(ostream& stream) {	
	stream << "kk write deck to file" << endl;
	iterator_t it = begin();
	for (; it != end(); it++) {
		(*it)->write(stream);
	}
	(*it)->write(stream);
	return stream;
}

template<typename T>
istream& Deck<T>::read(istream& stream) {
	// TODO: read number of elements
	// fill out the deck
	cout << "kk read deck from file" << endl;
	return stream;
}

template<typename T> 
bool Deck<T>::isEmpty() {
	return (size == 0);
}

template<typename T> 
int Deck<T>::getSize() {
	return size;
}
#endif