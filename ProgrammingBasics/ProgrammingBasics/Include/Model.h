#ifndef __MODEL
#define __MODEL

#include "Array.h"
#include "ID.h"
#include "Type.h"
#include <cmath>

class Primitive;

class Model
{
private:
	Array<Primitive> data; //or another container

public:
	Model();
	ID createObject(Type, Array<double>);
	ID getNearest(double, double);
	Type getObjType(ID);
	Array<double> getObjSubs(ID); //?????
	Array<double> getObjParam(ID);
};

// just pair of numbers
class Vector2 {
private:

public:
	Vector2(float, float);
	Vector2();
	float x;
	float y;
};

Vector2::Vector2(float _x, float _y) {
	x = _x;
	y = _y;
}
Vector2::Vector2() {
	x = 0.0f;
	y = 0.0f;
}

// parent of point, segment, arc
class Primitive {
private:
	ID& id;
	Type& type;
public:
	Primitive(ID, Type);
	virtual float GetDistance() = 0;
	ID GetId();
	Type GetType();
};

ID Primitive::GetId() {
	return id;
}

Primitive::Primitive(ID _id, Type _type) : id(_id), type(_type) {

}
Type Primitive::GetType() {
	return type;
}


class Point : public Primitive {
private:
	Vector2 position;
public:
	Point(Vector2);
	Point(float, float);
	Point(Point&); //copying constructor
	float GetDistance() override;
};

Point::Point(Vector2 pos) : Primitive(ID((int)this), Type(point)) {
	this->position = pos;
}
Point::Point(float _x, float _y) : Primitive(ID((int)this), Type(point)) {
	this->position = Vector2(_x, _y);
}
Point::Point(Point& _p) : Primitive(ID((int)this), Type(point)) {
	this->position = _p.position;
}

/* class Segment : public Primitive {
private:
	Point& point1;
	//pointers??
	Point& point2;
public:
	Segment(float, float, float, float);
	Segment(Point, Point); // nuz
	//Segment(Point*, Point*);
	float GetDistance() override;
};

Segment::Segment(float x1, float y1, float x2, float y2) :
	point1(Point(x1, y1)),
	point2(Point(x2, y2)),
	Primitive(ID((int)this), Type(segment))
{

}
Segment::Segment(Point _p1, Point _p2) :
	point1(_p1),
	point2(_p2),
	Primitive(ID((int)this), Type(segment))
{

} */

class Segment : public Primitive {
private:
	Vector2 point1;
	Vector2 point2;
public:
	Segment(Vector2, Vector2);
	Segment(float, float, float, float);
	float GetDistance() override;
	/*functions for getting and setting coords*/
};

Segment::Segment(Vector2 _p1, Vector2 _p2) : Primitive(ID((int)this), Type(segment)) {
	point1 = _p1;
	point2 = _p2;
}

Segment::Segment(float x1, float y1, float x2, float y2) : Primitive(ID((int)this), Type(segment)) {
	point1 = Vector2(x1, y1);
	point2 = Vector2(x2, y2);
}


// piece of circle
class Arc : public Primitive {
private:
	Vector2 center;
	Vector2 point1;
	float angle; // from -2pi to 2pi
public: 
	Arc(float, float, float, float, float); //size = sizeof(Arc);
	Arc(Vector2, Vector2, float);
	float GetDistance() override;
	/*Vector2 GetPoint1() const;
	Vector2 GetPoint2() const;
	other function for getting/setting
	*/
};

Arc::Arc(float cx, float cy, float px, float py, float _angle) : Primitive(ID((int)this), Type(arc)) {
	center = Vector2(cx, cy);
	point1 = Vector2(px, py);
	angle = _angle;
}

Arc::Arc(Vector2 _center, Vector2 _point1, float _angle) : Primitive(ID((int)this), Type(arc)) {
	center = _center;
	point1 = _point1;
	angle = _angle;
}

#endif