#ifndef __PRIMITIVES
#define __PRIMITIVES

#include "Vector2.h"
#include "IDgenerator.h"
#include "Type.h"

class Primitive {
private:
	ID& id;
	//Type& type;
	const type_id type;
public:
	Primitive(ID, type_id);
	virtual double GetDistance(Vector2) const = 0;
	ID GetId() const;
	type_id GetType();
};

class Point : public Primitive {
private:
	Vector2 position;
public:
	Point(Vector2);
	Point(double, double);
	Point(const Point&); //copying constructor
	double GetDistance(Vector2) const override;
	Vector2 GetPosition() const;
	void SetPosition(Vector2);
	void SetPosition(double, double);
};

class Segment : public Primitive {
private:
	Point point1;
	Point point2;

	class Equation {
	public:
		double a;
		double b;
		double c;
	};

	Equation* CreateEquation() {
		Equation* NewEquation = new Equation;
		Vector2 vector1 = point1.GetPosition();
		Vector2 vector2 = point2.GetPosition();
		NewEquation->a = vector1.y - vector2.y;
		NewEquation->b = vector2.x - vector1.x;
		NewEquation->c = vector1.x * vector2.y - vector2.x  * vector1.y;
		return NewEquation;
	}
public:
	Segment(Vector2, Vector2);
	Segment(double, double, double, double);
	double GetDistance(Vector2) const override;
	ID GetPoint1_ID() const;
	ID GetPoint2_ID() const;
	Vector2 GetPoint1_pos() const;
	Vector2 GetPoint2_pos() const;
	void SetPoint1_pos(Vector2);
	void SetPoint2_pos(Vector2);

	double Inequality(Vector2);
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
	double GetDistance(Vector2) const override;
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