#ifndef __DICT
#define __DICT

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
	Node* find(T1 key)
	{
		Node* temp = head;
		while (temp->key != key && temp != nullptr)
		{
			if (temp->key < key)
			{
				if (temp->rightChild != nullptr)
				{
					temp = temp->rightChild;
				}
				else
				{
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
					break;
				}
			}
		}
		if (temp->key != key || temp == nullptr)
			return nullptr;
		else
		{
			return temp;
		}
	}
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
		Node* temp = find(key);
		if (temp == nullptr) {
			return;
		}
		bool isRight = false;
		if (temp->parent != nullptr) {
			if (temp->parent->key < temp->key) {
				isRight = true;
			}
		}
		if (temp->rightChild == nullptr) {
			if (temp->leftChild == nullptr) {
				if (temp == head) {
					head = nullptr;
				}
				else {
					if (isRight) {
						temp->parent->rightChild = nullptr;
					}
					else {
						temp->parent->leftChild = nullptr;
					}
				}
				delete temp;
				--_size;
				return;
			}

			Node* right = temp->leftChild;
			if (right->rightChild == nullptr) {
				right->parent = temp->parent;
				if (temp == head) {
					head = right;
				}
				else {
					if (isRight) {
						temp->parent->rightChild = right;
					}
					else {
						temp->parent->leftChild = right;
					}
				}
				delete temp;
				--_size;
				return;
			}
			while (right->rightChild != nullptr)
			{
				right = right->rightChild;
			}

			if (right->leftChild != nullptr) {
				right->parent->rightChild = right->leftChild;
				right->leftChild->parent = right->parent;
			}
			else {
				right->parent = nullptr;
			}
			right->leftChild = temp->leftChild;
			right->leftChild->parent = right;
			right->parent = temp->parent;
			if (temp == head) {
				head = right;
			}
			else {
				if (isRight) {
					temp->parent->rightChild = right;
				}
				else {
					temp->parent->leftChild = right;
				}
			}
			delete temp;
			--_size;
			return;
		}

		Node* left = temp->rightChild;
		if (left->leftChild == nullptr) {
			if (temp->leftChild != nullptr) {
				left->leftChild = temp->leftChild;
				left->leftChild->parent = left;
			}
			left->parent = temp->parent;
			if (temp == head) {
				head = left;
			}
			else {
				if (isRight) {
					temp->parent->rightChild = left;
				}
				else {
					temp->parent->leftChild = left;
				}
			}
			delete temp;
			--_size;
			return;
		}

		while (left->leftChild != nullptr)
		{
			left = left->leftChild;
		}
		if (left->rightChild != nullptr) {
			left->parent->leftChild = left->rightChild;
			left->rightChild = left->parent;
		}
		else {
			left->parent = nullptr;
		}
		left->rightChild = temp->rightChild;
		left->rightChild->parent = left;
		if (temp->leftChild != nullptr) {
			left->leftChild = temp->leftChild;
			left->leftChild->parent = left;
		}
		if (temp == head) {
			head = left;
		}
		else {
			if (isRight) {
				temp->parent->rightChild = left;
			}
			else {
				temp->parent->leftChild = left;
			}
		}
		delete temp;
		--_size;
		return;
	}

	bool find(T1 key, T2& val)
	{
		Node* temp = head;
		while (temp != nullptr && temp->key != key)
		{
			if (temp->key < key)
			{
				if (temp->rightChild != nullptr)
				{
					temp = temp->rightChild;
				}
				else
				{
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
					break;
				}
			}
		}
		if (temp->key != key || temp == nullptr)
			return false;
		else
		{
			val = temp->value;
			return true;
		}
	}
};

#endif