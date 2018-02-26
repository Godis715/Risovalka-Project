#ifndef __LIST_H
#define __LIST_H

class List
{
private:
	class Node
	{
	private:
		int value;
		Node* next;
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

		void setNext(Node* nxt)
		{
			next = nxt;
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

	Node* head;
	Node* tail;
	int size;
	Node* current;

	Node* getHead();
	Node* getTail();
public:
	List();	
	int getSize();
	void moveTail();
	void moveHead();
	bool moveNext();
	int getCurrent();	
	void setCurrent(int newVal);
	void addElementBeforeHead(int val);
	void addElementAfterTail(int val);
	void addElementAfterCurrent(int val);
	void deleteAfterCurrentElement();
	void deleteHeadElement();
	void deleteTailElement();
	int getValueAt(int index) const;
	void setCurrentAt(int index);
};

#endif