#include <iostream>
#include "Array.cpp"

int main()
{
	int size = 20;
	Array<int> arr(size);
	for (size_t i = 0; i < size; i++)
	{
		arr[i] = rand() % 100;
	}
	std::cout << arr << "\n";
	arr.sort(0, size - 1);
	std::cout << arr << "\n";
	arr.reverse(0, size - 1);
	std::cout << arr << "\n";
	arr.sort(5, 10);
	std::cout << arr << "\n";
	arr.clear();
	arr.pushBack(1);
	arr.pushBack(2);
	arr.pushBack(3);
	arr.pushBack(21);
	arr.pushBack(35);
	arr.insert(3, 6);
	arr.insert(3, 6);
	std::cout << arr << "\n";
	std::cout << arr.popBack() << "\n";
	std::cout << arr.popBack() << "\n";
	std::cout << arr.popBack() << "\n";
	std::cout << arr.popBack() << "\n";
	std::cout << "Size = " << arr.getSize() << "\n";

	system("pause");
	return 0;
}
