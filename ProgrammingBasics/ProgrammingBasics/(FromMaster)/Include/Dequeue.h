#pragma once
#include "Queue.h"

template<class Type> class Deck
{
private:
	class Element
	{
	public:
		Element* next = nullptr;
		Element* prev = nullptr;
		Type value;
	};

	Element* head;
	Element* tail;
	int size;
public:
	Deck() {
		head = nullptr;
		tail = nullptr;
		size = 0;
	}
	~Deck() {
		DeleteDeck();
	}
	int GetSize() {
		return size;
	}

	void PushBegin(Type newValue) {
		Element* newElement = new Element;
		newElement->value = newValue;
		if (size != 0) {
			head->prev = newElement;
			newElement->next = head;
		}
		else
		{
			tail = newElement;
		}
		head = newElement;
		++size;
		return;
	}

	void PushBack(Type newValue) {
		if (size == 0) {
			PushBegin(newValue);
			return;
		}
		Element* newElement = new Element;
		newElement->value = newValue;
		newElement->prev = tail;
		tail->next = newElement;
		tail = newElement;
		++size;
		return;
	}

	Type PopBegin() {
		if (size == 0) {
			throw std::exception("deck is Empty");
		}
		Type value = head->value;
		Element* temp = head;
		head = head->next;
		--size;
		delete temp;
		if (head != nullptr) {
			head->prev = nullptr;
		}
		return value;
	}

	Type PopBack() {
		if (size == 0) {
			throw std::exception("deck is Empty");
		}
		Type value = tail->value;
		Element* temp = tail;
		tail = tail->prev;
		--size;
		delete temp;
		if (tail != nullptr) {
			tail->next = nullptr;
		}
		return value;
	}

	void DeleteDeck() {
		while (size != 0)
		{
			PopBegin();
		}
		return;
	}

	bool IsEmpty() {
		return (size == 0);
	}
};