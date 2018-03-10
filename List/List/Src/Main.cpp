#include <iostream>
#include <clocale>
#include "List.h"
#include "list_util.h"
#include <ctime>
using namespace std;



int main()
{
	srand(time(nullptr));
	List<int> list;
	try {
		std::setlocale(LC_ALL, "Russian");
		for (int i = 0; i < 100; ++i) {
			list.addElementAfterTail(rand()%1000);
		}
		printList<int>(list);
	}
	catch (std::exception e) {
		std::cout << "baaad";
	}
	std:cout << std::endl;
	BublesSort<int>(list);
	printList<int>(list);
	system("pause");
	return 0;
}