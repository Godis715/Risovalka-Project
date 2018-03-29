#include "Primitives.h"
#include <cmath>

ID Primitive::GetId() const {
	return id;
}
Primitive::Primitive(ID _id, Type _type) :
	id(_id),
	type(_type) {
}

Type Primitive::GetType() {
	return type;
}

Point::Point(Vector2 pos) :
	Primitive(IDGenerator::getInstance()->generateID(),
		Type(point))
{
	this->position = pos;
}
Point::Point(double _x, double _y) :
	Primitive(IDGenerator::getInstance()->generateID(),
		Type(point))
{
	this->position = Vector2(_x, _y);
}
Point::Point(const Point& _p) :
	Primitive(IDGenerator::getInstance()->generateID(),
		Type(point))
{
	this->position = _p.position;
}
double Point::GetDistance(Vector2 point) {
	return sqrt((position.x - point.x)*(position.x - point.x) +
		(position.y - point.y)*(position.y - point.y));
}

Vector2 Point::GetPosition() const {
	return position;
}
void Point::SetPosition(Vector2 _pos) {
	position = _pos;
}
void Point::SetPosition(double x, double y) {
	position.x = x;
	position.y = y;
}


Segment::Segment(Vector2 _p1, Vector2 _p2) :
	Primitive(IDGenerator::getInstance()->generateID(),
		Type(segment)),
	point1(Point(_p1)),
	point2(Point(_p2))
{

}

Segment::Segment(double x1, double y1, double x2, double y2) :
	Primitive(IDGenerator::getInstance()->generateID(),
		Type(segment)),
	point1(Point(x1, y1)),
	point2(Point(x2, y2))
{

}

Vector2 Segment::GetPoint1_pos() const {
	return point1.GetPosition();
}
Vector2 Segment::GetPoint2_pos() const {
	return point2.GetPosition();
}
void Segment::SetPoint1_pos(Vector2 _pos) {
	point1.SetPosition(_pos);
}
void Segment::SetPoint2_pos(Vector2 _pos) {
	point2.SetPosition(_pos);
}
ID Segment::GetPoint1_ID() const {
	return point1.GetId();
}
ID Segment::GetPoint2_ID() const {
	return point2.GetId();
}

Arc::Arc(double p1x, double p1y, double p2x, double p2y, double _angle) :
	Primitive(IDGenerator::getInstance()->generateID(),
		Type(arc)),
	point1(Point(p1x, p1y)),
	point2(Point(p2x, p2y))
{
	angle = _angle;
}

Arc::Arc(Vector2 _point1, Vector2 _point2, double _angle) :
	Primitive(IDGenerator::getInstance()->generateID(),
		Type(arc)),
	point1(Point(_point1)),
	point2(Point(_point2))
{
	angle = _angle;
}
double Segment::GetDistance(Vector2 point) {
	double dotProduct1 = 0.0;
	double dotProduct2 = 0.0;
	Vector2 point1 = this->point1.GetPosition();
	Vector2 point2 = this->point2.GetPosition();

	Vector2 pointTo1 = point - point1;
	Vector2 pointTo2 = point - point2;
	Vector2 segment = point2 - point1;
	dotProduct1 = Vector2::Dot(pointTo1, segment);
	dotProduct2 = Vector2::Dot(pointTo2, segment);
	dotProduct2 *= -1;
	double answer = 0;
	if (dotProduct1 >= 0 && dotProduct2 >= 0) {
		answer = pointTo1.x * segment.y - pointTo1.y * segment.x;
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

double Arc::GetDistance(Vector2) {
	return 0.0;
}

Vector2 Arc::GetCenter() const {
	Vector2 point1Pos = point1.GetPosition();
	Vector2 point2Pos = point2.GetPosition();

	Vector2 base = point2Pos - point1Pos;
	Vector2 halfBase = base * 0.5;
	double tempValue = sqrt(base.x * base.x - base.y * base.y);
	Vector2 N(-base.y, base.x);
	double H = halfBase.GetLength() / tan(angle / 2.0);
	N = N * (1.0 / tempValue * H);

	Vector2 H1 = point1.GetPosition() + halfBase + N;
	Vector2 H2 = point1.GetPosition() + halfBase + N;

	Vector2 H1toPoint1 = point1.GetPosition() - H1;
	Vector2 H1toPoint2 = point2.GetPosition() - H1;

	return (Vector2::Cross(H1toPoint1, H1toPoint2) > 0) ? H1 : H2;
}

ID Arc::GetPoint1_ID() const {
	return point1.GetId();
}
ID Arc::GetPoint2_ID() const {
	return point2.GetId();
}
Vector2 Arc::GetPoint1_pos() const {
	return point1.GetPosition();
}
Vector2 Arc::GetPoint2_pos() const {
	return point2.GetPosition();
}
void Arc::SetPoint1_pos(Vector2 _pos) {
	point1.SetPosition(_pos);
}
void Arc::SetPoint2_pos(Vector2 _pos) {
	point2.SetPosition(_pos);
}
double Arc::GetAngle() const {
	return angle;
}
