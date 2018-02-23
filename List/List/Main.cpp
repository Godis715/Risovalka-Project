#include <iostream>

using namespace std;

class Node
{
private:
	int value = 0;
	Node* next = nullptr;

public:
	Node()
	{
		int value = 0;
		Node* next = nullptr;
	}
	
	Node* getNext()
	{
		return next;
	}

	void setVal(int val)
	{
		value = val;
	}

	void setNext(Node* nxt)
	{
		next = nxt;
	}
};

class List
{
private:
	int listSize = 0;
	Node* head = nullptr;
	Node* tail = nullptr;

public:
	List()
	{
		int listSize = 0;
		Node* head = nullptr;
		Node* tail = nullptr;
	}

	void addElement(int value)
	{
		if (listSize == 0)
		{
			head = tail = new Node();
			head->setVal(value);
		}
	}

	void addElement(int value, Node* addAfter)
	{
		Node* temp = nullptr;
		temp->setVal(addAfter->getNext);
		addAfter->setNext(new Node());
		addAfter->getNext.setNext(temp);
	}
};

int main()
{

}