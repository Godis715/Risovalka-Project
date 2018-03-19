#pragma once

template<class T> class Result {
private:
	const T value;
	const bool result;
public:
	Result(bool, T);
	T GetValue() const;
	bool GetResult() const;
};

template<class T> Result<T>::Result(bool _result, T _value) : value(_value), result(_result) { }

class Empty {
public:
	Empty();
};