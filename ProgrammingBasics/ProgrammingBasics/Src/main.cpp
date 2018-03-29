#include <iostream>
#include "Requirement.h"

int main()
{
	Dict<int, int> dict;
	dict.Add(5, 5);
	dict.Add(3, 3);
	dict.Add(7, 7);
	dict.Add(1, 1);
	dict.Add(2, 2);
	dict.Add(4, 4);
	dict.Add(6, 6);
	dict.Add(8, 8);
	dict.Add(9, 9);
	dict.Erase(9);
	dict.Erase(1);
	dict.find(6);
	int q = -1;
	if (dict.IsCurrent()) {
		q = dict.GetCurrent();
	}
	std::cout << std::endl << q;
	int size = dict.getsize();
	dict.MoveParent();
	if (dict.IsCurrent()) {
		q = dict.GetCurrent();
	}
	std::cout << std::endl << q;
	dict.MoveLeft();
	if (dict.IsCurrent()) {
		q = dict.GetCurrent();
	}
	dict.MoveParent();
	dict.MoveRight();
	if (dict.IsCurrent()) {
		q = dict.GetCurrent();
	}
	std::cout << std::endl << q;
	dict.MoveHead();
	if (dict.IsCurrent()) {
		q = dict.GetCurrent();
	}
	std::cout << std::endl << q;

	dict.DeleteDict();
	std::cout << std::endl << dict.getsize();
	dict.Add(5, 5);
	dict.Add(3, 3);
	dict.Add(7, 7);
	system("pause");
	return 0;
}