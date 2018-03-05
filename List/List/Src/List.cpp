#include "List.h"
#include <stdexcept>

List::List(){
		head = nullptr;
		tail = nullptr;
		size = 0;
}

int List::getSize()
{
	return size;
}

void List::addElementBeforeHead(int val)
	{
		if (size == 0)
		{
			head = tail = new Node();
			head->setValue(val);
		}
		else
		{
			Node* temp = new Node();
			temp->setValue(val);
			temp->setNext(head);
			head = temp;
		}
		size++;
	}

void List::addElementAfterTail(int val)
	{
		if (size == 0)
		{
			head = tail = new Node();
			head->setValue(val);
		}
		else
		{
			Node* temp = new Node();
			temp->setValue(val);
			tail->setNext(temp);
			tail = temp;
		}
		size++;
	}

void List::deleteHeadElement()
	{
		Node* temp = head->getNext();
		delete head;
		head = temp;
		size--;
	}

void List::deleteTailElement()
	{
		Node* temp = head;
		for (int i = 0; i < size - 1; i++)
		{
			temp = temp->getNext();
		}
		delete tail;
		tail = temp;
		size--;
	}

List::Marker* List::createMarker() {
	List::Marker* newMarker = new Marker(this);
	newMarker->moveHead();
	return newMarker;
}

void List::Marker::moveTail()
{
	current = listForMarker->tail;
}

void List::Marker::moveHead() {
	current = listForMarker->head;
}

bool List::Marker::moveNext()
{
	if (current != nullptr && current->getNext() != nullptr)
	{
		current = current->getNext();
		return true;
	}
	return false;
}

int List::Marker::getCurrent() const {
	if (current != nullptr) {
		return current->getValue();
	}
	else {
		throw std::exception("Current was nullptr");
	}
}

void List::Marker::setCurrent(int value) {
	if (current != nullptr) {
		current->setValue(value);
	}
	else {
		throw std::exception("Current was nullptr");
	}
}

void List::Marker::addAfter(int val)
{
	if (listForMarker->size == 0)
	{
		listForMarker->head = listForMarker->tail = new Node();
		listForMarker->head->setValue(val);
	}
	else
	{
		Node* temp = new Node();
		temp->setValue(val);
		temp->setNext(current->getNext());
		current->setNext(temp);
		if (current == listForMarker->tail) {
			listForMarker->tail = temp;
		}
	}
	listForMarker->size++;
}

void List::Marker::deleteAfter()
{
	Node* temp = current->getNext();
	current->setNext(current->getNext()->getNext());
	delete temp;
	listForMarker->size--;
}
