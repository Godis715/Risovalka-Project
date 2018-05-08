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
ID CreateArc(double x1, double y1, double x2, double y2, double angle) {
	ID id;
	Array<double> params(5);
	params[0] = x1;
	params[1] = y1;
	params[2] = x2;
	params[3] = y2;
	params[4] = angle;

	if (!model.CreateObject(arc_t, params, id)) {
		throw std::exception("Creating arc failed");
	}
	return id;
}

void EqualSegmentLenReq(const ID& seg1, const ID& seg2) {
	Array<ID> segments(2);
	segments[0] = seg1;
	segments[1] = seg2;

	Array<double> params(0);

	if (!model.CreateRequirementByID(equalSegmentLen_t, segments, params)) {
		throw std::exception("Creating equalSegmentLen requirement failed");
	}
}
void DistBetPointsReq(const ID& point1, const ID& point2, double dist) {
	Array<ID> points(2);
	points[0] = point1;
	points[1] = point2;

	Array<double> params(1);
	params[0] = dist;

	if (!model.CreateRequirementByID(distBetPoints_t, points, params)) {
		throw std::exception("Creating distBetPoints requirement failed");
	}
}


int main()
{
	model;
	ID segment1 = CreateSegment(0.0, 0.0, 0.0, 20.0);
	ID segment2 = CreateSegment(0.0, 0.0, 0.0, 5.0);

	EqualSegmentLenReq(segment1, segment2);
	ID point1 = CreatePoint(0.0, 0.0);
	ID point2 = CreatePoint(1.0, 1.0);
	DistBetPointsReq(point1, point2, 9.0);

	BinSearchTree<ID, ID> component;
	model.GetComponent(segment1, component);

	model.GetComponent(point1, component);

	return 0;
}