#ifndef __DICT
#define __DICT

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
	// вопрос, почему оба варианта работают?
	Node* support;
	Node* temp; 
	// и здесь тоже?
	// Node<TKey, TVal>* find(TKey key)
	// и вообще она уже не нужна, но я ее оставлю для вопроса
	Node* find(TKey key)
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

	void LL() {
		temp = support->leftChild;
		support->leftChild = temp->rightChild;
		if (temp->rightChild != nullptr) {
			temp->rightChild->parent = support;
		}
		temp->rightChild = support;
		if (support->parent != nullptr) {
			if (support->key <= support->parent->key) {
				
				support->parent->leftChild = temp;
			}
			else {
				support->parent->rightChild = temp;

			}
			temp->parent = support->parent;
		}
		else {
			temp->parent = nullptr;
			head = temp;
		}
		support->parent = temp;
		return;
	}

	void RR() {
		temp = support->rightChild;
		support->rightChild = temp->leftChild;
		if (temp->leftChild != nullptr) {
			temp->leftChild->parent = support;
		}
		temp->leftChild = support;
		if (support->parent != nullptr) {
			if (support->key <= support->parent->key) {

				support->parent->leftChild = temp;
			}
			else {
				support->parent->rightChild = temp;

			}
			temp->parent = support->parent;
		}
		else {
			temp->parent = nullptr;
			head = temp;
		}
		support->parent = temp;
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
				lehtHigh = support->leftChild->leftChild->high;
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
				if (support->value <= support->value->value) {
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
			
			support = head;
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
					temp->rightChild->Father = support;
				}
				support->value = temp->value;
				support->key = temp->key
				delete temp;
				RestoreHigh();
				return;
			}
			temp->parent->leftChild = Temp->rightChild;
			if (temp->rightChild != nullptr) {
				temp->rightChild->Father = temp->Father;
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

	int getsize()
	{
		return size;
	}

	void Add(const TKey &key, const TVal &val)
	{
		size++;
		if (head == nullptr)
		{
			head = new Node;
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
					support->rightChild = new Node();
					support->rightChild->key = key;
					support->rightChild->value = val;
					support->rightChild->parent = support;
					support->rightChild->high = 1;
					RestoreHighUp();
					return;
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
					support->leftChild = new Node();
					support->leftChild->key = key;
					support->leftChild->value = val;
					support->leftChild->parent = support;
					RestoreHighUp();
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
				if (temp->leftChild != nullptr)
				{
					temp = temp->leftChild;
				}
				else
				{
					return;
				}
			}
		}
	}

	bool find(const TKey &key)
	{
		support = head;
		while (support != nullptr)
		{
			if (support->key == key) {
				current = support;
				return true;
			}
			if (support->key < key)
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
		current = Head;
	}

	bool MoveParent() {
		if (current == nullptr) {
			return false;
		}
		if (current->parent = nullptr) {
			return false;
		}
		current = current->parent;
		return true;
	}

	bool MoveLeft() {
		if (current == nullptr) {
			return false;
		}
		if (current->leftChild = nullptr) {
			return false;
		}
		current = current->leftChild;
		return true;
	}

	bool MoveRight() {
		if (current == nullptr) {
			return false;
		}
		if (current->rightChild = nullptr) {
			return false;
		}
		current = current->rightChild;
		return true;
	}

	bool IsCurrent() {
		if (current == nullptr) {
			return false;
		}
		else {
			return true;
		}
	}

	TVal* GetCurrent() {
		if (current == nullptr) {
			throw std::exception("use is current, it was nullptr");
		}
		else {
			return current->value;
		}
	}

	TKey GetCurrntKey() {
		if (current == nullptr) {
			throw std::exception("use is current, it was nullptr");
		}
		else {
			return current->key;
		}
	}
};

#endif