#pragma once

template <typename TKey, typename TValue> class Set {
private:
public:
	Set();
	bool Push(TKey, TValue);
	bool GetByKey(TKey, TValue&);
	TValue GetElement();
};