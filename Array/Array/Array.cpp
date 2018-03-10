#include <iostream>
#include <stdexcept>

template <class T> class Array
{
private:
	T* _storage = nullptr;
	int _size = 0;
	int _capacity = 512;
public:

	int getSize() const
	{
		return _size;
	}

	Array()
	{
		_capacity = 512;
		_size = 0;
		_storage = new T[_capacity];
	}

	Array(int size)
	{
		if (size < 0)
		{
			std::cout << "Bad array size. Size set by abs. value\n";
			size = abs(size);
		}
		if (size > _capacity)
		{
			_capacity = 2 * size;
		}
		_size = size;
		_storage = new T[_capacity];
		for (size_t i = 0; i < _size; i++)
		{
			_storage[i] = 0;
		}
	}

	T& operator[](int index)
	{
		return _storage[index];
	}
};

int main()
{
	Array<int> arr(513);
	arr[1] = 9;
	std::cout << arr[1] << "\n";
	system("pause");
	return 0;
}