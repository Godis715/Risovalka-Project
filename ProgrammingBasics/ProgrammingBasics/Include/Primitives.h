#ifndef __PRIMITIVES
#define __PRIMITIVES
#define PI 3.141592653589793 
#include "List.h"
#include "Array.h"
#include "Vector2.h"
#include "IDgenerator.h"
#include "Type.h"

class Primitive {
private:
	const ID id;
	const type_id type;
public:
	Primitive(ID, type_id);
	virtual double GetDistance(Vector2) const = 0;
	ID GetID() const;
	type_id GetType();
};

class Point : public Primitive {
private:
public:

	Vector2 position;

	Point(Vector2);
	Point(double, double);
	Point(const Point&);

	double GetDistance(Vector2) const override;
	Vector2 GetPosition() const;
	void SetPosition(Vector2);
	void SetPosition(double, double);
};

class Segment : public Primitive {
private:

	class Equation {
	public:
		double a;
		double b;
		double c;
	};
	Equation* CreateEquation() {
		Equation* NewEquation = new Equation;
		Vector2 vector1 = point1->GetPosition();
		Vector2 vector2 = point2->GetPosition();
		NewEquation->a = vector1.y - vector2.y;
		NewEquation->b = vector2.x - vector1.x;
		NewEquation->c = vector1.x * vector2.y - vector2.x  * vector1.y;
		return NewEquation;
	}

public:

	Point* point1;
	Point* point2;

	Segment(Point*, Point*);
	double GetDistance(Vector2) const;
	double GetLength() const;
	ID GetPoint1_ID() const;
	ID GetPoint2_ID() const;
	Vector2 GetPoint1_pos() const;
	Vector2 GetPoint2_pos() const;
	void SetPoint1_pos(Vector2);
	void SetPoint2_pos(Vector2);

	double Inequality(Vector2);
};

class Arc : public Primitive {
private:
	Point* point1;
	Point* point2;
public:
	double angle; // from 0 to 2pi
	Arc(Point*, Point*, double);
	double GetDistance(Vector2) const;
	Vector2 GetCenter() const;
	ID GetPoint1_ID() const;
	ID GetPoint2_ID() const;
	Vector2 GetPoint1_pos() const;
	Vector2 GetPoint2_pos() const;
	void SetPoint1_pos(Vector2);
	void SetPoint2_pos(Vector2);
	double GetAngle() const;
	void SetAngle(double);
};

#endif