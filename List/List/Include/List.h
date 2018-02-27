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
		Node* current = nullptr;
		List* ListForMarker;
	public:
		Marker(List* list)
		{
			current = list->head;
			ListForMarker = list;
		}
		Node* getCurrent();
		bool moveNext();
		void moveTail();
		void moveHead();
	};
	int getSize();
	void addElementBeforeHead(int val);
	void addElementAfterTail(int val);
	void addElementAfterMarker(int val, List::Marker marker);
	void deleteAfterMarkerElement(List::Marker marker);
	void deleteHeadElement();
	void deleteTailElement();
	int getValueAt(int index) const;
	void setCurrentAt(int index);
};

#endif