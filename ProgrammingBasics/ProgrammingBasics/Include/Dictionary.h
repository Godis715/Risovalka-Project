#ifndef __DICT
#define __DICT

#include "Array.h"
#include "Queue.h"

// class - parent of all Nodes
template <class Type> class Node {
public:
	Node(Type& _val) : value(_val)
	{
		right = nullptr;
		left = nullptr;
		parent = nullptr;
		high = 0;
	}
	Node(const Type& _val) : value(_val)
	{
		right = nullptr;
		left = nullptr;
		parent = nullptr;
		high = 0;
	}

	Node* right = nullptr;
	Node* left = nullptr;
	Node* parent = nullptr;
	Type value;
	int high;
};

// class - parent of all dictionaries
template <class TKey, class TVal> class BinSearchTree
{
private:
	typedef std::pair<TKey, TVal> T;

	virtual Node<T>* CreateNode(const TKey& _key, const TVal& _val) {
		T pair(_key, _val);
		
		return new Node<T>(pair);
	}

	Node<T>* AddNode(const TKey& key, const TVal& val) {
		size++;
		if (head == nullptr)
		{
			head = CreateNode(key, val);
			head->value.first = key;
			head->value.second = val;
			head->high = 1;
			return head;
		}

		Node<T>* node = head;
		while (node != nullptr)
		{
			if (key > node->value.first)
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
					return node->right;
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
					node->left->high = 1;
					RestoreHigh(node);
					return node->left;
				}
			}
		}
	}

	void LL(Node<T>* node) {
		Node<T>* temp = node->left;
		node->left = temp->right;
		if (temp->right != nullptr) {
			temp->right->parent = node;
		}
		temp->right = node;
		if (node->parent != nullptr) {
			if (node ==  node->parent->right) {
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

	void RR(Node<T>* node) {
		Node<T>* temp = node->right;
		node->right = temp->left;
		if (temp->left != nullptr) {
			temp->left->parent = node;
		}
		temp->left = node;
		if (node->parent != nullptr) {
			if (node == node->parent->right) {
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

	void RL(Node<T>* node) {
		node = node->right;
		LL(node);
		// ������ �����, ���� node ��� ���������� �� ���� ����
		node = node->parent->parent;
		RR(node);
	}

	void LR(Node<T>* node) {
		node = node->left;
		RR(node);
		// ������ �����, ���� node ��� ���������� �� ���� ����
		node = node->parent->parent;
		LL(node);
	}

	void RestoreBalance(Node<T>* node) {
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
				LL(node);
				return;
			}
			else {
				LR(node);
				return;
			}
		}
	}

	void RestoreHighOnce(Node<T>* node) {
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

protected:
	int size;
	Node<T>* head;

	void RestoreHigh(Node<T>* node) {
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

	Node<T>* FindNode(const TKey& key) {
		Node<T>* node = head;
		while (node != nullptr)
		{
			if (node->value.first == key) {
				return node;
			}
			if (key > node->value.first)
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

	void DeleteNode(Node<T>* node) {
		--size;
		if ((node->right == nullptr) && (node->left == nullptr)) {
			if (node->parent != nullptr) {
				if (node->value.first > node->parent->value.first) {
					node = node->parent;
					delete node->right;
					node->right = nullptr;
				}
				else {
					node = node->parent;
					delete node->left;
					node->left = nullptr;
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

			inRight = (node->right->high >= node->left->high);
		}
		else {

			inRight = (node->right != nullptr);
		}
		//
		Node<T>* temp = node->right;
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
					if (node->value.first > node->parent->value.first) {
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
			temp->parent->left = temp->right;
			if (temp->right != nullptr) {
				temp->right->parent = temp->parent;
			}
			Node<T>* tempParent = temp->parent;
			//
			temp->parent = node->parent;
			if (node->parent != nullptr) {
				if (node->value.first > node->parent->value.first) {
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
			temp->right = node->right;
			node->right->parent = temp;
			// ��� ��� �������������� ������ ���������� � ����������������,
			// �� �� ������ ���� �� ������ � ���������

			delete node;
			RestoreHigh(tempParent);
			return;
		}
		else {
			temp = node->left;
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
					if (node->value.first > node->parent->value.first) {
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
			temp->parent->right = temp->left;
			if (temp->left != nullptr) {
				temp->left->parent = temp->parent;
			}
			Node<T>* tempParent = temp->parent;
			//
			temp->parent = node->parent;
			if (node->parent != nullptr) {
				if (node->value.first > node->parent->value.first) {
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
			temp->left = node->left;
			node->left->parent = temp;

			delete node;
			RestoreHigh(tempParent);
			return;
		}
	}

public:
	BinSearchTree()
	{
		head = nullptr;
		size = 0;
	}

	BinSearchTree(const BinSearchTree& tree) {
		this->head = tree.head;
		this->size = tree.size;
	}

	BinSearchTree(BinSearchTree&& tree) {
		this->head = tree.head;
		this->size = tree.size;

		tree.head = nullptr;
		tree.size = 0;
	}

	void operator=(const BinSearchTree& tree) {
		this->head = tree.head;
		this->size = tree.size;
	}

	void operator=(BinSearchTree&& tree) {
		this->head = tree.head;
		this->size = tree.size;

		tree.head = nullptr;
		tree.size = 0;
	}

	~BinSearchTree() {
		DeleteDict();
	}

	class bst_iterator {
	protected:
		Node<T>* current;

		BinSearchTree<TKey, TVal>* tree;
		bool isValid;

		bool MoveNext() {
			if (!isValid) {
				return false;
			}
			if (current == nullptr) {
				isValid = false;
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
				Node<T>* temp = current;
				current = current->parent;
				while ((current != nullptr) && (current->right == temp))
				{
					temp = current;
					current = current->parent;
				}
				if (current == nullptr) {
					current = tree->head;
					isValid = false;
					return false;
				}
				else {
					return true;
				}
			}
			isValid = false;
			return false;
		}

		
	public:
		bst_iterator() { }
		bst_iterator(BinSearchTree<TKey, TVal>* _tree) : tree(_tree) {
			if (tree == nullptr || tree->head == nullptr) {
				isValid = false;
				return;
			}
			isValid = true;
			Begin();
		}
		bst_iterator(BinSearchTree<TKey, TVal>* _tree, Node<T>* node) : tree(_tree) {
			if (tree == nullptr || tree->head == nullptr || node == nullptr) {
				isValid = false;
				return;
			}
			isValid = true;
			current = node;
		}
		bst_iterator(bst_iterator&& marker) {
			this->isValid = marker.isValid;
			this->tree = marker.tree;
			this->current = marker.current;

			marker.tree = nullptr;
			marker.current = nullptr;
		}
		void operator=(bst_iterator&& marker) {
			this->isValid = marker.isValid;
			this->tree = marker.tree;
			this->current = marker.current;

			marker.tree = nullptr;
			marker.current = nullptr;
		}
		void operator= (const bst_iterator& marker) {
			this->isValid = marker.isValid;
			this->tree = marker.tree;
			this->current = marker.current;
		}
		bool operator++() {
			return this->MoveNext();
		}

		TVal operator*() const {
			if (!isValid) {
				throw std::exception("Marker was not valid");
			}
			return current->value.second;
		}

		bool Begin() {
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

		void Delete() {
			if (!isValid) {
				return;
			}
			tree->DeleteNode(current);
			isValid = false;
		}

		bool IsValid() const {
			return isValid;
		}
	};

	size_t GetSize() const
	{
		return size;
	}

	virtual void Add(const TKey &key, const TVal &val) {
		AddNode(key, val);
	}

	virtual void Add(Node<T>* node) {
		size++;
		node->left = nullptr;
		node->parent = nullptr;
		node->right = nullptr;
		node->high = 1;
		if (head == nullptr)
		{
			head = node;
			return;
		}

		Node<T>* temp = head;
		while (temp != nullptr)
		{
			if (node->value.first > temp->value.first)
			{
				if (temp->right != nullptr)
				{
					temp = temp->right;
				}
				else
				{
					temp->right = node;
					node->parent = temp;
					RestoreHigh(temp);
					return;
				}
			}
			else
			{
				if (temp->left != nullptr)
				{
					temp = temp->left;
				}
				else
				{
					temp->left = node;
					node->parent = temp;
					RestoreHigh(temp);
					return;
				}
			}
		}
	}

	bst_iterator Find(const TKey &key)
	{
		Node<T>* node = FindNode(key);
		return bst_iterator(this, node);
	}

	bst_iterator GetMarker() {
		return bst_iterator(this);
	};

	void DeleteDict() {
		if (head == nullptr) {
			return;
		}
		Node<T>* temp = head;
		head = nullptr;
		Stack<Node<T>*> stack;
		stack.Push(temp);
		while (!stack.IsEmpty())
		{
			temp = stack.Pop();
			if (temp->left != nullptr) {
				stack.Push(temp->left);
			}
			if (temp->right != nullptr) {
				stack.Push(temp->right);
			}
			delete temp;
		}
		size = 0;
		head = nullptr;
	}
};

template <class Type> class Set
{
private:
	virtual Node<Type>* CreateNode(const Type& value) {
		return new Node<Type>(value);
	}

	Node<Type>* AddNode(const Type& value) {
		size++;
		if (head == nullptr)
		{
			head = CreateNode(value);
			head->high = 1;
			return head;
		}

		Node<Type>* node = head;
		while (node != nullptr)
		{
			if (value > node->value)
			{
				if (node->right != nullptr)
				{
					node = node->right;
				}
				else
				{
					node->right = CreateNode(value);
					node->right->parent = node;
					node->right->high = 1;
					RestoreHigh(node);
					return node->right;
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
					node->left = CreateNode(value);
					node->left->parent = node;
					node->left->high = 1;
					RestoreHigh(node);
					return node->left;
				}
			}
		}
	}

	void LL(Node<Type>* node) {
		Node<Type>* temp = node->left;
		node->left = temp->right;
		if (temp->right != nullptr) {
			temp->right->parent = node;
		}
		temp->right = node;
		if (node->parent != nullptr) {
			if (node == node->parent->right) {
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

	void RR(Node<Type>* node) {
		Node<Type>* temp = node->right;
		node->right = temp->left;
		if (temp->left != nullptr) {
			temp->left->parent = node;
		}
		temp->left = node;
		if (node->parent != nullptr) {
			if (node == node->parent->right) {
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

	void RL(Node<Type>* node) {
		node = node->right;
		LL(node);
		// ������ �����, ���� node ��� ���������� �� ���� ����
		node = node->parent->parent;
		RR(node);
	}

	void LR(Node<Type>* node) {
		node = node->left;
		RR(node);
		// ������ �����, ���� node ��� ���������� �� ���� ����
		node = node->parent->parent;
		LL(node);
	}

	void RestoreBalance(Node<Type>* node) {
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
				LL(node);
				return;
			}
			else {
				LR(node);
				return;
			}
		}
	}

	void RestoreHighOnce(Node<Type>* node) {
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

protected:
	int size;
	Node<Type>* head;

	void RestoreHigh(Node<Type>* node) {
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

	Node<Type>* FindNode(const Type& key) {
		Node<Type>* node = head;
		while (node != nullptr)
		{
			if (node->value == key) {
				return node;
			}
			if (key > node->value)
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

	void DeleteNode(Node<Type>* node) {
		--size;
		if ((node->right == nullptr) && (node->left == nullptr)) {
			if (node->parent != nullptr) {
				if (node->value > node->parent->value) {
					node = node->parent;
					delete node->right;
					node->right = nullptr;
				}
				else {
					node = node->parent;
					delete node->left;
					node->left = nullptr;
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

			inRight = (node->right->high >= node->left->high);
		}
		else {

			inRight = (node->right != nullptr);
		}
		//
		Node<Type>* temp = node->right;
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
					if (node->value > node->parent->value) {
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
			temp->parent->left = temp->right;
			if (temp->right != nullptr) {
				temp->right->parent = temp->parent;
			}
			Node<Type>* tempParent = temp->parent;
			//
			temp->parent = node->parent;
			if (node->parent != nullptr) {
				if (node->value > node->parent->value) {
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
			temp->right = node->right;
			node->right->parent = temp;
			// ��� ��� �������������� ������ ���������� � ����������������,
			// �� �� ������ ���� �� ������ � ���������

			delete node;
			RestoreHigh(tempParent);
			return;
		}
		else {
			temp = node->left;
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
					if (node->value > node->parent->value) {
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
			temp->parent->right = temp->left;
			if (temp->left != nullptr) {
				temp->left->parent = temp->parent;
			}
			Node<Type>* tempParent = temp->parent;
			//
			temp->parent = node->parent;
			if (node->parent != nullptr) {
				if (node->value > node->parent->value) {
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
			temp->left = node->left;
			node->left->parent = temp;

			delete node;
			RestoreHigh(tempParent);
			return;
		}
	}

public:
	Set()
	{
		head = nullptr;
		size = 0;
	}

	Set(const Set& tree) {
		this->head = tree.head;
		this->size = tree.size;
	}

	Set(Set&& tree) {
		this->head = tree.head;
		this->size = tree.size;

		tree.head = nullptr;
		tree.size = 0;
	}

	void operator=(const Set& tree) {
		this->head = tree.head;
		this->size = tree.size;
	}

	void operator=(Set&& tree) {
		this->head = tree.head;
		this->size = tree.size;

		tree.head = nullptr;
		tree.size = 0;
	}

	~Set() {
		DeleteSet();
	}

	class bst_iterator {
	protected:
		Node<Type>* current;

		Set<Type>* tree;
		bool isValid;

		bool MoveNext() {
			if (!isValid) {
				return false;
			}
			if (current == nullptr) {
				isValid = false;
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
				Node<Type>* temp = current;
				current = current->parent;
				while ((current != nullptr) && (current->right == temp))
				{
					temp = current;
					current = current->parent;
				}
				if (current == nullptr) {
					current = tree->head;
					isValid = false;
					return false;
				}
				else {
					return true;
				}
			}
			isValid = false;
			return false;
		}


	public:
		bst_iterator() { }
		bst_iterator(Set<Type>* _tree) : tree(_tree) {
			if (tree == nullptr || tree->head == nullptr) {
				isValid = false;
				return;
			}
			isValid = true;
			Begin();
		}
		bst_iterator(Set<Type>* _tree, Node<Type>* node) : tree(_tree) {
			if (tree == nullptr || tree->head == nullptr || node == nullptr) {
				isValid = false;
				return;
			}
			isValid = true;
			current = node;
		}
		bst_iterator(bst_iterator&& marker) {
			this->isValid = marker.isValid;
			this->tree = marker.tree;
			this->current = marker.current;

			marker.tree = nullptr;
			marker.current = nullptr;
		}
		void operator=(bst_iterator&& marker) {
			this->isValid = marker.isValid;
			this->tree = marker.tree;
			this->current = marker.current;

			marker.tree = nullptr;
			marker.current = nullptr;
		}
		void operator= (const bst_iterator& marker) {
			this->isValid = marker.isValid;
			this->tree = marker.tree;
			this->current = marker.current;
		}
		bool operator++() {
			return this->MoveNext();
		}

		Type operator*() const {
			if (!isValid) {
				throw std::exception("Marker was not valid");
			}
			return current->value;
		}

		bool Begin() {
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

		void Delete() {
			if (!isValid) {
				return;
			}
			tree->DeleteNode(current);
			isValid = false;
		}

		bool IsValid() const {
			return isValid;
		}
	};

	size_t GetSize() const
	{
		return size;
	}

	virtual void Add(const Type& value) {
		AddNode(value);
	}

	virtual void Add(Node<Type>* node) {
		size++;
		node->left = nullptr;
		node->parent = nullptr;
		node->right = nullptr;
		node->high = 1;
		if (head == nullptr)
		{
			head = node;
			return;
		}

		Node<Type>* temp = head;
		while (temp != nullptr)
		{
			if (node->value > temp->value)
			{
				if (temp->right != nullptr)
				{
					temp = temp->right;
				}
				else
				{
					temp->right = node;
					node->parent = temp;
					RestoreHigh(temp);
					return;
				}
			}
			else
			{
				if (temp->left != nullptr)
				{
					temp = temp->left;
				}
				else
				{
					temp->left = node;
					node->parent = temp;
					RestoreHigh(temp);
					return;
				}
			}
		}
	}

	bst_iterator Find(const Type &key)
	{
		Node<Type>* node = FindNode(key);
		return bst_iterator(this, node);
	}

	bst_iterator GetMarker() {
		return bst_iterator(this);
	};

	void DeleteSet() {
		if (head == nullptr) {
			return;
		}
		Node<Type>* temp = head;
		head = nullptr;
		Stack<Node<Type>*> stack;
		stack.Push(temp);
		while (!stack.IsEmpty())
		{
			temp = stack.Pop();
			if (temp->left != nullptr) {
				stack.Push(temp->left);
			}
			if (temp->right != nullptr) {
				stack.Push(temp->right);
			}
			delete temp;
		}
		size = 0;
		head = nullptr;
	}
};


#endif