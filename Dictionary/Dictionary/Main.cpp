#include <iostream>

using namespace std;

template <class T1, class T2> class Pair
{
	T1 first;
	T2 second;
};

template <class T1, class T2> class Dict
{
private:
	int _size = 0;

	class Node
	{

	};

public:
	Dict()
	{

	}
	int getsize()
	{
		return _size;
	}
	void add(const T1 &key, const T2 &val)
	{

	}
	void erase(const T1 &key)
	{

	}
	bool find(T1 key, T2 &val)
	{

	}
	bool contains(T1 key)
	{

	}
};

int main()
{

}