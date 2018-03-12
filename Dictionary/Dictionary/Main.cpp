#include <iostream>

using namespace std;

template <class T1, class T2> class Pair
{
	T1 first;
	T2 second;
};

template <class T1, class T2> class Dict
{
private:
	int _size = 0;

	static class Node
	{
		Node* rightSon = nullptr;
		Node* leftSon = nullptr;
		Node* parent = nullptr;
		T1 key;
		T2 value;
	};

	Node* head = nullptr;

public:
	Dict()
	{

	}
	int getsize()
	{
		return _size;
	}
	void add(const T1 &key, const T2 &val)
	{

	}
	void erase(const T1 &key)
	{

	}
	bool find(T1 key, T2 &val)
	{
		Node* temp = head;
		while (temp->key != key && temp->leftChild != nullptr && temp->rightChild != nullptr)
		{
			if (temp->key < key)
			{
				temp = temp->rightChild;
			}
			else
			{
				temp = temp->leftChild;
			}
		}
		if (temp->key != key)
			return false;
		else
		{
			value = temp->value;
			return true;
		}
	}
};

int main()
{

}