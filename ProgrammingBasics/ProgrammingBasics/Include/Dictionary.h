#ifndef __DICT
#define __DICT
#include "Dequeue.h"
#include "Hash-Table.h"

template <class TKey, class TVal> class Pair
{
	TKey first;
	TVal second;
};

template <class TKey, class TVal> class Dict
{
private:

	template <class TKey, class TVal> class Node
	{
	public:
		Node* rightChild = nullptr;
		Node* leftChild = nullptr;
		Node* parent = nullptr;
		TKey key;
		TVal value;
		int high = 1;
	};

	int size;
	Node<TKey, TVal>* head;
	Node<TKey, TVal>* current;
	Node<TKey, TVal>* support;
	Node<TKey, TVal>* temp;

	void LL() {
		temp = support->leftChild;
		support->leftChild = temp->rightChild;
		if (temp->rightChild != nullptr) {
			temp->rightChild->parent = support;
		}
		temp->rightChild = support;
		if (support->parent != nullptr) {
			if (support->key > support->parent->key) {
				support->parent->rightChild = temp;
			}
			else {
				support->parent->leftChild = temp;
			}
			temp->parent = support->parent;
		}
		else {
			temp->parent = nullptr;
			head = temp;
		}
		support->parent = temp;
		RestoreHighOnce(support);
		RestoreHighOnce(temp);
	}

	void RR() {
		temp = support->rightChild;
		support->rightChild = temp->leftChild;
		if (temp->leftChild != nullptr) {
			temp->leftChild->parent = support;
		}
		temp->leftChild = support;
		if (support->parent != nullptr) {
			if (support->key > support->parent->key) {
				support->parent->rightChild = temp;
			}
			else {
				support->parent->leftChild = temp;
			}
			temp->parent = support->parent;
		}
		else {
			temp->parent = nullptr;
			head = temp;
		}
		support->parent = temp;
		RestoreHighOnce(support);
		RestoreHighOnce(temp);
	}

	void RL() {
		support = support->rightChild;
		LL();
		// дважды вверх, ведь support там опускается на один вниз
		support = support->parent->parent;
		RR();
	}

	void LR() {
		support = support->leftChild;
		RR();
		// дважды вверх, ведь support там опускается на один вниз
		support = support->parent->parent;
		LL();
	}

	void RestoreBalance() {
		int leftHigh = 0;
		int rightHigh = 0;
		if (support->leftChild != nullptr) {
			leftHigh = support->leftChild->high;
		}
		if (support->rightChild != nullptr) {
			rightHigh = support->rightChild->high;
		}

		if (rightHigh > leftHigh) {
			leftHigh = 0;
			rightHigh = 0;
			if (support->rightChild->leftChild != nullptr) {
				leftHigh = support->rightChild->leftChild->high;
			}
			if (support->rightChild->rightChild != nullptr) {
				rightHigh = support->rightChild->rightChild->high;
			}
			if (rightHigh >= leftHigh) {
				RR();
				return;
			}
			else {
				RL();
				return;
			}
		}
		else {
			leftHigh = 0;
			rightHigh = 0;
			if (support->leftChild->leftChild != nullptr) {
				leftHigh = support->leftChild->leftChild->high;
			}
			if (support->leftChild->rightChild != nullptr) {
				rightHigh = support->leftChild->rightChild->high;
			}
			if (leftHigh >= rightHigh) {
				LL();
				return;
			}
			else {
				LR();
				return;
			}
		}
	}

	void RestoreHigh() {
		while (support != nullptr)
		{
			int leftHigh = 0;
			int rightHigh = 0;
			if (support->leftChild != nullptr) {
				leftHigh = support->leftChild->high;
			}
			if (support->rightChild != nullptr) {
				rightHigh = support->rightChild->high;
			}
			if (rightHigh > leftHigh) {
				support->high = rightHigh + 1;
			}
			else {
				support->high = leftHigh + 1;
			}
			if ((rightHigh > leftHigh + 1) || (rightHigh + 1 < leftHigh)) {
				RestoreBalance();
			}
			support = support->parent;
		}
	}

	void RestoreHighOnce(Node<TKey, TVal>* node) {
		int leftHigh = 0;
		int rightHigh = 0;
		if (node->leftChild != nullptr) {
			leftHigh = node->leftChild->high;
		}
		if (node->rightChild != nullptr) {
			rightHigh = node->rightChild->high;
		}
		if (rightHigh > leftHigh) {
			node->high = rightHigh + 1;
		}
		else {
			node->high = leftHigh + 1;
		}
	}

	void Erase() {
		--size;
		if ((support->rightChild == nullptr) && (support->leftChild == nullptr)) {
			// если мы стоим на удаляемом
			if (current == support) {
				current = support->parent;
			}
			if (support->parent != nullptr) {
				if (support->value <= support->parent->value) {
					support = support->parent;
					delete support->leftChild;
					support->leftChild = nullptr;
				}
				else {
					support = support->parent;
					delete support->rightChild;
					support->rightChild = nullptr;
				}
				RestoreHigh();
			}
			else
			{
				head = nullptr;
				current = nullptr;
				delete support;
			}
			return;
		}
		// определение из какого лучше удалять
		bool inRight;
		if ((support->rightChild != nullptr) && (support->leftChild != nullptr)) {
			if (support->rightChild->high > support->leftChild->high) {
				inRight = true;
			}
			else {
				inRight = false;
			}
		}
		else {
			if (support->rightChild != nullptr) {
				inRight = true;
			}
			else {
				inRight = false;
			}
		}
		//
		if (inRight) {
			temp = support->rightChild;
			while (temp->leftChild != nullptr)
			{
				temp = temp->leftChild;
			}

			if (temp == support->rightChild) {
				// проверка, если у большего сына удаляемого елемента нет меньших сыновей
				support->rightChild = temp->rightChild;
				if (temp->rightChild != nullptr) {
					temp->rightChild->parent = support;
				}
				support->value = temp->value;
				support->key = temp->key;
				delete temp;
				RestoreHigh();
				return;
			}
			temp->parent->leftChild = temp->rightChild;
			if (temp->rightChild != nullptr) {
				temp->rightChild->parent = temp->parent;
			}
			support->value = temp->value;
			support->key = temp->key;
			// так как восстановление высоты происходит с вспомогательного,
			// то он должен быть на уровне с удаляемым
			support = temp->parent;
			delete temp;
			RestoreHigh();
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
				if (temp->leftChild != nullptr) {
					temp->leftChild->parent = support;
				}
				support->value = temp->value;
				support->key = temp->key;
				support = temp->parent;
				delete temp;
				RestoreHigh();
				return;
			}
			temp->parent->rightChild = temp->leftChild;
			if (temp->leftChild != nullptr) {
				temp->leftChild->parent = temp->parent;
			}
			support->value = temp->value;
			// так как восстановление высоты происходит с вспомогательного,
			// то он должен быть на уровне с удаляемым
			support->key = temp->key;
			delete temp;
			RestoreHigh();
			return;
		}
	}
public:
	Dict()
	{
		head = nullptr;
		current = nullptr;
		support = nullptr;
		temp = nullptr;
		size = 0;
	}

	int GetSize() const
	{
		return size;
	}

	void Add(const TKey &key, const TVal &val)
	{
		size++;
		if (head == nullptr)
		{
			head = new Node<TKey, TVal>;
			head->key = key;
			head->value = val;
			head->high = 1;
			current = head;
			return;
		}

		support = head;
		while (support != nullptr)
		{
			if (key > support->key)
			{
				if (support->rightChild != nullptr)
				{
					support = support->rightChild;
				}
				else
				{
					support->rightChild = new Node<TKey, TVal>;
					support->rightChild->key = key;
					support->rightChild->value = val;
					support->rightChild->parent = support;
					support->rightChild->high = 1;
					RestoreHigh();
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
					support->leftChild = new Node<TKey, TVal>;
					support->leftChild->key = key;
					support->leftChild->value = val;
					support->leftChild->parent = support;
					RestoreHigh();
					return;
				}
			}
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

	void DeleteCurrent() {
		if (current == nullptr) {
			return;
		}
		support = current;
		MoveNext();
		Erase();
	}

	bool Find(const TKey &key)
	{
		support = head;
		while (support != nullptr)
		{
			if (support->key == key) {
				current = support;
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
	}

	void MoveHead() {
		current = head;
	}

	bool MoveParent() {
		if (current == nullptr) {
			return false;
		}
		if (current->parent == nullptr) {
			return false;
		}
		current = current->parent;
		return true;
	}

	bool MoveLeft() {
		if (current == nullptr) {
			return false;
		}
		if (current->leftChild == nullptr) {
			return false;
		}
		current = current->leftChild;
		return true;
	}

	bool MoveRight() {
		if (current == nullptr) {
			return false;
		}
		if (current->rightChild == nullptr) {
			return false;
		}
		current = current->rightChild;
		return true;
	}

	void MoveBegin() {
		if (head == nullptr) {
			return;
		}
		current = head;
		while (current->leftChild != nullptr)
		{
			current = current->leftChild;
		}
	}

	void MoveEnd() {
		if (head == nullptr) {
			return;
		}
		current = head;
		while (current->rightChild != nullptr)
		{
			current = current->rightChild;
		}
	}

	bool MoveNext() {
		if (current == nullptr) {
			return false;
		}
		if (current->rightChild != nullptr) {
			current = current->rightChild;
			while (current->leftChild != nullptr)
			{
				current = current->leftChild;
			}
			return true;
		}
		if (current->parent != nullptr) {
			if (current == current->parent->leftChild) {
				current = current->parent;
				return true;
			}
			temp = current;
			current = current->parent;
			while ((current != nullptr) && (current->rightChild == temp))
			{
				temp = current;
				current = current->parent;
			}
			if (current == nullptr) {
				current = head;
				return false;
			}
			else {
				return true;
			}
		}
		return false;
		// if false then current = head
	}

	bool MovePrev() {
		if (current == nullptr) {
			return false;
		}
		if (current->leftChild != nullptr) {
			current = current->leftChild;
			return true;
		}
		if (current->parent != nullptr) {
			if (current == current->parent->rightChild) {
				current = current->parent;
				return true;
			}
			temp = current;
			current = current->parent;
			while ((current != nullptr) && (current->leftChild == temp))
			{
				temp = current;
				current = current->parent;
			}
			if (current == nullptr) {
				current = head;
				return false;
			}
			else {
				return true;
			}
		}
		return false;
		// if false then current = head
	}

	bool IsCurrent() {
		if (current == nullptr) {
			return false;
		}
		else {
			return true;
		}
	}

	TVal GetCurrent() const {
		if (current == nullptr) {
			throw std::exception("use is current, it was nullptr");
		}
		else {
			return current->value;
		}
	}

	TKey GetCurrentKey() {
		if (current == nullptr) {
			throw std::exception("use is current, it was nullptr");
		}
		else {
			return current->key;
		}
	}

	void DeleteDict() {
		temp = head;
		Deck<Node<TKey, TVal>*> deck;
		deck.PushTail(temp);
		while (deck.GetSize() > 0)
		{
			temp = deck.PopTail();
			if (temp->leftChild != nullptr) {
				deck.PushTail(temp->leftChild);
			}
			if (temp->rightChild != nullptr) {
				deck.PushTail(temp->rightChild);
			}
			delete temp;
		}
		temp = nullptr;
		head = nullptr;
		current = nullptr;
		support = nullptr;
		size = 0;
	}
};

#endif