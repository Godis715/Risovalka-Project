#include <iostream>

using namespace std;

class List
{
private:
	class Node
	{
	private:
		int value = 0;
		Node* next = nullptr;

	public:

		Node()
		{
			value = 0;
			next = 0;
		}

		Node* getNext()
		{
			return next;
		}

		int getValue()
		{
			return value;
		}

		void setValue(int newVal)
		{
			value = newVal;
		}
	};

	Node* head = nullptr;
	Node* tail = nullptr;
	int size = 0;
	Node* current = head;

	Node* getHead()
	{
		return head;
	}

	Node* getTail()
	{
		return tail;
	}


public:

	List()
	{
		head = nullptr;
		tail = nullptr;
		size = 0;
		current = head;
	}

	int getSize()
	{
		return size;
	}

	void moveTail()
	{
		current = this->getTail();
	}

	void moveHead()
	{
		current = this->getHead();
	}

	void moveNext()
	{
		current = current->getNext();
	}

	int getCurrent()
	{
		return current->getValue();
	}

	void setCurrent(int newVal)
	{
		current->setValue(newVal);
	}

	//Plombs below
	void addElementBeforeHead()
	{

	}

	void addElementAfterTail()
	{

	}

	void addElementAfterCurrent()
	{

	}

	void deleteCurrentElement()
	{

	}

	void deleteHeadElement()
	{

	}

	void deleteTailElement()
	{

	}
};

int main()
{
	List myList;
}