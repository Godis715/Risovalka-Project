#include "List.h"
#include <stdexcept>



List::Node* List::getHead(){
		return head;
}

List::Node* List::getTail()	{
		return tail;
}
List::List(){
		head = nullptr;
		tail = nullptr;
		size = 0;
		current = head;
}
int List::getSize()	{
		return size;
}

void List::moveTail()
	{
		current = this->getTail();
	}

void List::moveHead(){
		current = this->getHead();
}

bool List::moveNext()
	{
		if (current != nullptr && current->getNext() != nullptr)
		{
			current = current->getNext();
			return true;
		}
		return false;
	}

int List::getCurrent()
	{
		if(current != nullptr)
			return current->getValue();
		throw std::out_of_range("Пустой список");
	}

	void List::setCurrent(int newVal)
	{
		if(current != nullptr)
			current->setValue(newVal);
	}

	void List::addElementBeforeHead(int val)
	{
		if (size == 0)
		{
			head = tail = new Node();
			head->setValue(val);
			current = head;
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
			current = head;
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

	void List::addElementAfterCurrent(int val)
	{
		if (size == 0)
		{
			head = tail = new Node();
			head->setValue(val);
			current = head;
		}
		else
		{
			Node* temp = new Node();
			temp->setValue(val);
			temp->setNext(current->getNext());
			current->setNext(temp);

			if (current == tail) {
				tail = temp;
			}
		}
		size++;
	}

	void List::deleteAfterCurrentElement()
	{
		Node* temp = current->getNext();
		current->setNext(current->getNext()->getNext());
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

		current = currElem;
	}
