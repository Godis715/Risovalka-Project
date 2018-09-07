#ifndef __PRIMITIVES
#define __PRIMITIVES
#define PI 3.141592653589793 

#include "Vector2.h"

class Primitive : public Object{
private:
public:
	Primitive(object_type);
	virtual double GetDist(const Vector2&) const = 0;
};


class Arc;
class Point;
class Segment;

class PrimController{
private:
	PrimController();
	static PrimController* instance;

	ObjectController* objCtrl;

	Primitive* GetPrimitive(const ID&);
	Primitive* ConvertToPrimitive(Object*);
	bool IsPrimitive(object_type);
public:
	PrimController* GetInstance();

	Array<double*> GetPrimitiveParamsAsPointers(const ID&);
	void SetPrimitiveParams(const ID&, const Array<double>&);

	ID CreatePrimitive(object_type, const Array<double>&);
};

class Point : public Primitive {
private:
	Primitive* parent;

	double x;
	double y;

	friend class PrimController;
public:
	Point(const Vector2&);
	Point(double, double);
	Point(const Point&);

	double GetDist(const Vector2&) const;

	Vector2 GetPos() const;
	void SetPos(const Vector2&);
	void SetPos(double, double);

	Primitive* GetParent();
	void DeleteParent();
	bool SetParent(Primitive*);
	//
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
	double angle;

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
	double radius;
	Point* center;

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

class Requirement : public Object {
private:
protected:
	Array<double*> args;
	Array<double> params;
public:
	// checking type - it must by requirement type
	Requirement(object_type, const Array<double*>&);
	
	virtual double error() = 0;
	virtual void Change(const double);
	virtual void ChangeParams(const Array<double>& newParams) {
		if (newParams.GetSize() != params.GetSize()) {
			throw std::exception("Invalid requirement parameters!");
		}
		params = newParams;
	}
	Array<double> Gradient();
	Array<double*> GetArgs();
};


#endif