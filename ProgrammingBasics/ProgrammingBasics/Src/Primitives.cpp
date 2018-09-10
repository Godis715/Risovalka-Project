#include "Primitives.h"
#include <stdexcept>

ID Primitive::GetID() const {
	return id;
}
Primitive::Primitive(ID _id, object_type _type) :
	id(_id),
	type(_type)
{

}
object_type Primitive::GetType() {
	return type;
}

Point::Point(const Vector2& pos) :
	Primitive(IDGenerator::getInstance()->generateID(), ot_point)
{
	this->parent = nullptr;
	this->position = pos;
}
Point::Point(double _x, double _y) :
	Primitive(IDGenerator::getInstance()->generateID(), ot_point)
{
	this->parent = nullptr;
	this->position = Vector2(_x, _y);
}

Point::Point(ID id, double _x, double _y) :
	Primitive(id, ot_point)
{
	this->parent = nullptr;
	this->position = Vector2(_x, _y);
}
Point::Point(const Point& _p) :
	Primitive(IDGenerator::getInstance()->generateID(), ot_point)
{
	this->parent = nullptr;
	this->position = _p.position;
}
double Point::GetDistance(const Vector2& point) const {
	return sqrt((position.x - point.x)*(position.x - point.x) +
		(position.y - point.y)*(position.y - point.y));
}
Vector2 Point::GetPosition() const {
	return position;
}
void Point::SetPosition(const Vector2& _pos) {
	position = _pos;
}
void Point::SetPosition(double x, double y) {
	position.x = x;
	position.y = y;
}
Primitive* Point::GetParent() {
	return parent;
}
void Point::DeleteParent() {
	parent = nullptr;
}
bool Point::SetParent(Primitive* _parent) {
	if (parent != nullptr || _parent == nullptr) {
		return false;
	}
	parent = _parent;
}


Segment::Segment(Point* _p1, Point* _p2) :
	Primitive(IDGenerator::getInstance()->generateID(), ot_segment)
{
	if (_p1 == nullptr || _p2 == nullptr) {
		throw std::invalid_argument("Segment::Segment::parameters was nullptr");
	}

	point1 = _p1;
	point2 = _p2;

	_p1->SetParent(this);
	_p1->SetParent(this);

}

Segment::Segment(ID id, Point* _p1, Point* _p2) :
	Primitive(id, ot_segment)
{
	if (_p1 == nullptr || _p2 == nullptr) {
		throw std::invalid_argument("Segment::Segment::parameters was nullptr");
	}

	point1 = _p1;
	point2 = _p2;

	_p1->SetParent(this);
	_p1->SetParent(this);

}
double Segment::GetLength() const {
	return (point1->GetPosition() - point2->GetPosition()).GetLength();
}
Vector2 Segment::GetPoint1_pos() const {
	return point1->GetPosition();
}
Vector2 Segment::GetPoint2_pos() const {
	return point2->GetPosition();
}
void Segment::SetPoint1_pos(Vector2 _pos) {
	point1->SetPosition(_pos);
}
void Segment::SetPoint2_pos(Vector2 _pos) {
	point2->SetPosition(_pos);
}
ID Segment::GetPoint1_ID() const {
	return point1->GetID();
}
ID Segment::GetPoint2_ID() const {
	return point2->GetID();
}
double Segment::Inequality(Vector2 vector) {
	Equation* equation = this->CreateEquation();
	double answer = equation->a * vector.x + equation->b * vector.y + equation->c;
	delete equation;
	return answer;
}
double Segment::GetDistance(const Vector2& point) const {
	double dotProduct1 = 0.0;
	double dotProduct2 = 0.0;
	Vector2 point1 = this->point1->GetPosition();
	Vector2 point2 = this->point2->GetPosition();

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
	Primitive(IDGenerator::getInstance()->generateID(), ot_arc)
{
	if (_p1 == nullptr || _p2 == nullptr) {
		throw std::invalid_argument("Arc::Arc::parameters was nullptr");
	}

	point1 = _p1;
	point2 = _p2;

	angle = _angle;

	_p1->SetParent(this);
	_p2->SetParent(this);
}

// write this function
double Arc::GetDistance(const Vector2& _point) const {
	Vector2 r1 = point1->GetPosition() - center;
	Vector2 r2 = point2->GetPosition() - center;
	Vector2 vec = _point - center;

	bool inSector = true;

	double cross1 = Vector2::Cross(r1, vec);
	double cross2 = Vector2::Cross(vec, r2);

	if (angle < PI) {
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
	return center;
}

void Arc::RestoreCenter() {
	
	Vector2 point1Pos = point1->GetPosition();
	Vector2 point2Pos = point2->GetPosition();

	Vector2 base = point2Pos - point1Pos;
	double baseLength = base.GetLength();

	double H = (baseLength / 2.0) / tan(angle / 2.0);

	Vector2 ortH(-base.y / baseLength, base.x / baseLength);
	Vector2 midBase = (point1Pos + point2Pos) / 2.0;

	center = midBase + (ortH * H);

	point1Pos = point1Pos - center;
	point2Pos = point2Pos - center;

	if (Vector2::Cross(point1Pos, point2Pos) * (angle - PI) > 0) {
		center = midBase - (ortH * H);
	}
}

ID Arc::GetPoint1_ID() const {
	return point1->GetID();
}
ID Arc::GetPoint2_ID() const {
	return point2->GetID();
}
Vector2 Arc::GetPoint1_pos() const {
	return point1->GetPosition();
}
Vector2 Arc::GetPoint2_pos() const {
	return point2->GetPosition();
}
void Arc::SetPoint1_pos(Vector2 _pos) {
	point1->SetPosition(_pos);
}
void Arc::SetPoint2_pos(Vector2 _pos) {
	point2->SetPosition(_pos);
}
double Arc::GetAngle() const {
	return angle;
}

void Arc::SetAngle(double newAngle) {
	if (newAngle > 2 * PI) {
		angle = newAngle - (double)(int)(newAngle / (2 * PI)) * 2 * PI;
		return;
	}
	if (newAngle < 0.0) {
		angle = newAngle + ((double)((int)(abs(newAngle) / (2 * PI)) + 1) * 2 * PI);
		return;
	}
}

Circle::Circle(Point* _center,  double _radius) :
	Primitive(IDGenerator::getInstance()->generateID(), ot_circle)
{
	if (_center == nullptr) {
		throw std::invalid_argument("Circle::Circle::_center was nullptr");
	}
	if (_radius < 0) {
		throw std::invalid_argument("Circle::Circle::_radius was negative");
	}

	center = _center;

	radius = _radius;

	_center->SetParent(this);
}

Circle::Circle(ID id, Point* _center, double _radius) :
	Primitive(id, ot_circle)
{
	if (_center == nullptr) {
		throw std::invalid_argument("Circle::Circle::_center was nullptr");
	}
	if (_radius < 0) {
		throw std::invalid_argument("Circle::Circle::_radius was negative");
	}

	center = _center;

	radius = _radius;

	_center->SetParent(this);
}

// write this function
double Circle::GetDistance(const Vector2& _point) const {
	return abs(radius - (_point - Vector2(center->position.x, center->position.y)).GetLength());
}

Vector2 Circle::GetCenter() const {
	return center->GetPosition();
}

ID Circle::GetCenter_ID() const {
	return center->GetID();
}

void Circle::SetCenter_pos(Vector2 _pos) {
	center->SetPosition(_pos);
}

double Circle::GetRadius() const {
	return radius;
}

void Circle::SetRadius(double _radius)
{
	radius = _radius;
}

