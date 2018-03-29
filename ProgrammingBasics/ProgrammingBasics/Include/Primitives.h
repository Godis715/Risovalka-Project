#ifndef __PRIMITIVES
#define __PRIMITIVES

#include "Vector2.h"
#include "IDgenerator.h"
#include "Type.h"

class Primitive {
private:
	ID& id;
	Type& type;
public:
	Primitive(ID, Type);
	virtual double GetDistance(Vector2) = 0;
	ID GetId() const;
	Type GetType();
};

class Point : public Primitive {
private:
	Vector2 position;
public:
	Point(Vector2);
	Point(double, double);
	Point(const Point&); //copying constructor
	double GetDistance(Vector2) override;
	Vector2 GetPosition() const;
	void SetPosition(Vector2);
	void SetPosition(double, double);
};

class Segment : public Primitive {
private:
	Point point1;
	Point point2;
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
	Point point1;
	Point point2;
	double angle; // from 0 to 2pi
public:
	Arc(double, double, double, double, double); //size = sizeof(Arc);
	Arc(Vector2, Vector2, double);
	double GetDistance(Vector2) override;
	Vector2 GetCenter() const;
	ID GetPoint1_ID() const;
	ID GetPoint2_ID() const;
	Vector2 GetPoint1_pos() const;
	Vector2 GetPoint2_pos() const;
	void SetPoint1_pos(Vector2);
	void SetPoint2_pos(Vector2);
	double GetAngle() const;
	/*Vector2 GetPoint1() const;
	Vector2 GetPoint2() const;
	other function for getting/setting
	*/
};

#endif