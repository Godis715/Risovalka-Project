#ifndef __LIST_H
#define __LIST_H
// EVG?-class LMarker

#include "Dequeue.h"

template <typename T> class List
{
private:
	class Node
	{
	private:
	public:
		T value;
		Node* next;
		Node(Node* _next, const T& _value) : next(_next), value(_value)
		{

		}
	};

	Node* guard;
	Node* head;
	Node* tail;
	int size;
public:
	List() {
		guard = nullptr;
		head = nullptr;
		tail = nullptr;
		size = 0;
	}
	class Marker
	{
	private:
		Node* current;
		Node* prev;
		List* list;

		bool isValid;

		bool MoveNext() {
			if (!isValid || current->next == nullptr) {
				return false;
			}
			prev = current;
			current = current->next;
			return true;
		}
	public:
		Marker() {
			list = nullptr;
			current = nullptr;
			isValid = false;
		}

		Marker(List* _list)
		{
			if (_list->head == nullptr) {
				isValid = false;
				return;
			}
			isValid = true;
			prev = nullptr;
			current = _list->head;
			list = _list;
		}

		Marker(const Marker& marker) {
			this->current = marker->current;
			this->prev = marker->prev;
			this->list = marker->list;
			this->isValid = marker.isValid;
		}

		Marker(Marker&& marker) {
			this->current = marker.current;
			this->prev = marker.prev;
			this->list = marker.list;
			this->isValid = marker.isValid;

			marker.current = nullptr;
			marker.prev = nullptr;
			marker.list = nullptr;
		}

		void operator=(const Marker& marker) {
			this->current = marker.current;
			this->prev = marker.prev;
			this->list = marker.list;
			this->isValid = marker.isValid;
		}

		void operator=(Marker&& marker) {
			this->current = marker.current;
			this->prev = marker.prev;
			this->list = marker.list;
			this->isValid = marker.isValid;

			marker.current = nullptr;
			marker.prev = nullptr;
			marker.list = nullptr;
		}

		bool operator==(const Marker& marker) {
			return current == marker.current;
		}

		bool operator!=(const Marker& marker) {
			return current != marker.current;
		}

		bool operator++() {
			return MoveNext();
		}

		void DeleteCurrent() {
			if (!isValid) {
				return;
			}
			Node* temp = current;

			if (list->head == current) {
				list->head = current->next;
				list->guard->next = list->head;
			}
			else {
				prev->next = current->next;
			}
			if (current->next == nullptr) {
				list->tail = prev;
			}

			list->size--;
			delete temp;
		}

		T operator*() const {
			if (!isValid) {
				throw std::exception("Marker was not valid");
			}
			return current->value;
		}

		void AddAfter(const T& val) {
			if (!isValid) {
				return;
			}
			Node* newNode = new Node(current->next, val);
			current->next = newNode;
			if (newNode->next == nullptr) {
				list->tail = newNode;
			}
			list->size++;
		}

		// &&&&&??????
		bool IsValid() const {
			return isValid;
		}
	};
	
	size_t GetSize() const {
		return size;
	}

	Marker BeforeBegin() {
		head = guard;
		auto marker = Marker(this);
		if (head != nullptr) {
			head = guard->next;
		}
		return marker;
	}

	Marker Begin() {
		return Marker(this);
	}

	Marker End() {
		auto marker = Marker(this);
		while (++marker)
		{}
		return marker;
	}

	void Push(const T& val) {
		if (size == 0)
		{
			guard = head;
			head = tail = new Node(nullptr, val);
			guard = new Node(head, val);
		}
		else
		{
			Node* newNode = new Node(nullptr, val);
			tail->next = newNode;
			tail = newNode;
		}
		size++;
	}

	T GetTail() {
		if (tail != nullptr)
		{
			return tail->value;
		}
		else {
			// $$$
		}
	}

	T GetHead() {
		if (head != nullptr)
		{
			return head->value;
		}
		else {
			// $$$
		}
	}	

	Marker Find(const T& val) {
		Marker marker(this);
		for (marker; marker.IsValid(); ++marker) {
			if (marker.GetValue() == val) {
				break;
			}
		}
		return marker;
	}
};
#endif