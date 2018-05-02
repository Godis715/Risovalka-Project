#ifndef __SET
#define __SET

#include "Pair-Tree.h"

template <typename TKey, typename TValue> class Set {
private:
	template <class TKey, class TVal> class Node
	{
	public:
		Node * rightChild = nullptr;
		Node* leftChild = nullptr;
		Node* parent = nullptr;
		TKey key;
		TVal value;
	};

	int size;
	Node<TKey, TValue>* head;
	Node<TKey, TValue>* support;
	Node<TKey, TValue>* temp;

	void Erase() {
		--size;
		if ((support->rightChild == nullptr) && (support->leftChild == nullptr)) {
			if (support->parent != nullptr) {
				if (support->value <= support->parent->value) {
					support->parent->leftChild = nullptr;
					delete support;
					
				}
				else {
					support->parent->rightChild = nullptr;
					delete support;
				}
			}
			else
			{
				head = nullptr;
				delete support;
			}
			return true;
		}

		if (support->rightChild != nullptr) {
			temp = support->rightChild;
			while (temp->leftChild != nullptr)
			{
				temp = temp->leftChild;
			}

			if (temp == support->rightChild) {
				// проверка, если у большего сына удаляемого елемента нет меньших сыновей
				support->rightChild = temp->rightChild;
			}
			else {
				temp->parent->leftChild = temp->rightChild;
			}
			if (temp->rightChild != nullptr) {
				temp->rightChild->parent = temp->parent;
			}
			support->value = temp->value;
			support->key = temp->key;
			delete temp;
			return;
		}
		else {
			temp = support->leftChild;
			while (temp->rightChild != nullptr)
			{
				temp = temp->rightChild;
			}
			if (temp == support->leftChild) {
				// проверка, если у меньшего сына удаляемого елемента нет больших сыновей
				support->leftChild = temp->leftChild;
			}
			else {
				temp->parent->rightChild = temp->leftChild;
			}
			if (temp->leftChild != nullptr) {
				temp->leftChild->parent = temp->parent;
			}
			support->value = temp->value;
			support->key = temp->key;
			delete temp;
			return;
		}
	}
public:
	Set() {
		head = nullptr;
		support = nullptr;
		temp = nullptr;
		size = 0;
	}

	int getsize() const
	{
		return size;
	}

	bool Push(TKey key, TValue value) {
		size++;
		if (head == nullptr)
		{
			head = new Node<TKey, TValue>;
			head->key = key;
			head->value = value;
			return true;
		}

		support = head;
		while (support != nullptr)
		{
			if (key == support->key) {
				return false;
			}
			if (key > support->key)
			{
				if (support->rightChild != nullptr)
				{
					support = support->rightChild;
				}
				else
				{
					support->rightChild = new Node<TKey, TValue>;
					support->rightChild->key = key;
					support->rightChild->value = value;
					support->rightChild->parent = support;
					return true;
				}
			}
			else
			{
				if (support->leftChild != nullptr)
				{
					support = support->leftChild;
				}
				else
				{
					support->leftChild = new Node<TKey, TValue>;
					support->leftChild->key = key;
					support->leftChild->value = value;
					support->leftChild->parent = support;
					return true;
				}
			}
		}
		return false;
	}

	bool GetByKey(TKey key, TValue& value) {
		support = head;
		while (support != nullptr)
		{
			if (key == support->key) {
				value = support->value;
				return true;
			}
			if (key > support->key)
			{
				if (support->rightChild != nullptr)
				{
					support = support->rightChild;
				}
				else
				{
					return false;
				}
			}
			else
			{
				if (support->leftChild != nullptr)
				{
					support = support->leftChild;
				}
				else
				{
					return false;
				}
			}
		}
		return false;
	}

	TValue PopElement() {
		TValue value;
		if (size == 1) {
			--size;
			value = head->value;
			delete head;
			head = nullptr;
			support = nullptr;
			return value;
		}
		--size;
		support = head;
		while ((support->leftChild != nullptr) || (support->rightChild != nullptr))
		{
			if (support->leftChild != nullptr) {
				support = support->leftChild;
			}
			if (support->rightChild != nullptr) {
				support = support->rightChild;
			}
		}
		if (support == support->parent->leftChild) {
			support->parent->leftChild = nullptr;
			value = support->value;
			delete support;
			return value;
		}
		if (support == support->parent->rightChild) {
			support->parent->rightChild = nullptr;
			value = support->value;
			delete support;
			return value;
		}
	}

	void Erase(const TKey &key) {
		support = head;
		while (support != nullptr)
		{
			if (key == support->key) {
				Erase();
				return;
			}
			if (key > support->key)
			{
				if (support->rightChild != nullptr)
				{
					support = support->rightChild;
				}
				else
				{
					return;
				}
			}
			else
			{
				if (support->leftChild != nullptr)
				{
					support = support->leftChild;
				}
				else
				{
					return;
				}
			}
		}
	}
};

#endif