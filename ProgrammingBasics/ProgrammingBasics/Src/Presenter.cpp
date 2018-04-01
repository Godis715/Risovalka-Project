#include "Presenter.h"

ID Presenter::CreatePoint(double x, double y) {
	Array<double> params;
	params.pushBack(x);
	params.pushBack(y);

	ID id;
	model->createObject(point, params, id);
	return id;
}
ID Presenter::CreateSegment(double x1, double y1, double x2, double y2) {
	ID id;
	Array<double> params;
	params.pushBack(x1);
	params.pushBack(y1);
	params.pushBack(x2);
	params.pushBack(y2);
	model->createObject(segment, params, id);
	return id;
}
ID Presenter::CreateArc(double x1, double y1, double x2, double y2, double angle)
{
	ID id;
	Array<double> params;
	params.pushBack(x1);
	params.pushBack(y1);
	params.pushBack(x2);
	params.pushBack(y2);
	params.pushBack(angle);
	model->createObject(arc, params, id);
	return id;
}

Presenter::Presenter(View* view)
{
	this->view = view;
}

void Presenter::CreateRequirmentDistBetPoints(ID point1, ID point2, double d) 
{
	Array<double> dist;
	Array<ID> points;

	points.pushBack(point1);
	points.pushBack(point2);

	dist.pushBack(d);
	model->createRequirement(distBetPoints, points, dist);
	return;
}
void Presenter::CreateRequirmentPointsOnTheOneHand(ID segment, ID point1, ID point2)
{
	Array<double> params;//empty
	Array<ID> components;

	components.pushBack(point1);
	components.pushBack(point2);

	model->createRequirement(pointsOnTheOneHand, components, params);
	return;
}
void Presenter::CreateRequirmentDistanceBetweenPointSegment(ID segment, ID point, double d)
{
	Array<double> dist;
	Array<ID> components;

	components.pushBack(segment);
	components.pushBack(point);

	dist.pushBack(d);
	model->createRequirement(distBetPointSeg, components, dist);
	return;
}
void Presenter::CreateRequirmentAngleBetweenSegments(ID segment1, ID segment2, double a)
{
	Array<double> angle;
	Array<ID> segments;

	segments.pushBack(segment1);
	segments.pushBack(segment2);

	angle.pushBack(a);
	model->createRequirement(angleBetSeg, segments, angle);
	return;
}
void Presenter::CreateRequirmentDistanceBetweenPointArc(ID arc, ID point, double d)
{
	Array<double> dist;
	Array<ID> components;

	components.pushBack(arc);
	components.pushBack(point);

	dist.pushBack(d);
	model->createRequirement(distBetPointArc, components, dist);
	return;
}
void Presenter::CreateRequirmentPointInArc(ID arc, ID point)
{
	Array<double> params;//empty
	Array<ID> components;

	components.pushBack(arc);
	components.pushBack(point);

	model->createRequirement(pointInArc, components, params);
	return;
}
void Presenter::CreateRequirmentTrianle(ID segment1, ID segment2, ID segment3) {
	Array<double> params;//empty
	Array<ID> components;

	components.pushBack(segment1);
	components.pushBack(segment2);
	components.pushBack(segment3);

	model->createRequirement(pointInArc, components, params);
	return;
}
void Presenter::CreateRequirmentBestTrianle(ID segment1, ID segment2, ID segment3, double size) {
	Array<double> params;
	Array<ID> components;

	components.pushBack(segment1);
	components.pushBack(segment2);
	components.pushBack(segment3);
	params.pushBack(size);

	model->createRequirement(pointInArc, components, params);
	return;
}

int Presenter::Optimize() {
	return model->Optimize();
}
void Presenter::PrintSystemRequirement() {
	model->PrintSystemRequirement();
}
bool Presenter::getObjParam(const ID& id, Array<double>& array) {
	model->getObjParam(id, array);
}

void Presenter::DrawPoint(double x, double y)
{
	CreatePoint(x, y);
	//Draw();
}
void Presenter::DrawSegment(double x1, double y1, double x2, double y2)
{
	CreateSegment(x1, y1, x2, y2);
	//Draw();
}
void Presenter::DrawTriangle(
	double seg1x1, double seg1y1, double seg1x2, double seg1y2,
	double seg2x1, double seg2y1, double seg2x2, double seg2y2,
	double seg3x1, double seg3y1, double seg3x2, double seg3y2
)
{
	ID segment1 = CreateSegment(seg1x1, seg1y1, seg1x2, seg1y2);
	ID segment2 = CreateSegment(seg2x1, seg2y1, seg2x2, seg2y2);
	ID segment3 = CreateSegment(seg3x1, seg3y1, seg3x2, seg3y2);

	Array<ID> points1;
	Array<ID> points2;
	Array<ID> points3;

	model->GetSegmentPoints(segment1, points1);
	model->GetSegmentPoints(segment2, points2);
	model->GetSegmentPoints(segment3, points3);

	CreateRequirmentDistBetPoints(points1[1], points3[0], 0.0);
	CreateRequirmentDistBetPoints(points1[0], points2[1], 0.0);
	CreateRequirmentDistBetPoints(points3[1], points2[0], 0.0);

	CreateRequirmentDistBetPoints(points1[1], points1[0], 35.0);
	CreateRequirmentDistBetPoints(points2[0], points2[1], 35.0);
	CreateRequirmentDistBetPoints(points3[1], points3[0], 35.0);

	model->Optimize();
	//Draw();
}