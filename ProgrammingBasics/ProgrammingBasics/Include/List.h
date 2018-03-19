#ifndef __LIST_H
#define __LIST_H

#include <stdexcept>

template <typename T> class List
{
private:
	class Node
	{
	private:
		T value;
		Node* next;
	public:

		Node()
		{
			next = nullptr;
		}

		Node* getNext()
		{
			return next;
		}

		void setNext(Node* nxt)
		{
			next = nxt;
		}

		T getValue()
		{
			return value;
		}

		void setValue(T newVal)
		{
			value = newVal;
		}
	};

	Node* head;
	Node* tail;
	int size;
public:
	List();
	class Marker
	{
	private:
		Node* current;
		List* listForMarker;
	public:
		Marker(List* list)
		{
			current = list->head;
			listForMarker = list;
		}
		bool moveNext();
		T getCurrent() const;
		void setCurrent(T value);
		void moveTail();
		void moveHead();
		void addAfter(T val);
		void deleteAfter();
		void operator <<(T NewValue);
		T& operator >>(T& Temp);
	};

	int getSize();
	void addElementBeforeHead(T val);
	void addElementAfterTail(T val);
	void deleteHeadElement();
	void deleteTailElement();
	Marker* createMarker();
};

template <typename T> List<T>::List() {
	head = nullptr;
	tail = nullptr;
	size = 0;
}

template <typename T> int List<T>::getSize()
{
	return size;
}

template <typename T> void List<T>::addElementBeforeHead(T val)
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

template <typename T> void List<T>::addElementAfterTail(T val)
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

template <typename T> void List<T>::deleteHeadElement()
{
	Node* temp = head->getNext();
	delete head;
	head = temp;
	size--;
}

template <typename T> void List<T>::deleteTailElement()
{
	Node* temp = head;
	for (int i = 0; i < size - 2; i++)
	{
		temp = temp->getNext();
	}
	delete tail;
	tail = temp;
	size--;
}

template <typename T> typename List<T>::Marker* List<T>::createMarker() {
	List<T>::Marker* newMarker = new List<T>::Marker(this);
	newMarker->moveHead();
	return newMarker;
}

template <typename T> void List<T>::Marker::moveTail()
{
	current = listForMarker->tail;
}

template <typename T> void List<T>::Marker::moveHead() {
	current = listForMarker->head;
}

template <typename T> bool List<T>::Marker::moveNext()
{
	if (current != nullptr && current->getNext() != nullptr)
	{
		current = current->getNext();
		return true;
	}
	return false;
}

template <typename T> T List<T>::Marker::getCurrent() const {
	if (current != nullptr) {
		return current->getValue();
	}
	else {
		throw std::runtime_error("Current was nullptr");
	}
}

template <typename T> void List<T>::Marker::setCurrent(T value) {
	if (current != nullptr) {
		current->setValue(value);
	}
	else {
		throw std::exception("Current was nullptr");
	}
}

template <typename T> void List<T>::Marker::addAfter(T val)
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

template <typename T> void List<T>::Marker::deleteAfter()
{
	Node* temp = current->getNext();
	current->setNext(current->getNext()->getNext());
	delete temp;
	listForMarker->size--;
}

template <typename T> void List<T>::Marker::operator <<(T NewValue) {
	this->addAfter(NewValue);
}

//template <typename T> T List<T>::Marker::operator >>(Marker *marker) {
//	return marker->getCurrent();
//}

template <typename T> T& List<T>::Marker:: operator >> (T& Temp) {
	Temp = this->getCurrent();
	return Temp;
}
#endif
