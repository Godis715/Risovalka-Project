#include "Model.h"
#include <stdexcept>

Vector2::Vector2(double _x, double _y) {
	x = _x;
	y = _y;
}
Vector2::Vector2() {
	x = 0.0f;
	y = 0.0f;
}

ID Primitive::GetId() {
	return id;
}

Primitive::Primitive(ID _id, Type _type) : id(_id), type(_type) {
	
}
Type Primitive::GetType() {
	return type;
}

Point::Point(Vector2 pos) : Primitive(IDGenerator::getInstance()->generateID(), Type(point)) {
	this->position = pos;
}
Point::Point(double _x, double _y) : Primitive(IDGenerator::getInstance()->generateID(), Type(point)) {
	this->position = Vector2(_x, _y);
}
Point::Point(Point& _p) : Primitive(IDGenerator::getInstance()->generateID(), Type(point)) {
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
	Primitive(IDGenerator::getInstance()->generateID(), Type(segment)),
	point1(Point(_p1)),
	point2(Point(_p2))
{

}

Segment::Segment(double x1, double y1, double x2, double y2) : 
	Primitive(IDGenerator::getInstance()->generateID(), Type(segment)),
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
Vector2 Segment::SetPoint1_pos(Vector2 _pos) {
	point1.SetPosition(_pos);
}
Vector2 Segment::SetPoint2_pos(Vector2 _pos) {
	point2.SetPosition(_pos);
}
ID Segment::GetPoint1_ID() const {
	return point1.GetId();
}
ID Segment::GetPoint2_ID() const {
	return point2.GetId();
}

Arc::Arc(double cx, double cy, double px, double py, double _angle) : Primitive(IDGenerator::getInstance()->generateID(), Type(arc)) {
	center = Vector2(cx, cy);
	point1 = Vector2(px, py);
	angle = _angle;
}

Arc::Arc(Vector2 _center, Vector2 _point1, double _angle) : Primitive(IDGenerator::getInstance()->generateID(), Type(arc)) {
	center = _center;
	point1 = _point1;
	angle = _angle;
}

ID Model::createObject(Type T, Array<double> params) {
	switch (T.GetTypeId())
	{
	case point: {
		Point* _point;
		try {
			_point = new Point(params[0], params[1]);
		}
		catch (std::out_of_range) {
			throw std::invalid_argument("Invalid parameters");
		}
		data.pushBack(_point);
		return _point->GetId();
		break;
	}
	case segment: {
		Point* _point = new Point(params.popBack(), params.popBack());
		data.pushBack(_point);
		return _point->GetId();
		break;
	}
	default:
		break;
	}
	
}