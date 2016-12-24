#ifndef DECK_H
#define DECK_H

#include <memory>
#include "exceptions/Exception.h"
// #include "exceptions/DeckException.h"
#include "interfaces/Serializable.h"
#include "controllers/commands/AbstractCommand.h"
#include "model/cards/AbilityCard.h"
#include "DeckIterator.h"
#include <stdlib.h>


using namespace std;

template<typename T>
class Deck {
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
	Node* at(int index);
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

	void shuffle();
	void swap(Node*, Node*);

	ostream& write(ostream&);

	// template<typename T1>
	// friend ostream& operator<<(ostream& stream, Deck<T1> deck);
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
void Deck<T>::push_front(const T& data) {
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
void Deck<T>::push_back(const T& data) {
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
T Deck<T>::pop_front() {
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
T Deck<T>::pop_back() {
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
void Deck<T>::shuffle() {
	for (int k = 0; k < size*3; k++) {
		Node* first = at(rand() % size);
		Node* second = at(rand() % size);
		swap(first, second);
	}
}

template<typename T> 
void Deck<T>::swap(Node* firstNode, Node* secondNode) {
	if (first == firstNode || first == secondNode) {
		if (first == secondNode) {
			first = firstNode;
		} else {
			first = secondNode;
		}
	}
	if (last == firstNode || last == secondNode) {
		if (last == secondNode) {
			last = firstNode;
		} else {
			last = secondNode;
		}
	}
	if (secondNode->next == firstNode) {
		secondNode->next = firstNode->next;
		firstNode->previous = secondNode->previous;
		firstNode->next = secondNode;
		secondNode->previous = firstNode;
		if (secondNode->next != nullptr) {
			secondNode->next->previous = secondNode;
		}
		if (firstNode->previous != nullptr) {
			firstNode->previous->next = firstNode;
		}
		return;
	}
	if (secondNode->previous == firstNode) {
		secondNode->previous = firstNode->previous;
		firstNode->next = secondNode->next;
		firstNode->previous = secondNode;
		secondNode->next = firstNode;
		if (firstNode->next != nullptr) {
			firstNode->next->previous = firstNode;
		}
		if (secondNode->previous != nullptr) {
			secondNode->previous->next = secondNode;
		}
		return;
	}

	Node* tmp = secondNode->next;
	secondNode->next = firstNode->next;
	firstNode->next = tmp;
	if (firstNode->next != nullptr) {
		firstNode->next->previous = firstNode;
	}
	if (secondNode->next != nullptr) {
		secondNode->next->previous = secondNode;
	}

	tmp = secondNode->previous;
	secondNode->previous = firstNode->previous;
	firstNode->previous = tmp;
	if (firstNode->previous != nullptr) {
		firstNode->previous->next = firstNode;
	}
	if (secondNode->previous != nullptr) {
		secondNode->previous->next = secondNode;
	}
}
template<typename T>
typename Deck<T>::Node* Deck<T>::at(int index) {
	if (index >= size) {
		throw Exception("Out of range");
	}
	Node* tmp = first;
	for (int i = 0; i < index; i++) {
		tmp = tmp->next;
	}
	return tmp;
}

template<typename T>
ostream& Deck<T>::write(ostream& stream) {	
	stream << size << endl;
	if (size > 0) {
		iterator_t it = begin();
		for (; it != end(); it++) {
			(*it)->write(stream);
		}
		(*it)->write(stream);
	}	
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