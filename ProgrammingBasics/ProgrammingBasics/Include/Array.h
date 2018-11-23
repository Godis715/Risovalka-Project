#ifndef __ARRAY
#define __ARRAY

template <class T> class Array
{
private:
	T* _storage = nullptr;
	int _size = 0;
	int _capacity;
	const int _default_capacity;

	void doubleCapacity()
	{
		auto newStorage = new T[((_capacity != 0) ? (2 * _capacity) : 1)];
		for (int i = 0; i < _capacity; i++)
		{
			newStorage[i] = _storage[i];
		}
		delete[] _storage;
		_storage = newStorage;
		_capacity = ((_capacity != 0) ? (2 * _capacity) : 1);
	}

public:
	class ReadMarker {
	private:
		int index;
		Array<T>* arr;
	public:

		ReadMarker(Array<T>* _arr, int _index) {
			arr = _arr;
			if (index > arr->_size) {
				index = arr->_size;
			}
			else {
				index = _index;
			}
		}

		ReadMarker(const ReadMarker& marker) {
			this->arr = marker.arr;
			this->index = marker.index;
		}

		ReadMarker(ReadMarker&& marker) {
			this->arr = marker.arr;
			this->index = marker.index;

			marker.arr = nullptr;
		}

		T GetValue() const {
			return arr->_storage[index];
		}

		void operator ++() {
			index++;
		}

		bool operator == (const ReadMarker& marker) {
			if (this->arr != marker.arr) {
				throw std::exception("Trying to compare non-native markers");
			}

			return (this->index == marker.index);
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
		if (size < 0)
		{
			throw std::invalid_argument("Bad array size!");
		}
		_capacity = size;
		_size = size;

		if (size == 0) {
			_storage = nullptr;
		}
		else {
			_storage = new T[_capacity];
		}
	}

	Array(int size, const T& default_value) : _default_capacity(size)
	{
		if (size < 0)
		{
			throw std::invalid_argument("Bad array size!");
		}
		_capacity = size;
		_size = size;
		if (_capacity == 0) {
			_storage = nullptr;
		}
		else {
			_storage = new T[_capacity];
		}
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
		this->_storage = (arr._storage != nullptr) ? new T[_capacity] : nullptr;
		for (int i = 0; i < _size; ++i) {
			this->_storage[i] = arr._storage[i];
		}
	}

	~Array()
	{
		if(_capacity != 0) delete[] _storage;
	}
	
	void operator=(Array&& arr) {

		if (_capacity != 0) {
			delete[] this->_storage;
		}

		this->_capacity = arr._capacity;
		this->_size = arr._size;
		this->_storage = arr._storage;
		arr._storage = nullptr;
	}

	void operator=(const Array& arr) {
		if (arr._storage != this->_storage) {
			delete[] this->_storage;

			this->_capacity = arr._capacity;
			this->_size = arr._size;
			this->_storage = new T[_capacity];
			for (int i = 0; i < _size; ++i) {
				this->_storage[i] = arr._storage[i];
			}
		}
	}

	Array<T>& operator+(const Array& arr) {
		_capacity = this->_capacity + arr._capacity;
		T* newStorage = new T[_capacity];
		
		for (int i = 0; i < _size; ++i) {
			newStorage[i] = this->_storage[i];
		}
		for (int i = 0; i < arr._size; ++i) {
			newStorage[i + _size] = arr._storage[i];
		}
		delete[] this->_storage;

		this->_size = arr._size + _size;
		this->_storage = newStorage;

		return *this;
	}

	void operator+=(const Array& arr) {
		this->_capacity += arr._capacity;
		T* newStorage = new T[this->_capacity];

		for (int i = 0; i < _size; ++i) {
			newStorage[i] = this->_storage[i];
		}
		for (int i = 0; i < arr._size; ++i) {
			newStorage[i + _size] = arr._storage[i];
		}
		delete[] this->_storage;

		this->_size += arr._size;
		this->_storage = newStorage;
	}

	Array<T>& operator+(const T& elem) {
		_capacity = this->_capacity + 1;
		T* newStorage = new T[_capacity];

		for (int i = 0; i < _size; ++i) {
			newStorage[i] = this->_storage[i];
		}
		newStorage[_size] = elem;
		delete[] this->_storage;

		this->_size = _size + 1;
		this->_storage = newStorage;

		return *this;
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
		--_size;
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
		for (int i = 0; i < newSize && i < _size; i++)
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

	void Insert(int index, const T& value) {
		if (index > _size) {
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

	void Replace(int index, const T& value) {
		if (index >= _size) {
			throw std::out_of_range("Index out of range!");
		}
		if (index < 0) {
			throw std::invalid_argument("Negative index!");
		}
		_storage[index] = value;
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

	void EraseO_1_(int index){
		if (index >= _size) {
			throw std::out_of_range("Index out of range!");
		}
		if (index < 0) {
			throw std::invalid_argument("Negative index!");
		}
		T Temp = _storage[index];
		_storage[index] = _storage[GetSize() - 1];
		_storage[GetSize() - 1] = Temp;
		PopBack();
	}

	bool find(T& value, bool(*cmp)())
	{
		for (int i = 0; i < _size; i++)
		{
			if (value == _storage[i])
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

// everlasting memory

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