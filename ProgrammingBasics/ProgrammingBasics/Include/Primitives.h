#ifndef __PRIMITIVES
#define __PRIMITIVES

#include "Vector2.h"
#include "ID.h"

class Primitive;
class Arc;
class Point;
class Segment;
class Circle;

class PrimController{
private:
	PrimController();
	static PrimController* instance;

	ObjectController* objCtrl;

	Primitive* ConvertToPrimitive(Object*) const;
public:
	static PrimController* GetInstance();

	Primitive* GetPrimitive(const ID&) const;

	bool IsPrimitive(object_type) const;

	bool IsPrimitive(const ID&) const;

	Array<double> GetPrimitiveParamsAsValues(const ID&) const;

	Array<double*> GetPrimitiveParamsAsPointers(const ID&) const;
	Array<double*> GetPrimitiveParamsAsPointers(const Array<ID>&, int) const;

	Array<double*> GetPrimitiveDoubleParamsAsPointers(const ID&) const;
	Array<double*> GetPrimitiveDoubleParamsAsPointers(const Array<ID>&, int) const;
	
	void ApplyPrimitiveDoubleParams(const ID&) const;

	void SetPrimitiveParams(const ID&, const Array<double>&) const;

	ID CreatePrimitive(object_type, const Array<ID>&, const Array<double>&) const;
	Array<ID> GetChildren(const ID&);

	double GetDistanceToPoint(const ID&, double, double) const;
};

class Primitive : public Object {
private:
	Array<double*> doubleParams;
public:
	Primitive(object_type, const Array<double>&, const Array<ID>&);
	virtual ~Primitive();
	virtual double GetDist(const Vector2&) const = 0;

	Array<double> GetDoubleParamsAsValues();
	Array<double*> GetDoubleParamsAsPointers();

	void ApplyDoubleParams();
};

class Point : public Primitive {
private:
	double* x;
	double* y;

	friend class PrimController;
public:
	Point(const Vector2&);
	Point(double, double);
	Point(const Point&);

	double GetDist(const Vector2&) const;

	Vector2 GetPos() const;
	void SetPos(const Vector2&);
	void SetPos(double, double);
};

class Segment : public Primitive {
private:
	// temp class - move to requirement!!
	class Equation {
	public:
		double a;
		double b;
		double c;
	};
	Equation* CreateEquation() const {
		Equation* NewEquation = new Equation;
		Vector2 vector1 = point1->GetPos();
		Vector2 vector2 = point2->GetPos();
		NewEquation->a = vector1.y - vector2.y;
		NewEquation->b = vector2.x - vector1.x;
		NewEquation->c = vector1.x * vector2.y - vector2.x  * vector1.y;
		return NewEquation;
	}
	//
	friend class PrimController;
public:
	Point* point1;
	Point* point2;

	Segment(Point*, Point*);
	double GetDist(const Vector2&) const;
	double GetLength() const;

	// temp functions
	ID GetPointID1() const;
	ID GetPointID2() const;
	Vector2 GetPointPos1() const;
	Vector2 GetPointPos2() const;
	void SetPointPos1(Vector2);
	void SetPointPos2(Vector2);
	//

	// move to requirement!!!
	double Inequality(Vector2);
};

class Arc : public Primitive {
private:
	double cx;
	double cy;
	double* angle;

	Point* point1;
	Point* point2;

	friend class PrimController;
public:
	Arc(Point*, Point*, double);

	double GetDist(const Vector2&) const;
	void RestoreCenter();
	Vector2 GetCenter() const;

	// temp functions
	ID GetPointID1() const;
	ID GetPointID2() const;
	Vector2 GetPointPos1() const;
	Vector2 GetPointPos2() const;
	void SetPointPos1(Vector2);
	void SetPointPos2(Vector2);
	double GetAngle() const;
	void SetAngle(double);
	//
};

class Circle : public Primitive {
private:

	Point* center;

	double* radius;

	friend class PrimController;
public:
	Circle(Point*, double);

	double GetDist(const Vector2&) const;
	Vector2 GetCenter() const;

	// temp functions
	ID GetCenterID() const;
	void SetCenterPos(Vector2);
	double GetRadius() const;
	void SetRadius(double);
	//
};

#endif