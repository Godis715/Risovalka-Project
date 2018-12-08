#pragma once
#include "IDGenerator.h"
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <string>


namespace DrawProject {


	template <class T> class Element
	{
	public:
		Element(T val) {
			value = val;
			node = nullptr;
		}
		Element() {
			node = nullptr;
		}
		Element(T val, Element* _node) {
			value = val;
			node = _node;
		}
		T value;
		Element* node;
	};

	template <class Type> class Queue
	{
	private:

		Element<Type>* head;
		Element<Type>* tail;
		int size;
	public:
		Queue() {
			head = nullptr;
			tail = nullptr;
			size = 0;
		}
		~Queue() {
			Delete();
		}
		Type Pop()
		{
			if (IsEmpty())
			{
				throw new std::exception("Stack is empty!");
			}
			else
			{
				size--;
				Element<Type>* temp = head;
				head = temp->node;
				Type val = temp->value;
				delete temp;
				return val;
			}
		}
		void Push(Type val)
		{
			if (IsEmpty())
			{
				Element<Type>* newNode = new Element<Type>(val);
				head = newNode;
				tail = newNode;
			}
			else
			{
				Element<Type>* newNode = new Element<Type>(val);
				tail->node = newNode;
				tail = newNode;
			}
			size++;
		}
		void Delete() {
			while (!IsEmpty())
			{
				Pop();
			}
			return;
		}
		bool IsEmpty()
		{
			return size == 0;
		}
	};


	template<class Type> class Stack
	{
	private:
		Element<Type>* stack;
		int size;
	public:
		Stack() {
			stack = nullptr;
			size = 0;
		}
		~Stack() {
			Delete();
		}
		int GetSize() {
			return size;
		}

		void Push(Type val) {
			Element<Type>* newNode;
			if (IsEmpty()) {
				newNode = new Element<Type>(val);
			}
			else
			{
				newNode = new Element<Type>(val, stack);
			}
			stack = newNode;
			++size;
			return;
		}

		Type Pop() {
			if (IsEmpty()) {
				throw std::exception("stack is Empty");
			}
			Type value = stack->value;
			Element<Type>* temp = stack;
			stack = stack->node;
			--size;
			delete temp;
			return value;
		}

		void Delete() {
			while (!IsEmpty())
			{
				Pop();
			}
			return;
		}

		bool IsEmpty()
		{
			return size == 0;
		}
	};
}