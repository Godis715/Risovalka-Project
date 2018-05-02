#pragma once
#include "INumerable.h"

template <class T> class Queue
{
private:
	struct Node
	{
		T value;
		Node* prev;
		Node* next;
	};
	Node* head = nullptr;
	Node* tail = nullptr;
	int size = 0;
public:
	T pop()
	{
		if (isEmpty())
		{
			throw new std::exception("Stack is empty!");
		}
		else
		{
			size--;
			Node* temp = tail;
			tail = temp->next;
			T val = temp->value;
			delete temp;
			return val;
		}
	}
	void push(T val)
	{
		if (isEmpty())
		{
			Node* newNode = new Node{ val, nullptr, nullptr };
			head = tail = newNode;
		}
		else
		{
			Node* newNode = new Node{ val, head, nullptr };
			head->next = newNode;
			head = newNode;
		}
		size++;
	}
	bool isEmpty()
	{
		return size == 0;
	}
};
