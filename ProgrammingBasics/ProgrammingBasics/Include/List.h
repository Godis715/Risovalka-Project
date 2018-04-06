#ifndef __LIST_H
#define __LIST_H

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
		throw std::exception("Current was nullptr");
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



template <class T> class ListE
{
private:
	template <class T> class Element
	{
	public:
		Element * next = nullptr;
		Element* prev = nullptr;
		T value;
	};
	Element<T>* head;
	Element<T>* tail;
	Element<T>* current;
	Element<T>* label;
	int size = 0;
public:
	ListE() {
		head = nullptr;
		tail = nullptr;
		current = nullptr;
		label = nullptr;
	}

	int GetSize() {
		return size;
	}

	void PushHead(T newValue) {
		Element<T>* newElement = new Element<T>;
		newElement->value = newValue;
		if (size != 0) {
			head->prev = newElement;
			newElement->next = head;
		}
		else {
			current = newElement;
			tail = newElement;
		}
		head = newElement;
		++size;
		return;
	}

	void PushAfterCurrent(T newValue) {
		if (size == 0) {
			PushHead(newValue);
			return;
		}
		if (current == tail) {
			PushTail(newValue);
			return;
		}
		Element<T>* newElement = new Element<T>;
		newElement->next = current->next;
		newElement->prev = current;
		current->next->prev = newElement;
		current->next = newElement;
		++size;
		return;
	}

	void PushBeforeCurrent(T newValue) {
		if (size == 0) {
			PushHead(newValue);
			return;
		}
		if (current == head) {
			PushHead(newValue);
			return;
		}
		MovePrev();
		PushAfterCurrent(newValue);
		MoveNext();
		MoveNext();
	}

	void PushTail(T newValue) {
		if (size == 0) {
			PushHead(newValue);
			return;
		}
		Element<T>* newElement = new Element<T>;
		newElement->value = newValue;
		newElement->prev = tail;
		tail->next = newElement;
		tail = newElement;
		++size;
		return;
	}

	void DeleteCurrent() {
		if (size == 1) {
			head = nullptr;
			tail = nullptr;
			delete current;
			current = nullptr;
			--size;
			return;
		}
		if ((current->next == nullptr) || (current == tail)) {
			tail = current->prev;
		}
		else {
			current->next->prev = current->prev;
		}
		if ((current->prev == nullptr) || (current == head)) {
			head = current->next;
		}
		else {
			current->prev->next = current->next;
		}
		Element<T>* temp = current;
		if (!MoveNext()) {
			current = tail;
		}
		delete temp;
		--size;
		return;
	}

	void DeleteList() {
		while (size != 0)
		{
			current = head;
			DeleteCurrent();
		}
		return;
	}

	bool IsCurrent() {
		if (current == nullptr) {
			return false;
		}
		else {
			return true;
		}
	}

	T GetCurrent() {
		return current->value;
	}

	void MoveHead() {
		current = head;
	}

	void MoveTail() {
		current =tail;
	}

	bool MoveNext() {
		if (current->next == nullptr) {
			return false;
		}
		else {
			current = current->next;
			return true;
		}
	}

	bool MovePrev() {
		if (current->prev == nullptr) {
			return false;
		}
		else {
			current = current->prev;
			return true;
		}
	}

	void CreateLabel() {
		if (current != nullptr) {
			label = current;
		}
	}

	void DeleteLabel() {
		if (size == 1) {
			head = nullptr;
			tail = nullptr;
			delete current;
			--size;
			return;
		}
		if (label == nullptr) {
			return;
		}
		if (label == current) {
			label = nullptr;
			DeleteCurrent();
			return;
		}
		if ((label->next == nullptr) || (label == tail)) {
			tail = label->prev;
		}
		else {
			label->next->prev = label->prev;
		}
		if ((label->prev == nullptr) || (label == head)) {
			head = label->next;
		}
		else {
			label->prev->next = label->next;
		}
		delete label;
		label = nullptr;
		--size;
		return;
	}
};
#endif