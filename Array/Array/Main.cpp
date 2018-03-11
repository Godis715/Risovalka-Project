#include <iostream>
#include "Array.cpp"

int main()
{
	int size = 6;
	Array<int> arr(size);
	for (size_t i = 0; i < size; i++)
	{
		arr[i] = 2*i;
	}
	/*std::cout << arr.binSearch(0, size - 1, -1) << "\n";
	std::cout << arr.binSearch(0, size - 1, 4) << "\n";
	std::cout << arr.binSearch(0, size - 1, 7) << "\n";
	std::cout << arr.binSearch(0, size - 1, 11) << "\n";*/

	arr.insert(arr.binSearch(0, arr.getSize() - 1, -1) + 1, -1);
	arr.sort(0, arr.getSize() - 1);
	arr.insert(arr.binSearch(0, arr.getSize() - 1, 11) + 1, 11);
	arr.sort(0, arr.getSize() - 1);
	arr.insert(arr.binSearch(0, arr.getSize() - 1, 5) + 1, 5);
	//arr.insert(arr.binSearch(0, size - 1, -1) + 1, -1);
	std::cout << arr << "\n";
	system("pause");
	return 0;
}
