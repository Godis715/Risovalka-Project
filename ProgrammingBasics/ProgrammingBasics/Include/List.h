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

	Node* head;
	Node* tail;
	int size;
public:
	List() {
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
				isValid = false;
				return false;
			}
			prev = current;
			current = current->next;
			return true;
		}
	public:
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
		}

		Marker(Marker&& marker) {
			this->current = marker.current;
			this->prev = marker.prev;
			this->list = marker.list;

			marker.current = nullptr;
			marker.prev = nullptr;
			marker.list = nullptr;
		}

		Marker() {
			list = nullptr;
			current = nullptr;
			isValid = false;
		}

		void operator=(const Marker& marker) {
			this->current = marker.current;
			this->prev = marker.prev;
			this->list = marker.list;
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

			if (prev != nullptr) {
				prev->next = current->next;
			}
			else {
				list->head = current->next;
			}
			if (current->next == nullptr) {
				list->tail = prev;
			}

			list->size--;
			delete temp;
		}

		T GetValue() const {
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

	Marker Begin() {
		return Marker(this);
	}

	Marker End() {
		auto marker = Marker(this);
		while (++marker)
		{}
		return marker;
	}

	void PushTail(const T& val) {
		if (size == 0)
		{
			head = tail = new Node(nullptr, val);
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