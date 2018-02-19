#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

class Array
{
public:
	Array(Array &arr)
	{
		m_pSize = arr.m_pSize;
		if (m_pSize > 0)
		{
			m_pStorage = new int[m_pSize];
			for (size_t i = 0; i < m_pSize; i++)
			{
				m_pStorage[i] = arr.m_pStorage[i];
			}
		}
	}
	Array()
	{
		m_pStorage = nullptr;
		m_pSize = 0;
	}
	Array(int k)
	{
		if (k <= 0)
		{
			throw invalid_argument("bad array size");
		}
		else
		{
			m_pStorage = new int[k];
			m_pSize = k;
		}
		
	}
	~Array()
	{
		if (m_pStorage != nullptr)
		{
			delete[] m_pStorage;
		}
	}
	int getElement(int number)const
	{
		return m_pStorage[number];
	}
	size_t getSize()const 
	{
		return m_pSize;
	}
	void addElement(int digit)
	{	
		if (m_pStorage == nullptr)
		{
			m_pStorage = new int[1];
			m_pStorage[0] = digit;
			m_pSize = 1;
		}
		else
		{
			int *newM_pStorage = new int[m_pSize + 1];
			for (size_t i = 0; i < m_pSize; i++)
			{
				newM_pStorage[i] = m_pStorage[i];
			}
			newM_pStorage[m_pSize] = digit;
			m_pSize++;
			delete[] m_pStorage;
			m_pStorage = newM_pStorage;
		}
		
	}
	void removeElement(size_t number)
	{
		if (m_pSize == 1)
		{
			m_pSize = 0;
			m_pStorage = nullptr;
		}
		else
		{
			int *newM_pStorage = new int[m_pSize - 1];
			for (size_t i = 0; i < number; i++)
			{
				newM_pStorage[i] = m_pStorage[i];
			}
			for (size_t i = number; i < m_pSize - 1; i++)
			{
				newM_pStorage[i] = m_pStorage[i + 1];
			}
			m_pSize--;
			delete[] m_pStorage;
			m_pStorage = newM_pStorage;
		}
	
	}
	void clearArray()
	{
		if (m_pStorage != nullptr)
		{
			delete[] m_pStorage;
			m_pStorage = nullptr;
			m_pSize = 0;
		}
		
	}
	void setElement(size_t index, int digit)
	{
		m_pStorage[index] = digit;
	}
	
	
private:
	int *m_pStorage;
	size_t m_pSize;
};
void sort(Array *arr)
{
	int countSwap = 0;
	do
	{
		countSwap = 0;
		for (size_t i = 1; i < arr->getSize(); i++)
		{
			if (arr->getElement(i - 1) > arr->getElement(i))
			{
				int b;
				b = arr->getElement(i - 1);
				arr->setElement(i - 1, arr->getElement(i));
				arr->setElement(i, b);
				countSwap++;
			}
		}
	} while (countSwap != 0);
}
bool testAddElement()
{
	Array arr;
	arr.addElement(1);
	arr.addElement(2);
	arr.addElement(3);
	return arr.getSize() == 3;

}
bool testRemoveElement()
{
	Array arr;
	arr.addElement(1);
	arr.addElement(2);
	arr.addElement(3);
	arr.removeElement(1);
	bool check = false;
	if (arr.getElement(0) == 1 && arr.getElement(1) == 3)check = true;
	return (arr.getSize() == 2) && check;
}
void watch(Array arr)
{
	for (size_t i = 0; i < arr.getSize(); i++)
	{
		cout << arr.getElement(i) << " ";
	}
}
void test()
{
	for (;;)
	{
		Array m;
		for (size_t i = 0; i < 100; i++)
		{
			m.addElement(i);
		}
	}
}
void test1()
{
	Array m;
	for (;;)
	{
		for (size_t i = 0; i < 100; i++)
		{
			m.addElement(i);
		}
		watch(m);
		m.clearArray();
	}
}
int main()
{
	test1();
	
	Array arr;
	/*try
	{
		int k;
		cin >> k;
		Array arr1(int k);
	}
	catch
	{

	}*/
	ifstream file("file.txt");
	if (file.is_open())
	{
		while (!file.eof())
		{
			int a;
			file >> a;
			arr.addElement(a);
		}
	}
	file.close();
	watch(arr);
	sort(&arr);
	cout << endl;
	watch(arr);
	system("pause");
	if (testAddElement)
	{
		cout << "AddElement robit";
	}
	else
	{
		cout << "AddElement ne robit";
		return 0;
	}
	cout << endl;
	if (testRemoveElement)
	{
		cout << "RemoveElement robit";
	}
	else
	{
		cout << "RemoveElement ne robit";
	}
	
	system("pause");
	return 0;
}