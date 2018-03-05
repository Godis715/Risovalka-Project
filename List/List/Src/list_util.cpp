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
			std::cout << "������ ����\n";
		}
	} while (marker->moveNext());
	std::cout << "\n";
}

void BublesSort(List& list) {
	if (list.getSize() < 2) {
		return;
	}
	
	auto markerLeft = list.createMarker();
	auto markerRight = list.createMarker();
	markerRight->moveNext();
	bool WasSwap = false;
	try
	{
		markerLeft->getCurrent();
	}
	catch (std::exception)
	{
		std::cout << "������ ����\n";
	}
	try
	{
		markerRight->getCurrent();
	}
	catch (std::exception)
	{
		std::cout << "������ ����\n";
	}

	do
	{
		WasSwap = false;
		markerLeft->moveHead();
		markerRight->moveHead();
		markerRight->moveNext();
		do
		{
			int Left = markerLeft->getCurrent();
			int Right = markerRight->getCurrent();
			if (Left > Right) {
				markerLeft->setCurrent(Right);
				markerRight->setCurrent(Left);
				WasSwap = true;
			}

		} while ((markerLeft->moveNext()) && (markerRight->moveNext()));
	} while (WasSwap);
	return;
}