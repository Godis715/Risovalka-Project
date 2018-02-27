#include "List.h"
#include <stdexcept>




List::List(){
		head = nullptr;
		tail = nullptr;
		size = 0;
}
int List::getSize()	{
		return size;
}

void List::Marker::moveTail()
	{
		current = ListForMarker->tail;
	}

void List::Marker::moveHead(){
		current = ListForMarker->head;
}
List::Node* List::Marker::getCurrent()
{
	if (current != nullptr)
	{
		return current;
	}
	else
	{
		throw std::out_of_range("Список пуст\n");
	}
	
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

	void List::addElementAfterMarker(int val, List::Marker marker)
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
			temp->setNext(marker.getCurrent()->getNext());
			marker.getCurrent()->setNext(temp);
			if (marker.getCurrent() == tail) {
				tail = temp;
			}
		}
		size++;
	}

	void List::deleteAfterMarkerElement(List::Marker marker)
	{
		Node* temp = marker.getCurrent()->getNext();
		marker.getCurrent()->setNext(marker.getCurrent()->getNext()->getNext());
		delete temp;
		size--;
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

	int List::getValueAt(int index) const {
		if (index < 0) {
			throw std::exception("Index was negative.");
		}

		if (head == nullptr) {
			throw std::exception("List is empty.");
		}

		Node* currElem = head;

		for (int i = 0; i < index; ++i) {
			currElem = currElem->getNext();
			if (currElem == nullptr) {
				throw std::exception("Index out of range.");
			}
		}

		return currElem->getValue();
	}

	void List::setCurrentAt(int index) {
		if (index < 0) {
			throw std::exception("Index was negative.");
		}

		if (head == nullptr) {
			throw std::exception("List is empty.");
		}

		Node* currElem = head;

		for (int i = 0; i < index; ++i) {
			currElem = currElem->getNext();
			if (currElem == nullptr) {
				throw std::exception("Index out of range.");
			}
		}
	}
