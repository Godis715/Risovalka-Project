#pragma once
#include "Primitives.h"

#define TABLE_I ((ListE<Pair<Tkey, Tval>>*)table[i])
#define TABLE_INDEX ((ListE<Pair<Tkey, Tval>>*)table[index])
// JUST FOOOOOR FUUUUUUUN

class Hash {
public:
	unsigned long long operator()(ID& key) {
		return key.GetHash();
	}
	unsigned long long operator()(int& key) {
		return key;
	}
};

template <class Tkey, class Tval, class Hash> class HashTable
{
private:
	template <class Tkey, class Tval> class Pair
	{
	public:
		//Pair() { }
		Pair(Tkey& _key, Tval& _value) {
			key = _key;
			value = _value;
		}
		Pair(Pair& _pair) {
			key = _pair.key;
			value = _pair.value;
		}
		Tkey key;
		Tval value;
	};

	Array<ListE<Pair<Tkey, Tval>>> table;
	Hash hash;
	int hashSize = 0;
	int countElements = 0;

	void PushToColumn(int index, Pair<Tkey, Tval>& pair) {
		++countElements;
		if (table[index].GetSize() == 0) {
			table[index].PushHead(pair);
			return;
		}
		table[index].MoveTail();
		do
		{
			if (pair.key > table[index].GetCurrent().key) {
				table[index].PushAfterCurrent(pair);
				return;
			}
		} while (table[index].MovePrev());
		table[index].PushHead(pair);
	}

	void ChangeHashTable() {
		int prevSize = hashSize;
		hashSize *= 2;
		Array<ListE<Pair<Tkey, Tval>>> temp = table;
		table = Array<ListE<Pair<Tkey, Tval>>>(hashSize);
		//for (int i = 0; i < hashSize; ++i) {
		//	table[i] = new ListE<Pair<Tkey, Tval>*>;
		//}
		for (int i = 0; i < prevSize; ++i) {
			if (temp[i].GetSize() != 0) {
				do
				{
					Tval value = temp[i].GetCurrent().value;
					Tkey key = temp[i].GetCurrent().key;
					Input(key, value);
				} while (temp[i].MovePrev() != 0);
				temp[i].DeleteList();
			}
		}
		return;
	}
public:
	HashTable(int size) : table(size) {
		hashSize = size;
	}
	//~HashTable() {
	//	for (int i = 0; i < hashSize; ++i) {
	//		table[i]->DeleteList();
	//	}
	//}

	void Input(Tkey key, Tval value) {
		Pair<Tkey, Tval> pair(key, value);
		int index = hash(key) % hashSize;
		PushToColumn(index, pair);
		if (hashSize <= countElements) {
			ChangeHashTable();
		}
	}

	bool Searching(Tkey key, Tval& value) {
		int index = hash(key) % hashSize;
		if (table[index].GetSize() == 0) {
			return false;
		}
		table[index].MoveHead();
		do
		{
			if (key == table[index].GetCurrent().key) {
				value = table[index].GetCurrent().value;
				return true;
			}
			if (key < table[index].GetCurrent().key) {
				return false;
			}
		} while (table[index].MoveNext());
		return false;
	}

	void DeleteElement(Tkey key) {
		int index = hash(key) % hashSize;
		if (table[index].GetSize() == 0) {
			return;
		}
		table[index].MoveHead();
		do
		{
			if (key == table[index].GetCurrent().key) {
				table[index].DeleteCurrent();
				return;
			}
			if (key < table[index].GetCurrent().key) {
				return;
			}
		} while (table[index].MoveNext());
	}
};