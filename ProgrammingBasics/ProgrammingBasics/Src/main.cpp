#include <ctime>
#include <vector>
#include <iostream>
#include <ctime>

#include "Requirement.h"
#include "DataController.h"
#include "Model.h"

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

	LoggerInit();
	auto dataCtrl = DataController::GetInstance();
	auto primCtrl = PrimController::GetInstance();
	auto reqCtrl = ReqController::GetInstance();
	auto model = Model::GetInstance();

	ID point1 = model->CreatePrimitive(ot_point, CreateArr(20.0, 30.0));
	ID point2 = model->CreatePrimitive(ot_point, CreateArr(0.0, -50.0));
	ID distBetPoints = model->CreateRequirement(ot_distBetPoints, CreateArr(point1, point2), CreateArr(20.0));

	ID segment1 = model->CreatePrimitive(ot_segment, CreateArr(0.0, 1.1, 2.2, -5.5));
	ID segment2 = model->CreatePrimitive(ot_segment, CreateArr(100.0, 200.0, 5.0, 6.0));
	ID equalSegment = model->CreateRequirement(ot_equalSegmentLen, CreateArr(segment1, segment2), Array<double>(0));
	
	SVGformat svg;

	svg.Save("temp.svg", true);
}