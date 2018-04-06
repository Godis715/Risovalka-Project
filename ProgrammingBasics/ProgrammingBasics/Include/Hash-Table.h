#pragma once
#include "Primitives.h"

// � ������� �������� ������������� ������
#define TABLE_I ((ListE<Pair<Tkey, Tval>>*)table[i])
#define TABLE_INDEX ((ListE<Pair<Tkey, Tval>>*)table[index])
// JUST FOOOOOR FUUUUUUUN

template <class Tkey, class Tval> class HashTable
{
private:
	template <class Tkey, class Tval> class Pair
	{
	public:
		Pair() {}
		~Pair() {}
		Tkey key;
		Tval Tval;
	};

	// ������ ���������� �� ������
	ListE<Pair<Tkey, Tval>*>** table;
	int hashSize = 0;
	int countElements = 0;

	// ������ ������ ����� � ������������ ������ �������
	void PushToColumn(int index, Pair<Tkey, Tval>* pair) {
		++countElements;
		if (table[index]->GetSize() == 0) {
			table[index]->PushHead(pair);
			return;
		}
		table[index]->MoveTail();
		do
		{
			if (pair.key > table[index]->GetCurrent().key) {
				table[index]->PushAfterCurrent(pair);
				return;
			}
		} while (table[index]->MoveTail());
		table[index]->PushHead(pair);
	}

	int HashFunction_1(Tkey key) {
		return key % hashSize;
	}

	int HashFunction_2(Pair pair) {
		return pair.key % size;
	}

	int HashFunction_3(Pair pair) {
		return pair.key % size;
	}

	void ChangeHashTable() {
		int prevSize = hashSize;
		hashSize *= 2;
		ListE<Pair<Tkey, Tval>*>** temp = table;
		table = new ListE<Pair<Tkey, Tval>*>*[hashSize];
		for (int i = 0; i < hashSize; ++i) {
			table[i] = new ListE<Pair<Tkey, Tval>*>;
		}
		for (int i = 0; i < prevSize; ++i) {
			if (temp[i]->GetSize() != 0) {
				do
				{
					Tval value = temp[i]->GetCurrent()->value;
					Tkey key = temp[i]->GetCurrent()->key;
					Input(key, value);
				} while (temp[i]->MovePrev() != 0);
				temp[i]->DeleteList();
			}
		}
		return;
	}
public:
	HashTable(int size) {
		hashSize = size;
		Tkey* temp = new Tkey;
		int t = *temp % 5;
		table = new ListE<Pair<Tkey, Tval>*>*[hashSize];
		for (int i = 0; i < hashSize; ++i) {
			table[i] = new ListE<Pair<Tkey, Tval>*>;
		}

	}
	~HashTable() {
		for (int i = 0; i < hashSize; ++i) {
			table[i]->DeleteList();
		}
	}

	void Input(Tkey key, Tval value) {
		Pair<Tkey, Tval>* pair = new Pair<Tkey, Tval>(key, value);
		int index = HashFunction_1(key);
		PushToColumn(index, pair);
		if (hashSize <= countElements * 2) {
			ChangeHashTable();
		}
	}

	bool Searching(Tkey key, Tval& value) {
		int index = HashFunction_1(key);
		if (table[index]->GetSize() == 0) {
			return false;
		}
		table->MoveHead();
		do
		{
			if (key == table[index]->GetCurrent().key) {
				value = table[index]->GetCurrent().value;
				return true;
			}
			if (key < table[index]->GetCurrent().key) {
				return false;
			}
		} while (table[index]->MoveNext());
		return false;
	}

	void DeleteElement(Tkey key) {
		int index = HashFunction_1(key);
		if (table[index]->GetSize() == 0) {
			return;
		}
		table[index]->MoveHead();
		do
		{
			if (key == table[index]->GetCurrent().key) {
				table[index]->DeleteCurrent();
				return;
			}
			if (key < table[index]->GetCurrent().key) {
				return;
			}
		} while (table[index]->MoveNext());
	}
};