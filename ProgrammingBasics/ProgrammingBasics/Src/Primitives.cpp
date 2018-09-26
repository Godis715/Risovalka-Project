#include "Primitives.h"
#include <stdexcept>

Primitive::Primitive(object_type _type, const Array<double>& _params, const Array<ID>& _children)
	: Object(_type, _params, children)
{

}

Array<double> Primitive::GetDoubleParamsAsValues() {
	Array<double> doubleParamsValues(doubleParams.GetSize());
	for (int i = 0; i < params.GetSize(); ++i) {
		doubleParamsValues[i] = *doubleParams[i];
	}
	return doubleParamsValues;
}

Array<double*> Primitive::GetDoubleParamsAsPointers() {
	return doubleParams;
}

void Primitive::ApplyDoubleParams() {
	for (int i = 0; i < params.GetSize(); ++i) {
		params[i] = *doubleParams[i];
	}
}

Point::Point(const Vector2& pos) :
	Primitive(ot_point, CreateArr(pos.x, pos.y), Array<ID>(0))
{
	this->x = &params[0];
	this->y = &params[1];
}
Point::Point(double _x, double _y) :
	Primitive(ot_point, CreateArr(_x, _y), Array<ID>(0))
{
	this->x = &params[0];
	this->y = &params[1];
}
Point::Point(const Point& _p) :
	Primitive(ot_point, CreateArr(*_p.x, *_p.y), Array<ID>(0))
{
	this->x = &params[0];
	this->y = &params[1];
}
double Point::GetDist(const Vector2& point) const {
	return sqrt((*x - point.x)*(*x - point.x) +
		(*y - point.y)*(*y - point.y));
}
Vector2 Point::GetPos() const {
	return Vector2(*x, *y);
}
void Point::SetPos(const Vector2& _pos) {
	*x = _pos.x;
	*y = _pos.y;
}
void Point::SetPos(double _x, double _y) {
	*x = _x;
	*y = _y;
}

Segment::Segment(Point* _p1, Point* _p2) :
	Primitive(ot_segment, Array<double>(0), CreateArr(_p1->GetID(), _p2->GetID()))
{
	if (_p1 == nullptr || _p2 == nullptr) {
		throw std::invalid_argument("Segment::Segment::parameters was nullptr");
	}

	point1 = _p1;
	point2 = _p2;
}
double Segment::GetLength() const {
	return (point1->GetPos() - point2->GetPos()).GetLength();
}
Vector2 Segment::GetPointPos1() const {
	return point1->GetPos();
}
Vector2 Segment::GetPointPos2() const {
	return point2->GetPos();
}
void Segment::SetPointPos1(Vector2 _pos) {
	point1->SetPos(_pos);
}
void Segment::SetPointPos2(Vector2 _pos) {
	point2->SetPos(_pos);
}
ID Segment::GetPointID1() const {
	return point1->GetID();
}
ID Segment::GetPointID2() const {
	return point2->GetID();
}
double Segment::Inequality(Vector2 vector) {
	Equation* equation = this->CreateEquation();
	double answer = equation->a * vector.x + equation->b * vector.y + equation->c;
	delete equation;
	return answer;
}
double Segment::GetDist(const Vector2& point) const {
	double dotProduct1 = 0.0;
	double dotProduct2 = 0.0;
	Vector2 point1 = this->point1->GetPos();
	Vector2 point2 = this->point2->GetPos();

	Vector2 pointTo1 = point - point1;
	Vector2 pointTo2 = point - point2;
	Vector2 segment = point2 - point1;
	dotProduct1 = Vector2::Dot(pointTo1, segment);
	dotProduct2 = Vector2::Dot(pointTo2, segment);
	dotProduct2 *= -1;
	double answer = 0;
	if (dotProduct1 >= 0 && dotProduct2 >= 0) {
		answer = abs(Vector2::Cross(pointTo1, segment));
		answer /= 2;
		answer /= segment.GetLength();
	}
	else {
		answer = pointTo1.GetLength();
		if (answer > pointTo2.GetLength()) {
			answer = pointTo2.GetLength();
		}
	}
	return answer;
}

Arc::Arc(Point* _p1, Point* _p2, double _angle) :
	Primitive(ot_arc, CreateArr(_angle), CreateArr(_p1->GetID(), _p2->GetID()))
{
	if (_p1 == nullptr || _p2 == nullptr) {
		throw std::invalid_argument("Arc::Arc::parameters was nullptr");
	}

	point1 = _p1;
	point2 = _p2;

	angle = &params[0];
}

// write this function
double Arc::GetDist(const Vector2& _point) const {
	Vector2 center(cx, cy);
	Vector2 r1 = point1->GetPos() - center;
	Vector2 r2 = point2->GetPos() - center;
	Vector2 vec = _point - center;

	bool inSector = true;

	double cross1 = Vector2::Cross(r1, vec);
	double cross2 = Vector2::Cross(vec, r2);

	if (*angle < PI) {
		inSector = (cross1 > 0 && cross2 > 0);
	}
	else {
		inSector = (cross1 > 0 || cross2 > 0);
	}
	if (inSector) {
		return abs(vec.GetLength() - r1.GetLength());
	}
	else {
		double dist1 = (r1 - vec).GetLength();
		double dist2 = (r2 - vec).GetLength();
		return (dist1 > dist2) ? dist1 : dist2;
	}
}

Vector2 Arc::GetCenter() const {
	return Vector2(cx, cy);
}

void Arc::RestoreCenter() {
	Vector2 center;
	Vector2 point1Pos = point1->GetPos();
	Vector2 point2Pos = point2->GetPos();

	Vector2 base = point2Pos - point1Pos;
	double baseLength = base.GetLength();

	double H = (baseLength / 2.0) / tan(*angle / 2.0);

	Vector2 ortH(-base.y / baseLength, base.x / baseLength);
	Vector2 midBase = (point1Pos + point2Pos) / 2.0;

	center = midBase + (ortH * H);

	point1Pos = point1Pos - center;
	point2Pos = point2Pos - center;

	if (Vector2::Cross(point1Pos, point2Pos) * (*angle - PI) > 0) {
		center = midBase - (ortH * H);
	}
	cx = center.x;
	cy = center.y;
}

ID Arc::GetPointID1() const {
	return point1->GetID();
}
ID Arc::GetPointID2() const {
	return point2->GetID();
}
Vector2 Arc::GetPointPos1() const {
	return point1->GetPos();
}
Vector2 Arc::GetPointPos2() const {
	return point2->GetPos();
}
void Arc::SetPointPos1(Vector2 _pos) {
	point1->SetPos(_pos);
}
void Arc::SetPointPos2(Vector2 _pos) {
	point2->SetPos(_pos);
}
double Arc::GetAngle() const {
	return *angle;
}

void Arc::SetAngle(double newAngle) {
	if (newAngle > 2 * PI) {
		*angle = newAngle - (double)(int)(newAngle / (2 * PI)) * 2 * PI;
		return;
	}
	if (newAngle < 0.0) {
		*angle = newAngle + ((double)((int)(abs(newAngle) / (2 * PI)) + 1) * 2 * PI);
		return;
	}
}

Circle::Circle(Point* _center,  double _radius) :
	Primitive(ot_circle, CreateArr(_radius), CreateArr(_center->GetID()))
{
	if (_center == nullptr) {
		throw std::invalid_argument("Circle::Circle::_center was nullptr");
	}
	if (_radius < 0) {
		throw std::invalid_argument("Circle::Circle::_radius was negative");
	}

	center = _center;

	radius = &params[0];
}

// write this function
double Circle::GetDist(const Vector2& _point) const {
	return abs(*radius - (_point - Vector2(center->GetPos().x, center->GetPos().y)).GetLength());
}

Vector2 Circle::GetCenter() const {
	return center->GetPos();
}

ID Circle::GetCenterID() const {
	return children[0];
}

void Circle::SetCenterPos(Vector2 _pos) {
	center->SetPos(_pos);
}

double Circle::GetRadius() const {
	return *radius;
}

void Circle::SetRadius(double _radius)
{
	*radius = _radius;
}

