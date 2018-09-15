#include <ctime>
#include <vector>
#include <iostream>
#include <ctime>

#include "Requirement.h"

void LoggerInit() {
	Logger::InitLogger(&std::cout, LEVEL_1);
}

Array<double> PointParams(double x, double y) {
	Array<double> params(2);
	params[0] = x;
	params[1] = y;
	return params;
}

Array<double> SegParams(double x1, double y1, double x2, double y2) {
	Array<double> params(4);
	params[0] = x1;
	params[1] = y1;
	params[2] = x2;
	params[3] = y2;
	return params;
}

Array<double> CircleParams(double x1, double y1, double radius) {
	Array<double> params(3);
	params[0] = x1;
	params[1] = y1;
	params[2] = radius;
	return params;
}

class Counter {
public:
	int count;
	Counter() {
		count = 0;
	}
	int operator()() {
		return count++;
	}
};


bool CheckCircles(BinSearchTree<int, int>& tree) {
	auto it = tree.GetMarker();
	int size = tree.GetSize();

	int i = 0;
	while (it.IsValid()) {
		++it;
		i++;
		if (i > size) {
			return false;
		}
	}
	return true;
}
const int number = 6;
int* GenerateRandomArray() {
	int* arr = new int[number];
	for (int i = 0; i < number; ++i) {
		arr[i] = rand() % 3;
	}
	return arr;
}

int GetErrorIteration() {
	while (true) {
		int* arr = GenerateRandomArray();
		for (int i = 1; i < number; ++i) {
			BinSearchTree<int, int> tree;
			for (int j = 0; j < i; ++j) {
				tree.Add(arr[j], arr[j]);
			}
			bool goodTree = CheckCircles(tree);
			if (!goodTree) {
				for (int k = 0; k < number; k++) {
					std::cout << arr[k] << " ";
				}
				std::cout << "\nat " << i;
				system("pause");
			}
		}
		delete[] arr;
	}
	return -1;
}

int main()
{
	srand(time(0));
	int n = GetErrorIteration();
	system("pause");
}