#include <iostream>
#include <stdexcept>

template <class T> class Array
{
private:
	T* _storage = nullptr;
	int _size = 0;
	int _capacity = 512;

	void doubleCapacity()
	{
		auto newStorage = new T[2 * _capacity];
		for (size_t i = 0; i < _capacity; i++)
		{
			newStorage[i] = _storage[i];
		}
		delete[] _storage;
		_storage = newStorage;
		_capacity *= 2;
	}

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

	~Array()
	{
		delete[] _storage;
	}

	T& operator[](int index)
	{
		if (index < 0 || index >= size)
		{
			throw std::out_of_range("Index out of range!");
		}
		return _storage[index];
	}

	void pushBack(T value)
	{
		if (_size + 1 > _capacity)
		{
			doubleCapacity();
		}
		_storage[_size++] = value;
	}

	T popBack()
	{
		if (_size == 0)
		{
			throw std::out_of_range("Array is empty");
		}
		_size--;
		return _storage[_size];
	}
};

int main()
{
	Array<int> arr;
	arr.pushBack(1);
	arr.pushBack(2);
	arr.pushBack(3);
	std::cout << arr.popBack() << "\n";
	std::cout << arr.popBack() << "\n";
	std::cout << arr.popBack() << "\n";
	std::cout << "Size = " << arr.getSize() << "\n";
	system("pause");
	return 0;
}