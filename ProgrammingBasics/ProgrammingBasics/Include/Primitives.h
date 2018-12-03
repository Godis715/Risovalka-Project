#ifndef __PRIMITIVES
#define __PRIMITIVES

#include "Vector2.h"
#include "ID.h"

#define VERTEX		1
#define CENTER		2
#define ANGLE		3
#define RADIUS		4
#define CURVE_AS_IT_IS		5
#define CURVE_PARAMS		6
#define SEARCHING_AREA 5.0
#define EPS 1e-3

#define GETVARPARAMS(...) GetVariableObjParam(__VA_ARGS__, 0)
#define SETVARPARAMS(...) SetVariableObjParam(__VA_ARGS__, 0)

int sign(double);
void line≈quation(double, double, double&);
void quadro≈quation(double, double, double, double&, double&);
void cubicEquotion(double, double, double, double, double&, double&, double&);
Vector2 GetPoint(const Vector2&, const Vector2&, const Vector2&, const Vector2&, const double);

class Primitive;
class Arc;
class Point;
class Segment;
class Circle;
class Curve;

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

	bool IsActivated(const ID&) const;

	Array<double> GetPrimitiveParamsAsValues(const ID&) const;
	Array<double> GetPrimParamsForDrawing(const ID&) const;

	Array<double> GetVariableObjParam(const ID&, int...) const;
	Array<double> GetVariableObjParam(const ID&, int[]) const;

	void SetVariableObjParam(const ID&, const Array<double>&, int...) const;
	void SetVariableObjParam(const ID&, const Array<double>&, int[]) const;


	Array<double*> GetPrimitiveParamsAsPointers(const ID&) const;
	Array<double*> GetPrimitiveParamsAsPointers(const Array<ID>&, int) const;

	Array<double*> GetPrimitiveDoubleParamsAsPointers(const ID&) const;
	//Array<double*> GetPrimitiveDoubleParamsAsPointers(const Array<ID>&, int) const;
	
	void ApplyPrimitiveDoubleParams(const ID&) const;

	void SetPrimitiveParams(const ID&, const Array<double>&) const;

	void Activate(const ID&) const;

	void Deactivate(const ID&) const;

	ID CreatePrimitive(object_type, const Array<ID>&, const Array<double>&) const;
	

	Array<ID> GetChildren(const ID&) const;

	double GetDistanceToPoint(const ID&, double, double) const;
};

class Primitive : public Object {
private:
	Array<double*> doubleParams;

	bool isActivated;
public:
	Primitive(object_type, const Array<double>&, const Array<ID>&);
	Primitive(object_type, const Array<double>&, const Array<Point*>&);
	virtual ~Primitive();
	virtual double GetDist(const Vector2&) const = 0;
	bool IsActivated();
	void Activate();
	void Deactivate();
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
	void SetPointPos1(const Vector2&);
	void SetPointPos2(const Vector2&);
	void SetPointPos1(const double, const double);
	void SetPointPos2(const double, const double);
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
	void SetPointPos1(const Vector2&);
	void SetPointPos2(const Vector2&);
	void SetPointPos1(const double, const double);
	void SetPointPos2(const double, const double);
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
	void SetCenterPos(const Vector2&);
	void SetCenterPos(const double, const double);
	double GetRadius() const;
	void SetRadius(const double);
	//
};

class Curve : public Primitive {
private:
	Array<Point*> points;
	Array<Vector2> orts;
	Array<double> coefControls_1;
	Array<double> coefControls_2;
	ObjectController* objCtrl;

	friend class PrimController;

	const int GetSize() const ;
public:
	Curve(const Array<Point*>&, const Array<double>&);

	double GetDist(const Vector2&) const;

	Array<ID> GetPointIDs() const;
	Array<Vector2> GetPointPositions() const;
	Array<double> GetPointDoubles() const;
	Array<double> GetCurveAsItIs() const;
	Array<double> GetCurveParams() const;
	void SetCurveAsItIs(const Array<double>&);
	void SetCurveParams(const Array<double>&);

	void AddPoint(const int, Point*, const Array<double>&);
	void DeletePoint(const ID&);
	bool ItISExtremePoint(const ID&) const;
};

#endif