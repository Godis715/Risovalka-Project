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
	Array<Primitive*> data; //or another container
	IDGenerator* idGen;
public:
	Model();
	ID createObject(Type, Array<double>);
	ID getNearest(double, double);
	bool getNearest(double, double, ID&);
	Type getObjType(ID);
	Array<double> getObjSubs(ID); //?????
	Array<double> getObjParam(ID);
};

// just pair of numbers
class Vector2 {
private:

public:
	Vector2(double, double);
	Vector2();
	static double Dot(Vector2, Vector2);
	double x;
	double y;
	Vector2 operator -(Vector2&);
	double GetLength();
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
	Vector2 GetPosition() const;
	void SetPosition(Vector2);
	void SetPosition(double, double);
};

class Segment : public Primitive {
private:
	Point& point1;
	Point& point2;
public:
	Segment(Vector2, Vector2);
	Segment(double, double, double, double);
	double GetDistance(Vector2) override;
	ID GetPoint1_ID() const;
	ID GetPoint2_ID() const;
	Vector2 GetPoint1_pos() const;
	Vector2 GetPoint2_pos() const;
	void SetPoint1_pos(Vector2);
	void SetPoint2_pos(Vector2);

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