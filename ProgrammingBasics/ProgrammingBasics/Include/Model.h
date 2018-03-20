#ifndef __MODEL
#define __MODEL

#include "Array.h"
#include "Type.h"
#include <cmath>
#include "IDGenerator.h"


class Primitive;

class Model
{
private:
	static Array<Primitive*> data; //or another container
	static IDGenerator* idGen;
public:
	Model();
	static ID createObject(Type, Array<double>);
	static ID getNearest(double, double);
	static Type getObjType(ID);
	static Array<double> getObjSubs(ID); //?????
	static Array<double> getObjParam(ID);
};

// just pair of numbers
class Vector2 {
private:

public:
	Vector2(double, double);
	Vector2();
	double x;
	double y;
};

// parent of point, segment, arc
class Primitive {
private:
	ID& id;
	Type& type;
public:
	Primitive(ID, Type);
	virtual double GetDistance(Vector2) = 0;
	ID GetId();
	Type GetType();
};

class Point : public Primitive {
private:
	Vector2 position;
public:
	Point(Vector2);
	Point(double, double);
	Point(Point&); //copying constructor
	double GetDistance(Vector2) override;
};

class Segment : public Primitive {
private:
	ID point1;
	ID point2;
public:
	Segment(Vector2, Vector2);
	Segment(double, double, double, double);
	double GetDistance(Vector2) override;
	/*functions for getting and setting coords*/
};

// piece of circle
class Arc : public Primitive {
private:
	Vector2 center;
	Vector2 point1;
	double angle; // from -2pi to 2pi
public: 
	Arc(double, double, double, double, double); //size = sizeof(Arc);
	Arc(Vector2, Vector2, double);
	double GetDistance(Vector2) override;
	/*Vector2 GetPoint1() const;
	Vector2 GetPoint2() const;
	other function for getting/setting
	*/
};



#endif