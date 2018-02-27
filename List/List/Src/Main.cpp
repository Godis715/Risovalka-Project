#include <iostream>
#include <clocale>
#include "List.h"
#include "list_util.h"
using namespace std;



int main()
{
	try {
		std::setlocale(LC_ALL, "Russian");
		List list;
		for (int i = 0; i < 10; ++i) {
			//list.addElementAfterTail(i);
		}
		printListStrange(list);
	}
	catch (std::exception e) {
		std::cout << "baaad";
	}
	system("pause");
	return 0;
}