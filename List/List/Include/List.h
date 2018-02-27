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
public:
	List();	
	class Marker
	{
	private:
		Node* current;
		List* listForMarker;
	public:
		Marker(List* list)
		{
			current = list->head;
			listForMarker = list;
		}
		bool moveNext();
		int getCurrent() const;
		void setCurrent(int value);
		void moveTail();
		void moveHead();
		void addAfter(int val);
		void deleteAfter();
	};
	
	int getSize();
	void addElementBeforeHead(int val);
	void addElementAfterTail(int val);
	void deleteHeadElement();
	void deleteTailElement();
	Marker* createMarker();
};

#endif