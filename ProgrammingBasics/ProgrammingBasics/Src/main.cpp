#include <ctime>
#include "Model.h"

Model model;

ID CreatePoint(double x, double y) {
	ID id;
	Array<double> params(2);
	params[0] = x;
	params[1] = y;

	if (!model.CreateObject(point_t, params, id)) {
		throw std::exception("Creating point failed");
	}
	return id;
}
ID CreateSegment(double x1, double y1, double x2, double y2) {
	ID id;
	Array<double> params(4);
	params[0] = x1;
	params[1] = y1;
	params[2] = x2;
	params[3] = y2;

	if (!model.CreateObject(segment_t, params, id)) {
		throw std::exception("Creating segment failed");
	}
	return id;
}

int main()
{
	ID point1 = CreatePoint(1.0, 2.0);
	ID point2 = CreatePoint(3.0, 5.0);

	Array<double> params1;
	model.getObjParam(point1, params1);

	Array<double> params2;
	model.getObjParam(point2, params2);

	double x1 = params1[0];
	double y1 = params1[1];
	double x2 = params2[0];
	double y2 = params2[1];

	Array<ID> id;
	id.PushBack(point1);
	id.PushBack(point2);

	params1.Clear();
	params1.PushBack(5.0);
	model.CreateRequirementByID(distBetPoints_t, id, params1);


	return 0;
}