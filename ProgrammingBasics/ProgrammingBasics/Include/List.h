#ifndef __LIST_H
#define __LIST_H

#include "INumerable.h"
#include <stdexcept>

template <typename T> class List : public INumerable
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
	class Marker : IMarker
	{
	private:
		Node* current;
		Node* prev;
		List* listForMarker;
	public:
		Marker(List* list)
		{
			if (list->head == nullptr) {
				isValid = false;
				return;
			}
			isValid = true;
			prev = nullptr;
			current = list->head;
			listForMarker = list;
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

		bool MoveNext() {
			if(!isValid || current->next == nullptr) {
				isValid = false;
				return false;
			}
			prev = current;
			current = current->next;
			return true;
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
	};
	
	size_t GetSize() const {
		return size;
	}
	template <class T> IMarker<T>* GetMarker() {
		return new Marker(this);
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
};

//
//template <class T> class ListE
//{
//private:
//	template <class T> class Element
//	{
//	public:
//		Element() {
//
//		}
//		Element(T& val) : value(val) {
//		
//		}
//		Element* next = nullptr;
//		Element* prev = nullptr;
//		T value;
//	};
//	Element<T>* head;
//	Element<T>* tail;
//	Element<T>* current;
//	int size = 0;
//public:
//	ListE() {
//		head = nullptr;
//		tail = nullptr;
//		current = nullptr;
//	}
//
//	int GetSize() const {
//		return size;
//	}
//
//	void PushHead(T& newValue) {
//		Element<T>* newElement = new Element<T>(newValue);
//		if (size != 0) {
//			head->prev = newElement;
//			newElement->next = head;
//		}
//		else {
//			current = newElement;
//			tail = newElement;
//		}
//		head = newElement;
//		++size;
//		return;
//	}
//
//	void PushAfterCurrent(T& newValue) {
//		if (size == 0) {
//			PushHead(newValue);
//			return;
//		}
//		if (current == tail) {
//			PushTail(newValue);
//			return;
//		}
//		Element<T>* newElement = new Element<T>(newValue);
//		newElement->next = current->next;
//		newElement->prev = current;
//		current->next->prev = newElement;
//		current->next = newElement;
//		++size;
//		return;
//	}
//
//	void PushBeforeCurrent(T& newValue) {
//		if (size == 0) {
//			PushHead(newValue);
//			return;
//		}
//		if (current == head) {
//			PushHead(newValue);
//			return;
//		}
//		MovePrev();
//		PushAfterCurrent();
//		MoveNext();
//		MoveNext();
//	}
//
//	void PushTail(T& newValue) {
//		if (size == 0) {
//			PushHead(newValue);
//			return;
//		}
//		Element<T>* newElement = new Element<T>(newValue);
//		newElement->prev = tail;
//		tail->next = newElement;
//		tail = newElement;
//		++size;
//		return;
//	}
//
//	void DeleteCurrent() {
//		if (size == 1) {
//			head = nullptr;
//			tail = nullptr;
//			delete current;
//			current = nullptr;
//			--size;
//			return;
//		}
//		if ((current->next == nullptr) || (current == tail)) {
//			tail = current->prev;
//		}
//		else {
//			current->next->prev = current->prev;
//		}
//		if ((current->prev == nullptr) || (current == head)) {
//			head = current->next;
//		}
//		else {
//			current->prev->next = current->next;
//		}
//		Element<T>* temp = current;
//		if (!MoveNext()) {
//			current = tail;
//		}
//		delete temp;
//		--size;
//		return;
//	}
//
//	void DeleteList() {
//		while (size != 0)
//		{
//			current = head;
//			DeleteCurrent();
//		}
//		return;
//	}
//
//	bool IsCurrent() {
//		if (current == nullptr) {
//			return false;
//		}
//		else {
//			return true;
//		}
//	}
//
//	T GetCurrent() {
//		return current->value;
//	}
//
//	void MoveHead() {
//		current = head;
//	}
//
//	void MoveTail() {
//		current =tail;
//	}
//
//	bool MoveNext() {
//		if (current->next == nullptr) {
//			return false;
//		}
//		else {
//			current = current->next;
//			return true;
//		}
//	}
//
//	bool MovePrev() {
//		if (current->prev == nullptr) {
//			return false;
//		}
//		else {
//			current = current->prev;
//			return true;
//		}
//	}
//};
#endif