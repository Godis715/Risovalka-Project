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
	int getVal()
	{
		return value;
	}
	void setNext(Node* nxt)
	{
		next = nxt;
	}

	int GetValue() {
		return value;
	}
};

class List
{
private:
	int listSize = 0;
	Node* head = nullptr;
	Node* tail = nullptr;

	void insert(int value, Node* addAfter)
	{
		Node* temp = new Node();
		temp->setNext(addAfter->getNext());
		temp->setVal(value);
		addAfter->setNext(temp);
	}
public:
	List()
	{
		int listSize = 0;
		Node* head = nullptr;
		Node* tail = nullptr;
	}
	void newHead(int value)
	{
		if (listSize == 0)
		{
			head = tail = new Node();
			head->setVal(value);
		}
		else
		{
			Node* temp = new Node();
			temp->setNext(head);
			temp->setVal(value);
			head = temp;
		}
		listSize++;
	}
	void addElement(int value)
	{
		if (listSize == 0)
		{
			head = tail = new Node();
			head->setVal(value);
		}
		else
		{
			insert(value, tail);
			tail = tail->getNext();
		}
		listSize++;

	}
	void addElement(int value, int index)
	{
		if (listSize == 0)
		{
			head = tail = new Node();
			head->setVal(value);
		}
		else
		{
			if (index < listSize)
			{
				Node* curr = head;
				int i = 0;
				while (i != index)
				{
					curr = curr->getNext();
					i++;
				}
				insert(value, curr);
				if (i = listSize - 1)
				{
					tail = tail->getNext();
				}
				listSize++;
			}
		}
	}
};

int main()
{

}