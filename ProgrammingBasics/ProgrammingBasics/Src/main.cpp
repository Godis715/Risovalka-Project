#include <ctime>
#include <vector>
#include <iostream>
#include <ctime>

#include "Requirement.h"
#include "DataController.h"
#include "Model.h"
#include "ViewFLTK.h"

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

int main()
{
	//Model* model = Model::GetInstance();
	//ID circle = model->CreatePrimitive(ot_circle, CreateArr(0.0, 0.0, 10.0));

	//Array<double> params = model->GETVARPARAMS(circle, RADIUS, CENTER);
	//for (int i = 0; i < params.GetSize(); ++i) {
	//	std::cout << params[i] << " ";
	//}
	LoggerInit();
	IView* view = ViewFLTK::GetInstance();
	view->Run();
}