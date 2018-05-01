#ifndef __ARRAY
#define __ARRAY

#include <stdexcept>

template <class T> class Array
{
private:
	T* _storage = nullptr;
	int _size = 0;
	int _capacity;
	const int _default_capacity;

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

	//Sort methods begin
	// look after
	/*void createPyramid(int cur, int end, int delta)
	{
		int child;
		while ((cur - delta) <= (end - delta) / 2)
		{
			if ((cur - delta) * 2 + 1 <= (end - delta))
			{
				if ((cur - delta) * 2 + 2 <= (end - delta) && _storage[(cur - delta) * 2 + 2 + delta] > _storage[(cur - delta) * 2 + 1 + delta])
				{
					child = (cur - delta) * 2 + 2 + delta;
				}
				else
				{
					child = (cur - delta) * 2 + 1 + delta;
				}
				if (_storage[cur] < _storage[child])
				{
					swap(cur, child);
					cur = child;
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

	void phaseOne(int l, int r, int delta)
	{
		for (int i = (l + r) / 2; i >= l; i--)
		{
			createPyramid(i, r, delta);
		}
	}

	void phaseTwo(int l, int r, int delta)
	{
		int end = r;
		while (end != l)
		{
			swap(l, end);
			end--;
			createPyramid(l, end, delta);
		}
	}*/

	//Sort methods end

public:

	class ReadMarker {
	private:
		size_t index;
		Array<T>* arr;
	public:

		ReadMarker(Array<T>* _arr, size_t _index) {
			arr = _arr;
			if (index > arr->_size) {
				index = arr->_size;
			}
			else {
				index = _index;
			}
		}

		ReadMarker(const ReadMarker& marker) {
			this->arr = marker->arr;
			this->index = marker->index;
		}

		ReadMarker(ReadMarker&& marker) {
			this->arr = marker->arr;
			this->index = marker->index;

			marker->arr = nullptr;
		}

		T GetValue() const {
			return arr->_storage[index];
		}

		void operator ++() {
			index++;
		}

		bool operator != (const ReadMarker& marker) {
			if (this->arr != marker->arr) {
				throw std::exception("Trying to compare non-native markers");
			}

			return (this->index != marker->index);
		}

	};

	Array() : _default_capacity(64)
	{
		_capacity = _default_capacity;
		_size = 0;
		_storage = new T[_capacity];
	}

	Array(int size) : _default_capacity(size)
	{
		if (size <= 0)
		{
			throw std::invalid_argument("Bad array size!");
		}
		_capacity = size;
		_size = size;
		_storage = new T[_capacity];
	}

	Array(int size, const T& default_value) : _default_capacity(size)
	{
		if (size <= 0)
		{
			throw std::invalid_argument("Bad array size!");
		}
		_capacity = size;
		_size = size;
		_storage = new T[_capacity];
		FillDefault(default_value);
	}

	Array(Array&& arr) : _default_capacity(arr._default_capacity) {
		this->_capacity = arr._capacity;
		this->_size = arr._size;
		this->_storage = arr._storage;
		arr._storage = nullptr;
	}

	Array(const Array& arr) : _default_capacity(arr._default_capacity) {
		this->_capacity = arr._capacity;
		this->_size = arr._size;
		this->_storage = new T[_capacity];
		for (int i = 0; i < _size; ++i) {
			this->_storage[i] = arr._storage[i];
		}
	}

	~Array()
	{
		delete[] _storage;
	}
	
	void operator=(Array&& arr) {
		this->_capacity = arr._capacity;
		this->_size = arr._size;
		this->_storage = arr._storage;
		arr._storage = nullptr;
	}

	void operator=(const Array& arr) {
		this->_capacity = arr._capacity;
		this->_size = arr._size;
		this->_storage = new T[_capacity];
		for (int i = 0; i < _size; ++i) {
			this->_storage[i] = arr._storage[i];
		}
	}

	int GetSize() const
	{
		return _size;
	}

	void FillDefault(const T& default_value) {
		for (int i = 0; i < _size; ++i) {
			_storage[i] = default_value;
		}
	}

	T& operator[](int index)
	{
		if (index < 0 || index >= _size)
		{
			throw std::out_of_range("Index out of range!");
		}
		return _storage[index];
	}

	const T& operator[](int index) const
	{
		if (index < 0 || index >= _size)
		{
			throw std::out_of_range("Index out of range!");
		}
		return _storage[index];
	}

	void PushBack(const T& value)
	{
		if (_size + 1 > _capacity)
		{
			doubleCapacity();
		}
		_storage[_size++] = value;
	}

	T PopBack()
	{
		if (_size == 0)
		{
			throw std::out_of_range("Array is empty");
		}
		_size--;
		return _storage[_size];
	}

	bool IsEmpty() const
	{
		return (_size > 0) ? false : true;
	}

	void Resize(int newSize)
	{
		if (newSize < 0)
		{
			throw std::invalid_argument("Negative size!");
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
		_size = newSize;
	}

	void Clear()
	{
		_capacity = _default_capacity;
		Resize(0);
	}

	void Swap(int index1, int index2)
	{
		if (index1 > _size - 1 || index2 > _size - 1)
		{
			throw std::out_of_range("Index out of range!");
		}
		if (index1 < 0 || index2 < 0)
		{
			throw std::invalid_argument("Negative index!");
		}
		T temp = _storage[index1];
		_storage[index1] = _storage[index2];
		_storage[index2] = temp;
	}

	/*void sort(int l, int r)
	{
		if (l < 0 || r < 0 || l > r || l >= _size || r >= _size)
		{
			throw std::invalid_argument("Negative index! OR Index out of range\n");
		}
		int delta = l;
		phaseOne(l, r, delta);
		phaseTwo(l, r, delta);
	} */

	/*void Reverse(int l, int r)
	{
		if (l < 0 || r < 0 || l > r || l >= _size || r >= _size)
		{
			throw std::invalid_argument("Negative index! OR Index out of range\n");
		}
		for (int i = 0; i < (r - l + 1) / 2; i++)
		{
			Swap(l + i, r - i);
		}
	}*/

	void Insert(int index, const T& value) {
		if (index >= _size) {
			throw std::out_of_range("Index out of range!");
		}
		if (index < 0) {
			throw std::invalid_argument("Negative index!");
		}
		PushBack(value);
		for (int i = _size - 2; i >= index; --i) {
			T temp = _storage[i];
			_storage[i] = _storage[i + 1];
			_storage[i + 1] = temp;
		}
	}

	void Erase(int index) {
		if (index >= _size) {
			throw std::out_of_range("Index out of range!");
		}
		if (index < 0) {
			throw std::invalid_argument("Negative index!");
		}
		for (int i = index; i < _size - 1; i++) {
			T Temp = _storage[i];
			_storage[i] = _storage[i + 1];
			_storage[i + 1] = Temp;
		}
		PopBack();
	}

	/*int BinSearch(int l, int r, T value)
	{
		if (l < 0 || r < 0 || l > r || l >= _size || r >= _size)
		{
			throw std::invalid_argument("Negative index! OR Index out of range\n");
		}
		if (value < _storage[l])
		{
			return l - 1;
		}
		if (value > _storage[r])
		{
			return r;
		}
		int index;
		while (true)
		{
			int center = (l + r) / 2;
			if (_storage[center] == value)
			{
				index = center;
				break;
			}
			if (r - l <= 1)
			{
				if (_storage[l] == value)
				{
					index = l;
					break;
				}
				if (_storage[r] == value)
				{
					index = r;
					break;
				}
				index = l;
				break;
			}
			if (value < _storage[center])
			{
				r = center;
			}
			else
			{
				l = center;
			}
		}
		return index;
	} */

	bool find(T& value, bool(*cmp)())
	{
		for (size_t i = 0; i < _size; i++)
		{
			if (value = _storage[i])
			{
				return true;
			}
		}
		return false;
	}

	ReadMarker Begin() {
		return ReadMarker(this, 0);
	}

	ReadMarker End() {
		return ReadMarker(this, _size);
	}

}; 

//template <class T> std::ostream& operator<< (std::ostream& out, Array<T>& arr)
//{
//	for (size_t i = 0; i < arr.GetSize(); i++)
//	{
//		out << arr[i] << " ";
//	}
//	out << "\n";
//	return out;
//}
#endif