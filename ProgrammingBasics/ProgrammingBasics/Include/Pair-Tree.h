#ifndef __PAIRTREE
#define __PAIRTREE

#include "Dictionary.h"

template <class TKey, class TValFirst, class TValSecond> class PairNode :
	public Node<TKey, TValFirst> {
public:
	PairNode(const TKey& _key, const TValFirst& _val) : Node<TKey, TValFirst>(_key, _val) {

	}
	~PairNode() {
		delete list;
	}
	List<PairNode<TKey, TValSecond, TValFirst >*>* list;
	bool flag;
};


template <class TKey, class TValFirst, class TValSecond> class PairTree :
	public BinSearchTree<TKey, TValFirst>
{
public:
	~PairTree() {}

	class PairMarker :
		public BinSearchTree<TKey, TValFirst>::Marker
	{
	public:

		PairMarker(BinSearchTree<TKey, TValFirst>* _tree) :
			BinSearchTree<TKey, TValFirst>::Marker(_tree) {}
		PairMarker(BinSearchTree<TKey, TValFirst>* _tree, Node<TKey, TValFirst>* _node) :
			BinSearchTree<TKey, TValFirst>::Marker(_tree, _node) { }
		PairMarker(PairMarker&& marker) : BinSearchTree<TKey, TValFirst>::Marker(marker.tree, marker.current) {
			marker.tree = nullptr;
			marker.current = nullptr;
		}
		PairMarker(const PairMarker& marker) : BinSearchTree<TKey, TValFirst>::Marker(marker.tree, marker.current) {
			
		}
		PairMarker() { }

		void operator=(const PairMarker& marker) {
			this->current = marker->current;
			this->tree = marker->tree;
		}
		void operator=(PairMarker&& marker) {
			this->current = marker->current;
			this->tree = marker->tree;

			marker->current = nullptr;
			marker->tree = nullptr;
		}
		~PairMarker() {}

		List<PairNode<TKey, TValSecond, TValFirst >*>* GetList() {
			if (!this->isValid) {
				throw std::exception("Marker was not valid");
			}
			PairNode<TKey, TValFirst, TValSecond>* node = dynamic_cast<PairNode<TKey, TValFirst, TValSecond>*>(this->current);
			return node->list;
		}

		const TKey& GetKey() {
			if (!this->isValid) {
				throw std::exception("Marker was not valid");
			}
			return this->current->key;
		}

		void MakeFlag() {
			if (! this->isValid) {
				throw std::exception("Marker was not valid");
			}
			PairNode<TKey, TValFirst, TValSecond>* node = dynamic_cast<PairNode<TKey, TValFirst, TValSecond>*>(this->current);
			node->flag = true;
		}
	};

	PairMarker FindPair(const TKey& key) {
		auto node = GetNode(key);
		return PairMarker(this, node);
	}

	PairMarker GetPairMarker() {
		return PairMarker(this);
	}

	void Merge(PairTree<TKey, TValFirst, TValSecond>* tree) {
		if (tree->GetSize() == 0) {
			return;
		}
		Deck<Node<TKey, TValFirst>*> deck;
		Node<TKey, TValFirst>* temp = tree->head;
		deck.PushBack(temp);
		while (!deck.IsEmpty()) {
			temp = deck.PopBack();
			if (temp->left != nullptr) {
				deck.PushBack(temp->left);
			}
			if (temp->right != nullptr) {
				deck.PushBack(temp->right);
			}
			this->Add(temp);
		}
		tree->head = nullptr;
		tree->size = 0;
	}

	PairNode<TKey, TValFirst, TValSecond>* GetNode(const TKey& key) {
		Node<TKey, TValFirst>* node = this->FindNode(key);
		PairNode<TKey, TValFirst, TValSecond>* pairNode = dynamic_cast<PairNode<TKey, TValFirst, TValSecond>*>(node);
		return pairNode;
	}

	PairNode<TKey, TValFirst, TValSecond>* GetNode() {
		Node<TKey, TValFirst>* node = this->head;
		if (node == nullptr) {
			return nullptr;
		}
		//while (node->left != nullptr) {
		//	node = node->left;
		//}
		PairNode<TKey, TValFirst, TValSecond>* pairNode = dynamic_cast<PairNode<TKey, TValFirst, TValSecond>*>(node);
		return pairNode;
	}



	void Delete(Node<TKey, TValFirst>* node) {
		this->DeleteNode(node);
	}

	void ThrowOutNode(Node<TKey, TValFirst>* node) {
		--this->size;
		if ((node->right == nullptr) && (node->left == nullptr)) {
			if (node->parent != nullptr) {
				if (node->key > node->parent->key) {
					node = node->parent;
					node->right = nullptr;
				}
				else {
					node = node->parent;
					node->left = nullptr;
				}
				this->RestoreHigh(node);
			}
			else
			{
				this->head = nullptr;
			}
			return;
		}
		// определение из какого лучше удалять
		bool inRight;
		if ((node->right != nullptr) && (node->left != nullptr)) {

			inRight = (node->right->high >= node->left->high);
		}
		else {

			inRight = (node->right != nullptr);
		}
		//
		Node<TKey, TValFirst>* temp = node->right;
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
				// проверка, если у большего сына удаляемого елемента нет меньших сыновей	
				temp->parent = node->parent;
				if (node->parent != nullptr) {
					if (node->key > node->parent->key) {
						node->parent->right = temp;
					}
					else {
						node->parent->left = temp;
					}

				}
				else
				{
					this->head = temp;
				}
				//
				this->RestoreHigh(temp);
				return;
			}
			//
			temp->parent->left = temp->right;
			if (temp->right != nullptr) {
				temp->right->parent = temp->parent;
			}
			Node<TKey, TValFirst>* tempParent = temp->parent;
			//
			temp->parent = node->parent;
			if (node->parent != nullptr) {
				if (node->key > node->parent->key) {
					node->parent->right = temp;
				}
				else {
					node->parent->left = temp;
				}

			}
			else
			{
				this->head = temp;
			}
			//
			temp->right = node->right;
			node->right->parent = temp;
			// так как восстановление высоты происходит с вспомогательного,
			// то он должен быть на уровне с удаляемым

			this->RestoreHigh(tempParent);
			
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
				// проверка, если у большего сына удаляемого елемента нет меньших сыновей	
				temp->parent = node->parent;
				if (node->parent != nullptr) {
					if (node->key > node->parent->key) {
						node->parent->right = temp;
					}
					else {
						node->parent->left = temp;
					}

				}
				else
				{
					this->head = temp;
				}
				//
				this->RestoreHigh(temp);
				return;
			}
			//
			temp->parent->right = temp->left;
			if (temp->left != nullptr) {
				temp->left->parent = temp->parent;
			}
			Node<TKey, TValFirst>* tempParent = temp->parent;
			//
			temp->parent = node->parent;
			if (node->parent != nullptr) {
				if (node->key > node->parent->key) {
					node->parent->right = temp;
				}
				else {
					node->parent->left = temp;
				}

			}
			else
			{
				this->head = temp;
			}
			//
			temp->left = node->left;
			node->left->parent = temp;
			// так как восстановление высоты происходит с вспомогательного,
			// то он должен быть на уровне с удаляемым

			this->RestoreHigh(tempParent);
			return;
		}
	}
};

#endif // !__PAIRTREE