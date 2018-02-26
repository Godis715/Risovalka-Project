#include <iostream>
#include "List.h"
#include "list_util.h"
using namespace std;



int main()
{
	List list;
	for (int i = 0; i < 10; ++i) {
		list.addElementAfterTail(i);
//		list.addElementAfterCurrent(i);
		//list.moveTail();
	}
	printList(list);

	return 0;
}