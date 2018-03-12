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
	public:
		Node* rightChild = nullptr;
		Node* leftChild = nullptr;
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
		_size++;
		if (head == nullptr)
		{
			head = new Node;
			head->key = key;
			head->value = val;
			return;
		}
		Node* temp = head;
		while (temp != nullptr)
		{
			if (key > temp->key)
			{
				if (temp->rightChild != nullptr)
				{
					temp = temp->rightChild;
				}
				else
				{
					temp->rightChild = new Node();
					temp->rightChild->key = key;
					temp->rightChild->value = val;
					temp->rightChild->parent = temp;
					break;
				}
			}
			else
			{
				if (temp->leftChild != nullptr)
				{
					temp = temp->leftChild;
				}
				else
				{
					temp->leftChild = new Node();
					temp->leftChild->key = key;
					temp->leftChild->value = val;
					temp->leftChild->parent = temp;
					break;
				}
			}
		}
	}
	void erase(const T1 &key)
	{

	}
	bool find(T1 key, T2& val)
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
			val = temp->value;
			return true;
		}
	}
};

int main()
{
	Dict<char, int> arr;
	arr.add('a', 5);
	int res = 0;
	//arr.find('a', res);
	cout << arr.find('a', res) << " " << res << "\n";
	system("pause");
	return 0;
}