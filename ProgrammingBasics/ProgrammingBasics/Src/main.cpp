#include <iostream>
#include "Model.h"

int main()
{
	Model model;

	Array<double> arr_arc;
	arr_arc.pushBack(4.0);
	arr_arc.pushBack(5.0);
	arr_arc.pushBack(1.0);
	arr_arc.pushBack(2.0);
	arr_arc.pushBack(3.4 / 2.0);

	ID myArc;
	model.createObject(arc, arr_arc, myArc);

	type_id type;
	model.getObjType(myArc, type);

	system("pause");
	return 0;
}

//Dict<int, int> dict;
//dict.Add(5, 5);
//dict.Add(3, 3);
//dict.Add(7, 7);
//dict.Add(1, 1);
//dict.Add(2, 2);
//dict.Add(4, 4);
//dict.Add(6, 6);
//dict.Add(8, 8);
//dict.Add(9, 9);
//dict.Erase(9);
//dict.Erase(1);
//dict.find(6);
//int q = -1;
//if (dict.IsCurrent()) {
//	q = dict.GetCurrent();
//}
//std::cout << std::endl << q;
//int size = dict.getsize();
//dict.MoveParent();
//if (dict.IsCurrent()) {
//	q = dict.GetCurrent();
//}
//std::cout << std::endl << q;
//dict.MoveLeft();
//if (dict.IsCurrent()) {
//	q = dict.GetCurrent();
//}
//dict.MoveParent();
//dict.MoveRight();
//if (dict.IsCurrent()) {
//	q = dict.GetCurrent();
//}
//std::cout << std::endl << q;
//dict.MoveHead();
//if (dict.IsCurrent()) {
//	q = dict.GetCurrent();
//}
//std::cout << std::endl << q;
//
//dict.DeleteDict();
//std::cout << std::endl << dict.getsize();
//dict.Add(5, 5);
//dict.Add(3, 3);
//dict.Add(7, 7);