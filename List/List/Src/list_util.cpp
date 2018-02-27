#include "list_util.h"
#include <iostream>

void printListStrange(List& list) {
	auto marker = list.createMarker();
	do {
		if (marker->getCurrent() % 2 == 0) {
			std::cout << marker->getCurrent() << " ";
		}
	} while (marker->moveNext());
	marker->moveHead();
	do {
		if (marker->getCurrent() % 2 == 1) {
			std::cout << marker->getCurrent() << " ";
		}
	} while (marker->moveNext());
}

void printList(List& list) {
	auto marker = list.createMarker();
	do {
		try
		{
			std::cout << marker->getCurrent() << " ";
		}
		catch (std::out_of_range)
		{
			std::cout << "Список пуст\n";
		}
	} while (marker->moveNext());
	std::cout << "\n";
}