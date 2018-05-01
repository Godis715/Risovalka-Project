#ifndef __DICT
#define __DICT
#include "Dequeue.h"
#include "Hash-Table.h"

// class - parent of all Nodes
template <class TKey, class TVal> class Node {
public:
	Node(const TKey& _key, const TVal& _val) : key(_key), value(_val)
	{
		right = nullptr;
		left = nullptr;
		parent = nullptr;
		high = 0;
	}
	Node* right = nullptr;
	Node* left = nullptr;
	Node* parent = nullptr;
	TKey key;
	TVal value;
	int high;
};

// class - parent of all dictionaries
template <class TKey, class TVal> class BinSearchTree : public INumerable
{
private:
	int size;
	Node<TKey, TVal>* head;
	Node<TKey, TVal>* current;

	// i think this fields became useless when we'll write marker
	// imho
	Node<TKey, TVal>* support;
	Node<TKey, TVal>* temp;

	virtual Node<TKey, TVal>* CreateNode(const TKey&, const TVal&) = 0;

	void DeleteNode(Node<TKey, TVal>* node) {
		--size;
		if ((node->right == nullptr) && (node->left == nullptr)) {
			if (node->parent != nullptr) {
				if (node->value <= node->parent->value) {
					node = node->parent;
					delete node->left;
					node->left = nullptr;
				}
				else {
					node = node->parent;
					delete node->right;
					node->right = nullptr;
				}
				RestoreHigh(node);
			}
			else
			{
				head = nullptr;
				delete node;
			}
			return;
		}
		// ����������� �� ������ ����� �������
		bool inRight;
		if ((node->right != nullptr) && (node->left != nullptr)) {

			inRight = (node->right->high > node->left->high);

		}
		else {

			inRight = (node->right != nullptr);
		}
		//
		Node<TKey, TVal>* temp = node->right;
		if (inRight) {
			
			while (temp->left != nullptr)
			{
				temp = temp->left;
			}

			//
			temp->left = node->left;
			if (node->left != nullptr) {
				node->left->parent = temp;
			}
			//

			if (temp == node->right) {
				// ��������, ���� � �������� ���� ���������� �������� ��� ������� �������	
				temp->parent = node->parent;
				if (node->parent != nullptr) {
					if (node->value <= node->parent->value) {
						node->parent->left = temp;
					}
					else {
						node->parent->right = temp;
					}
					
				}
				else
				{
					head = temp;
				}
				//
				delete node;
				RestoreHigh(temp);
				return;
			}
			//
			temp->parent->left = temp->right;
			if (temp->right != nullptr) {
				temp->right->parent = temp->parent;
			}
			Node<TKey, TVal>* tempParent = temp->parent;
			//
			temp->parent = node->parent;
			if (node->parent != nullptr) {
				if (node->value <= node->parent->value) {
					node->parent->left = temp;
				}
				else {
					node->parent->right = temp;
				}

			}
			else
			{
				head = temp;
			}
			//
			temp->right = node->right;
			node->right->parent = temp;
			// ��� ��� �������������� ������ ���������� � ����������������,
			// �� �� ������ ���� �� ������ � ���������

			delete node;
			RestoreHigh(tempParent);
			return;
		}
		else {
			while (temp->right != nullptr)
			{
				temp = temp->right;
			}

			//
			temp->right = node->right;
			if (node->right != nullptr) {
				node->right->parent = temp;
			}
			//

			if (temp == node->left) {
				// ��������, ���� � �������� ���� ���������� �������� ��� ������� �������	
				temp->parent = node->parent;
				if (node->parent != nullptr) {
					if (node->value <= node->parent->value) {
						node->parent->right = temp;
					}
					else {
						node->parent->left = temp;
					}

				}
				else
				{
					head = temp;
				}
				//
				delete node;
				RestoreHigh(temp);
				return;
			}
			//
			temp->parent->right = temp->right;
			if (temp->left != nullptr) {
				temp->left->parent = temp->parent;
			}
			Node<TKey, TVal>* tempParent = temp->parent;
			//
			temp->parent = node->parent;
			if (node->parent != nullptr) {
				if (node->value <= node->parent->value) {
					node->parent->right = temp;
				}
				else {
					node->parent->left = temp;
				}

			}
			else
			{
				head = temp;
			}
			//
			temp->left = node->lefy;
			node->left->parent = temp;
			// ��� ��� �������������� ������ ���������� � ����������������,
			// �� �� ������ ���� �� ������ � ���������

			delete node;
			RestoreHigh(tempParent);
			return;
		}
	}

	void AddNode(const TKey& key, const TVal& val) {
		size++;
		if (head == nullptr)
		{
			head = CreateNode();
			head->key = key;
			head->value = val;
			head->high = 1;
			return;
		}

		Node<TKey, TVal>* node = head;
		while (node != nullptr)
		{
			if (key > node->key)
			{
				if (node->right != nullptr)
				{
					node = node->right;
				}
				else
				{
					node->right = CreateNode(key, val);
					node->right->parent = node;
					node->right->high = 1;
					RestoreHigh(node);
					return;
				}
			}
			else
			{
				if (node->left != nullptr)
				{
					node = node->left;
				}
				else
				{
					node->left = CreateNode(key, val);
					node->left->parent = node;
					RestoreHigh(node);
					return;
				}
			}
		}
	}

	void LL(Node<TKey, TVal>* node) {
		Node<TKey, TVal>* temp = node->left;
		node->left = temp->right;
		if (temp->right != nullptr) {
			temp->right->parent = node;
		}
		temp->right = node;
		if (node->parent != nullptr) {
			if (node->key > node->parent->key) {
				node->parent->right = temp;
			}
			else {
				node->parent->left = temp;
			}
			temp->parent = node->parent;
		}
		else {
			temp->parent = nullptr;
			head = temp;
		}
		node->parent = temp;
		RestoreHighOnce(node);
		RestoreHighOnce(temp);
	}

	void RR(Node<TKey, TVal>* node) {
		Node<TKey, TVal>* temp = node->right;
		node->right = temp->left;
		if (temp->left != nullptr) {
			temp->left->parent = node;
		}
		temp->left = node;
		if (node->parent != nullptr) {
			if (node->key > node->parent->key) {
				node->parent->right = temp;
			}
			else {
				node->parent->left = temp;
			}
			temp->parent = node->parent;
		}
		else {
			temp->parent = nullptr;
			head = temp;
		}
		node->parent = temp;
		RestoreHighOnce(node);
		RestoreHighOnce(temp);
	}

	void RL(Node<TKey, TVal>* node) {
		node = node->right;
		LL(node);
		// ������ �����, ���� node ��� ���������� �� ���� ����
		node = node->parent->parent;
		RR(node);
	}

	void LR(Node<TKey, TVal>* node) {
		node = node->left;
		RR(node);
		// ������ �����, ���� node ��� ���������� �� ���� ����
		node = node->parent->parent;
		LL(node);
	}

	void RestoreBalance(Node<TKey, TVal>* node) {
		int leftHigh = 0;
		int rightHigh = 0;
		if (node->left != nullptr) {
			leftHigh = node->left->high;
		}
		if (node->right != nullptr) {
			rightHigh = node->right->high;
		}

		if (rightHigh > leftHigh) {
			leftHigh = 0;
			rightHigh = 0;
			if (node->right->left != nullptr) {
				leftHigh = node->right->left->high;
			}
			if (node->right->right != nullptr) {
				rightHigh = node->right->right->high;
			}
			if (rightHigh >= leftHigh) {
				RR(node);
				return;
			}
			else {
				RL(node);
				return;
			}
		}
		else {
			leftHigh = 0;
			rightHigh = 0;
			if (node->left->left != nullptr) {
				leftHigh = node->left->left->high;
			}
			if (node->left->right != nullptr) {
				rightHigh = node->left->right->high;
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

	void RestoreHigh(Node<TKey, TVal>* node) {
		while (node != nullptr)
		{
			int leftHigh = 0;
			int rightHigh = 0;
			if (node->left != nullptr) {
				leftHigh = node->left->high;
			}
			if (node->right != nullptr) {
				rightHigh = node->right->high;
			}
			if (rightHigh > leftHigh) {
				node->high = rightHigh + 1;
			}
			else {
				node->high = leftHigh + 1;
			}
			if ((rightHigh > leftHigh + 1) || (rightHigh + 1 < leftHigh)) {
				RestoreBalance(node);
			}
			node = node->parent;
		}
	}

	void RestoreHighOnce(Node<TKey, TVal>* node) {
		int leftHigh = 0;
		int rightHigh = 0;
		if (node->left != nullptr) {
			leftHigh = node->left->high;
		}
		if (node->right != nullptr) {
			rightHigh = node->right->high;
		}
		if (rightHigh > leftHigh) {
			node->high = rightHigh + 1;
		}
		else {
			node->high = leftHigh + 1;
		}
	}

public:
	BinSearchTree()
	{
		head = nullptr;
		current = nullptr;
		support = nullptr;
		temp = nullptr;
		size = 0;
	}

	~BinSearchTree() {
		DeleteDict();
	}

	class Marker : public IMarker {
	private:
		Node<TKey, TVal>* current;
		BinSearchTree<TKey, TVal>* tree;
		
	public:
		Marker(BinSearchTree<TKey, TVal>* _tree) : tree(_tree) {
			if (tree == nullptr || tree->head == nullptr) {
				isValid = false;
				return;
			}
			MoveBegin();
		}
		TVal GetValue() const {
			if (!isValid) {
				throw std::exception("Marker was not valid");
			}
			return current->value;
		}
		bool MoveNext() {
			if (!isValid) {
				return false;
			}
			if (current == nullptr) {
				return false;
			}
			if (current->right != nullptr) {
				current = current->right;
				while (current->left != nullptr)
				{
					current = current->left;
				}
				return true;
			}
			if (current->parent != nullptr) {
				if (current == current->parent->left) {
					current = current->parent;
					return true;
				}
				temp = current;
				current = current->parent;
				while ((current != nullptr) && (current->right == temp))
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
		}
		bool MoveBegin() {
			if (tree == nullptr || tree->head == nullptr) {
				isValid = false;
				return false;
			}
			isValid = true;
			current = tree->head;
			while (current->left != nullptr)
			{
				current = current->left;
			}
			return true;
		}
		void DeleteCurrent() {
			if (!isValid) {
				return;
			}
			
		}
	};

	int GetSize() const
	{
		return size;
	}

	virtual void Add(const TKey &key, const TVal &val) {
		AddNode(key, val);
	}

	/*void Erase(const TKey &key) {
		support = head;
		while (support != nullptr)
		{
			if (key == support->key) {
				Erase();
				return;
			}
			if (key > support->key)
			{
				if (support->right != nullptr)
				{
					support = support->right;
				}
				else
				{
					return;
				}
			}
			else
			{
				if (support->left != nullptr)
				{
					support = support->left;
				}
				else
				{
					return;
				}
			}
		}
	}*/

	IMarker* Find(const TKey &key)
	{
		Node<TKey, TVal>* node = head;
		while (node != nullptr)
		{
			if (node->key == key) {
				return new Marker(node);
			}
			if (key > node->key)
			{
				if (node->right != nullptr)
				{
					node = node->right;
				}
				else
				{
					return nullptr;
				}
			}
			else
			{
				if (node->left != nullptr)
				{
					node = node->left;
				}
				else
				{
					return nullptr;
				}
			}
		}
		return nullptr;
	}

	void DeleteDict() {
		if (head == nullptr) {
			return;
		}
		temp = head;
		Deck<Node<TKey, TVal>*> deck;
		deck.PushTail(temp);
		while (deck.GetSize() > 0)
		{
			temp = deck.PopTail();
			if (temp->left != nullptr) {
				deck.PushTail(temp->left);
			}
			if (temp->right != nullptr) {
				deck.PushTail(temp->right);
			}
			delete temp;
		}
		size = 0;
	}
};

template <class TKey, class TVal> class Dict : public BinSearchTree<TKey, TVal> {
private:
	template <class TKey, class TVal> class DictNode : public Node<TKey, TVal> {
		DictNode(const TKey& _key, const TVal& _val) : Node<TKey, TVal>(const TKey& _key, const TVal& _val) { }
	};
	Node<TKey, TVal>* CreateNode(const TKey& _key, const TVal& _val)
	{
		return new DictNode(_key, _val);
	}
public:

};


#endif