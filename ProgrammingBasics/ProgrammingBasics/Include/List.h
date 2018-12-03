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

	Node* guardHead;
	Node* guardTail;
	Node* head;
	Node* tail;
	int size;
public:
	List() {
		guardHead = nullptr;
		guardTail = nullptr;
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
			if (!isValid || current == list->guardTail) {
				isValid = false;
				return false;
			}
			
			prev = current;
			current = current->next;
			if (current == list->guardTail) {
				isValid = false;
				return false;
			}
			else {
				return true;
			}
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

		Marker(List* _list, Node* _current)
		{
			if (_list->head == nullptr || _current == nullptr) {
				isValid = false;
			}
			current = _current;
			list = _list;
			if (current == list->guardTail) {
				isValid = false;
			}
			else {
				isValid = true;
			}
		}

		Marker(List* _list, Node* _prev, Node* _current)
		{
			if (_list->head == nullptr || _prev == nullptr || _current == nullptr) {
				isValid = false;
			}
			prev = _prev;
			current = _current;
			list = _list;	prev = _prev;
			if (current == list->guardTail) {
				isValid = false;
			}
			else {
				isValid = true;
			}
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
				list->guardHead->next = list->head;
			}
			else {
				prev->next = current->next;
			}
			if (current->next == list->guardTail) {
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
		return Marker(this, guardHead);
	}

	Marker Begin() {
		auto marker = Marker(this);
		if (marker.IsValid()) {
			return marker;
		}
		else {
			return AfterEnd();
		}
	}

	Marker End() {
		auto marker = Marker(this);
		auto temp = Marker(this);
		while (++temp)
		{
			++marker;
		}
		return marker;
	}

	Marker AfterEnd() {
		return Marker(this, tail, guardTail);
	}

	void Push(const T& val) {
		if (guardHead == nullptr) {
			guardHead = new  Node(nullptr, val);
			guardTail = new  Node(nullptr, val);
		}
		if (size == 0)
		{
			head = new Node(nullptr, val);
			tail = head;
			guardHead->next = head;
		}
		else
		{
			Node* newNode = new Node(nullptr, val);
			tail->next = newNode;
			tail = newNode;
		}
		tail->next = guardTail;
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

	void Clear() {
		if (head == nullptr || size ==0)
		{
			return;
		}
		guardHead->next = guardTail;
		auto node = head;
		while (node != guardTail) {
			auto temp = node->next;
			delete node;
			node = temp;
		}
		size = 0;
		head = nullptr;
		tail = nullptr;
	}
};
#endif