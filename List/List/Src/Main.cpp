#include <iostream>
#include <clocale>
#include "List.h"
#include "list_util.h"
using namespace std;



int main()
{
	setlocale(LC_ALL, "Russian");
	List list;
	for (int i = 0; i < 10; ++i) {
		//list.addElementAfterTail(i);
	}
	printList(list);
	system("pause");
	return 0;
}