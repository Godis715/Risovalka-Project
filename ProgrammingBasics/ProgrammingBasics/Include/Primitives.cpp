#include "Primitives.h"

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
	Primitive(IDGenerator::getInstance()->generateID(), point_t)
{
	this->parent = nullptr;
	this->position = pos;
}
Point::Point(double _x, double _y) :
	Primitive(IDGenerator::getInstance()->generateID(), point_t)
{
	this->parent = nullptr;
	this->position = Vector2(_x, _y);
}
Point::Point(const Point& _p) :
	Primitive(IDGenerator::getInstance()->generateID(), point_t)
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


Segment::Segment(Point* _p1, Point* _p2) :
	Primitive(IDGenerator::getInstance()->generateID(), segment_t)
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

Arc::Arc(Point* _p1, Point* _p2, double _angle) :
	Primitive(IDGenerator::getInstance()->generateID(), arc_t)
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
	return 0.0;
}
Vector2 Arc::GetCenter() const {
	Vector2 point1Pos = point1->GetPosition();
	Vector2 point2Pos = point2->GetPosition();

	Vector2 base = point2Pos - point1Pos;
	Vector2 halfBase = base * 0.5;
	double tempValue = sqrt(base.x * base.x - base.y * base.y);
	Vector2 N(-base.y, base.x);
	double H = halfBase.GetLength() / tan(angle / 2.0);
	N = N * (1.0 / tempValue * H);

	Vector2 H1 = point1->GetPosition() + halfBase + N;
	Vector2 H2 = point1->GetPosition() + halfBase + N;

	Vector2 H1toPoint1 = point1->GetPosition() - H1;
	Vector2 H1toPoint2 = point2->GetPosition() - H1;

	return (Vector2::Cross(H1toPoint1, H1toPoint2) > 0) ? H1 : H2;
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

Primitive* Point::GetParent() {
	return parent;
}

bool Point::SetParent(Primitive* _parent) {
	if (parent != nullptr || _parent == nullptr) {
		return false;
	}
	parent = _parent;
}