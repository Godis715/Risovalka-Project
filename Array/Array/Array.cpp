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

	void FillDefault(size_t l, size_t r)
	{
		for (size_t i = l; i <= r; i++)
		{
			_storage[i] = 0;
		}
	}

	void createPyramid(int cur, int end)
	{
		int childe;
		while (cur <= end / 2)
		{
			if (cur * 2 + 1 <= end)
			{
				if (cur * 2 + 2 <= end && _storage[cur * 2 + 2] > _storage[cur * 2 + 1])
				{
					childe = cur * 2 + 2;
				}
				else
				{
					childe = cur * 2 + 1;
				}
				if (_storage[cur] < _storage[childe])
				{
					swap(cur, childe);
					cur = childe;
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
		}
	}
	
	void phaseOne(int l, int r)
	{
		for (int i = (l + r) / 2; i >= l; i--)
		{
			createPyramid(i, r);
		}
	}
	
	void phaseTwo(int l, int r)
	{
		int end = r;
		while (end != l)
		{
			swap(l, end);
			end--;
			createPyramid(0, end);
		}
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
		FillDefault(0, _size - 1);
	}

	~Array()
	{
		delete[] _storage;
	}

	T& operator[](int index)
	{
		if (index < 0 || index >= _size)
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

	bool isEmpty()
	{
		return (_size > 0) ? false : true;
	}

	void resize(int newSize)
	{
		if (newSize < 0)
		{
			std::cout << "Negative size! Size token by abs. value\n";
			newSize = abs(newSize);
		}
		if (newSize > _capacity)
		{
			_capacity = 2 * newSize;
		}
		auto newStorage = new T[_capacity];
		for (size_t i = 0; i < newSize && i < _size; i++)
		{
			newStorage[i] = _storage[i];
		}
		delete[] _storage;
		_storage = newStorage;
		if (newSize > _size)
		{
			FillDefault(_size, newSize - 1);
		}
		_size = newSize;
	}

	void clear()
	{
		_capacity = 512;
		resize(0);
	}

	int find(T value)
	{
		int index = -1;
		for (size_t i = 0; i < _size; i++)
		{
			if (_storage[i] = value)
			{
				index = i;
				break;
			}
		}
		return index;
	}

	void swap(int index1, int index2)
	{
		if (index1 < 0 || index2 < 0)
		{
			std::cout << "Negative index! Index token by abs. value\n";
			index1 = abs(index1);
			index2 = abs(index2);
		}
		T temp = _storage[index1];
		_storage[index1] = _storage[index2];
		_storage[index2] = temp;
	}

	//TODO: Normal sort
	/*void sort(int l, int r)
	{
		if (l < 0 || r < 0 || l > r || l >= _size || r >= _size)
		{
			std::cout << "Negative index! OR Index out of range\n";
			throw std::invalid_argument("Negative index! OR Index out of range\n");
		}
		for (int i = l; i <= r; i++)
		{
			for (int j = i+1; j <= r; j++)
			{
				if (arr[j] < arr[j - 1])
				{
					swap(j, j - 1);
				}
			}
		}
	}*/

	void sort(int l, int r)
	{
		if (l < 0 || r < 0 || l > r || l >= _size || r >= _size)
		{
			std::cout << "Negative index! OR Index out of range\n";
			throw std::invalid_argument("Negative index! OR Index out of range\n");
		}
		phaseOne(l, r);
		phaseTwo(l, r);
	}
};

int main()
{
	int size = 20;
	Array<int> arr(size);
	for (size_t i = 0; i < size; i++)
	{
		arr[i] = rand() % 100;
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
	arr.sort(0, size - 1);
	for (size_t i = 0; i < size; i++)
	{
		std::cout << arr[i] << " ";
	}
	//arr.pushBack(1);
	//arr.pushBack(2);
	//arr.pushBack(3);
	//std::cout << arr.popBack() << "\n";
	//std::cout << arr.popBack() << "\n";
	//std::cout << arr.popBack() << "\n";
	//std::cout << "Size = " << arr.getSize() << "\n";
	
	system("pause");
	return 0;
}