#include "Primitives.h"
#include <stdexcept>

#define EPS 1e-3
#pragma region someFunc
int sign(double x) {
	if (x > 0) {
		return 1;
	}
	return -1;
}

void line흎uation(double a, double b, double& x1) {
	if (abs(a) < EPS) {
		return;
	}
	x1 = -b / a;
}

void quadro흎uation(double a, double b, double c, double& x1, double &x2) {
	if (abs(a) < EPS) {
		line흎uation(b, c, x1);
		return;
	}
	if (abs(c) < EPS) {
		x2 = 0;
		line흎uation(a, b, x1);
		return;
	}
	double D = b * b - 4 * a * c;
	if (abs(D) < EPS) {
		x1 = -b / (2 * a);
		return;
	}
	if (D > 0) {
		D = sqrt(D);
		x1 = (-b + D) / (2 * a);
		x2 = (-b - D) / (2 * a);
		return;
	}
}

void cubic흎uation(double a, double b, double c, double d, double& x1, double &x2, double &x3) {
	if (abs(a) < EPS) {
		quadro흎uation(b, c, d, x1, x2);
		return;
	}
	if (abs(d) < EPS) {
		x3 = 0;
		quadro흎uation(a, b, c, x1, x2);
		return;
	}
	d = d / a;
	c = c / a;
	a = b / a;
	b = c;
	c = d;
	double Q = (a * a - 3 * b) / 9;
	double R = (2 * a * a * a - 9 * a*b + 27 * c) / 54;
	if (R * R < Q * Q * Q) {
		double t = acos(R / sqrt(Q * Q * Q)) / 3;

		x1 = -2 * sqrt(Q)*cos(t) - a / 3;
		x2 = -2 * sqrt(Q)*cos(t + (2 * PI / 3)) - a / 3;
		x3 = -2 * sqrt(Q)*cos(t - (2 * PI / 3)) - a / 3;
		return;
	}
	double A = -sign(R) * pow(abs(R) + sqrt(R * R - Q * Q * Q), double(1) / 3);
	double B = 0;
	if (abs(A) > EPS) {
		B = Q / A;
	}
	x1 = (A + B) - a / 3;
	return;
}
#pragma endregion

#pragma region Primitive
Primitive::Primitive(object_type _type, const Array<double>& _params, const Array<ID>& _children)
	: Object(_type, _params, children),
	doubleParams(_params.GetSize()),
	isActivated(true)
{
	for (int i = 0; i < doubleParams.GetSize(); ++i) {
		doubleParams[i] = new double(params[i]);
	}
}

Primitive::Primitive(object_type _type, const Array<double>& _params, const Array<Point*>& _children)
	: Object(_type, _params, children),
	doubleParams(_params.GetSize()),
	isActivated(true)
{
	for (int i = 0; i < doubleParams.GetSize(); ++i) {
		doubleParams[i] = new double(params[i]);
	}
}


Primitive::~Primitive() {
	for (int i = 0; i < doubleParams.GetSize(); ++i) {
		delete doubleParams[i];
	}

}

Array<double*> Primitive::GetDoubleParamsAsPointers() {
	return doubleParams;
}

void Primitive::ApplyDoubleParams() {
	for (int i = 0; i < params.GetSize(); ++i) {
		params[i] = *doubleParams[i];
	}
}

bool Primitive::IsActivated() {
	return isActivated;
}
void Primitive::Activate() {
	isActivated = true;
}
void Primitive::Deactivate() {
	isActivated = false;
}

#pragma endregion

#pragma region Point
Point::Point(const Vector2& pos) :
	Primitive(ot_point, CreateArr(pos.x, pos.y), Array<ID>(0))
{
	this->x = &params[0];
	this->y = &params[1];
}
Point::Point(double _x, double _y) :
	Primitive(ot_point, CreateArr(_x, _y), Array<ID>(0))
{
	this->x = &params[0];
	this->y = &params[1];
}
Point::Point(const Point& _p) :
	Primitive(ot_point, CreateArr(*_p.x, *_p.y), Array<ID>(0))
{
	this->x = &params[0];
	this->y = &params[1];
}
double Point::GetDist(const Vector2& point) const {
	return sqrt((*x - point.x)*(*x - point.x) +
		(*y - point.y)*(*y - point.y));
}
Vector2 Point::GetPos() const {
	return Vector2(*x, *y);
}
void Point::SetPos(const Vector2& _pos) {
	*x = _pos.x;
	*y = _pos.y;
}
void Point::SetPos(double _x, double _y) {
	*x = _x;
	*y = _y;
}
#pragma endregion

#pragma region Segment
Segment::Segment(Point* _p1, Point* _p2) :
	Primitive(ot_segment, Array<double>(0), CreateArr(_p1->GetID(), _p2->GetID()))
{
	if (_p1 == nullptr || _p2 == nullptr) {
		throw std::invalid_argument("Segment::Segment::parameters was nullptr");
	}

	point1 = _p1;
	point2 = _p2;
}
double Segment::GetLength() const {
	return (point1->GetPos() - point2->GetPos()).GetLength();
}
Vector2 Segment::GetPointPos1() const {
	return point1->GetPos();
}
Vector2 Segment::GetPointPos2() const {
	return point2->GetPos();
}
void Segment::SetPointPos1(const Vector2& _pos) {
	point1->SetPos(_pos);
}
void Segment::SetPointPos2(const Vector2& _pos) {
	point2->SetPos(_pos);
}
void Segment::SetPointPos1(const double x, const double y) {
	point1->SetPos(x, y);
}
void Segment::SetPointPos2(const double x, const double y) {
	point2->SetPos(x, y);
}
ID Segment::GetPointID1() const {
	return point1->GetID();
}
ID Segment::GetPointID2() const {
	return point2->GetID();
}
double Segment::Inequality(Vector2 vector) {
	Equation* equation = this->CreateEquation();
	double answer = equation->a * vector.x + equation->b * vector.y + equation->c;
	delete equation;
	return answer;
}
double Segment::GetDist(const Vector2& point) const {
	double dotProduct1 = 0.0;
	double dotProduct2 = 0.0;
	Vector2 point1 = this->point1->GetPos();
	Vector2 point2 = this->point2->GetPos();

	Vector2 pointTo1 = point - point1;
	Vector2 pointTo2 = point - point2;
	Vector2 segment = point2 - point1;
	dotProduct1 = Vector2::Dot(pointTo1, segment);
	dotProduct2 = Vector2::Dot(pointTo2, segment);
	dotProduct2 *= -1;
	double answer = 0;
	if (dotProduct1 >= 0 && dotProduct2 >= 0) {
		answer = abs(Vector2::Cross(pointTo1, segment));
		answer /= 2;
		answer /= segment.GetLength();
	}
	else {
		answer = pointTo1.GetLength();
		if (answer > pointTo2.GetLength()) {
			answer = pointTo2.GetLength();
		}
	}
	return answer;
}
#pragma endregion

#pragma region Arc
Arc::Arc(Point* _p1, Point* _p2, double _angle) :
	Primitive(ot_arc, CreateArr(_angle), CreateArr(_p1->GetID(), _p2->GetID()))
{
	if (_p1 == nullptr || _p2 == nullptr) {
		throw std::invalid_argument("Arc::Arc::parameters was nullptr");
	}

	point1 = _p1;
	point2 = _p2;

	angle = &params[0];
	RestoreCenter();
}

// write this function
double Arc::GetDist(const Vector2& _point) const {
	Vector2 center(cx, cy);
	Vector2 r1 = point1->GetPos() - center;
	Vector2 r2 = point2->GetPos() - center;
	Vector2 vec = _point - center;

	bool inSector = true;

	double cross1 = Vector2::Cross(r1, vec);
	double cross2 = Vector2::Cross(vec, r2);

	if (*angle < PI) {
		inSector = (cross1 > 0 && cross2 > 0);
	}
	else {
		inSector = (cross1 > 0 || cross2 > 0);
	}
	if (inSector) {
		return abs(vec.GetLength() - r1.GetLength());
	}
	else {
		double dist1 = (r1 - vec).GetLength();
		double dist2 = (r2 - vec).GetLength();
		return (dist1 > dist2) ? dist1 : dist2;
	}
}

Vector2 Arc::GetCenter() const {
	return Vector2(cx, cy);
}

void Arc::RestoreCenter() {
	Vector2 center;
	Vector2 point1Pos = point1->GetPos();
	Vector2 point2Pos = point2->GetPos();

	Vector2 base = point2Pos - point1Pos;
	double baseLength = base.GetLength();

	double H = (baseLength / 2.0) / tan(*angle / 2.0);

	Vector2 ortH(-base.y / baseLength, base.x / baseLength);
	Vector2 midBase = (point1Pos + point2Pos) / 2.0;

	center = midBase + (ortH * H);

	point1Pos = point1Pos - center;
	point2Pos = point2Pos - center;

	if (Vector2::Cross(point1Pos, point2Pos) * (*angle - PI) > 0) {
		center = midBase - (ortH * H);
	}
	cx = center.x;
	cy = center.y;
}

ID Arc::GetPointID1() const {
	return point1->GetID();
}
ID Arc::GetPointID2() const {
	return point2->GetID();
}
Vector2 Arc::GetPointPos1() const {
	return point1->GetPos();
}
Vector2 Arc::GetPointPos2() const {
	return point2->GetPos();
}
void Arc::SetPointPos1(const Vector2& _pos) {
	point1->SetPos(_pos);
}
void Arc::SetPointPos2(const Vector2& _pos) {
	point2->SetPos(_pos);
}
void Arc::SetPointPos1(const double x, const double y) {
	point1->SetPos(x, y);
}
void Arc::SetPointPos2(const double x, const double y) {
	point2->SetPos(x, y);
}
double Arc::GetAngle() const {
	return *angle;
}

void Arc::SetAngle(double newAngle) {
	if (newAngle > 2 * PI) {
		*angle = newAngle - (double)(int)(newAngle / (2 * PI)) * 2 * PI;
		return;
	}
	if (newAngle < 0.0) {
		*angle = newAngle + ((double)((int)(abs(newAngle) / (2 * PI)) + 1) * 2 * PI);
		return;
	}
	*angle = newAngle;
}
#pragma endregion

#pragma region Circle
Circle::Circle(Point* _center,  double _radius) :
	Primitive(ot_circle, CreateArr(_radius), CreateArr(_center->GetID()))
{
	if (_center == nullptr) {
		throw std::invalid_argument("Circle::Circle::_center was nullptr");
	}
	if (_radius < 0) {
		throw std::invalid_argument("Circle::Circle::_radius was negative");
	}

	center = _center;

	radius = &params[0];
}

// write this function
double Circle::GetDist(const Vector2& _point) const {
	return abs(*radius - (_point - Vector2(center->GetPos().x, center->GetPos().y)).GetLength());
}

Vector2 Circle::GetCenter() const {
	return center->GetPos();
}

ID Circle::GetCenterID() const {
	return children[0];
}

void Circle::SetCenterPos(const Vector2& _pos) {
	center->SetPos(_pos);
}
void Circle::SetCenterPos(const double x, const double y) {
	center->SetPos(x, y);
}

double Circle::GetRadius() const {
	return *radius;
}

void Circle::SetRadius(const double _radius)
{
	*radius = _radius;
}
#pragma endregion

#pragma region Curve
Curve::Curve(const Array<Point*>& _points, const Array<double>& _controlPoints) :
	Primitive(ot_curve, 0, _points), coefControls_1(_points.GetSize() - 1),
	coefControls_2(_points.GetSize() - 1), orts(_points.GetSize())
{
	points = _points;
	
	int index = 0;
	for (size_t i = 0; i < points.GetSize(); i++)
	{
		if (i == 0)
		{
			Vector2 controlPoint = Vector2(_controlPoints[index], _controlPoints[index + 1]);
			orts[i] = (controlPoint - points[i]->GetPos()).Normalized();
			coefControls_2[i] = (controlPoint - points[i]->GetPos()).GetLength();
			index += 2;

		}
		else if (i == points.GetSize() - 1)
		{
			Vector2 controlPoint = Vector2(_controlPoints[index], _controlPoints[index + 1]);
			orts[i] = (controlPoint - points[i]->GetPos()).Normalized();
			coefControls_1[i - 1] = (controlPoint - points[i]->GetPos()).GetLength();
		}
		else
		{
			Vector2 controlPoint = Vector2(_controlPoints[index], _controlPoints[index + 1]);
			orts[i] = (controlPoint - points[i]->GetPos()).Normalized();
			coefControls_1[i - 1] = (controlPoint - points[i]->GetPos()).GetLength();
			coefControls_2[i] = coefControls_1[i - 1] * -1;
			index += 4;
		}
	}
}

Vector2 Curve::GetPoint(const Vector2& P0, const Vector2& P1,
	const Vector2& P2, const Vector2& P3, const double t) const {
	double t1 = 1 - t;
	Vector2 result =   P0 * t1 * t1 * t1;
	result += P1 * t1 * t1 * t * 3;
	result += P2 * t1 * t * t * 3;
	result += P3 * t * t * t;
	return result;
}

double Curve::GetDist(const Vector2& click) const {
	Vector2 P0;
	Vector2 P1;
	Vector2 P2;
	Vector2 P3;
	double dist = DBL_MAX;
	for (int i = 0; i < points.GetSize() - 1; ++i) {
		P0 = points[i]->GetPos();
		P1 = orts[i] * coefControls_2[i] + points[i]->GetPos();
		P2 = orts[i + 1] * coefControls_1[i] + points[i + 1]->GetPos();
		P3 = points[i + 1]->GetPos();
		if (click.x < P0.x - SEARCHING_AREA && click.x < P1.x - SEARCHING_AREA &&
			click.x < P2.x - SEARCHING_AREA && click.x < P3.x - SEARCHING_AREA) {
			continue;
		}
		if (click.x > P0.x + SEARCHING_AREA && click.x > P1.x + SEARCHING_AREA &&
			click.x > P2.x + SEARCHING_AREA && click.x > P3.x + SEARCHING_AREA) {
			continue;
		}
		if (click.y < P0.y - SEARCHING_AREA && click.y < P1.y - SEARCHING_AREA &&
			click.y < P2.y - SEARCHING_AREA && click.y < P3.y - SEARCHING_AREA) {
			continue;
		}
		if (click.y > P0.y + SEARCHING_AREA && click.y > P1.y + SEARCHING_AREA &&
			click.y > P2.y + SEARCHING_AREA && click.y > P3.y + SEARCHING_AREA) {
			continue;
		}

		double tx[] = { DBL_MIN, DBL_MIN , DBL_MIN };
		double ty[] = { DBL_MIN, DBL_MIN , DBL_MIN };
		size_t countSolution = 3;
		double Ax = (-P0.x + 3 * P1.x - 3 * P2.x + P3.x);
		double Bx = (3 * P0.x - 6 * P1.x + 3 * P2.x);
		double Cx = (-3 * P0.x + 3 * P1.x);
		double Dx = (P0.x - click.x);

		double Ay = (-P0.y + 3 * P1.y - 3 * P2.y + P3.y);
		double By = (3 * P0.y - 6 * P1.y + 3 * P2.y);
		double Cy = (-3 * P0.y + 3 * P1.y);
		double Dy = (P0.y - click.y);
		cubic흎uation(Ax, Bx, Cx, Dx, tx[0], tx[1], tx[2]);
		cubic흎uation(Ay, By, Cy, Dy, ty[0], ty[1], ty[2]);
		
		for (int i = 0; i < countSolution; ++i) {
			if (ty[i] > -EPS && ty[i] < 1 + EPS) {
				Vector2 Y = GetPoint(P0, P1, P2, P3, ty[i]) - click;
				double dot = Vector2::Dot(Y, Y);
				if (dist > dot) {
					dist = dot;
				}
			}
		}
		for (int i = 0; i < countSolution; ++i) {
			if (tx[i] > -EPS && tx[i] < 1 + EPS) {
				Vector2 X = GetPoint(P0, P1, P2, P3, tx[i]) - click;
				double dot = Vector2::Dot(X, X);
				if (dist > dot) {
					dist = dot;
				}
			}
		}
	}
	return sqrt(dist);
}

Array<ID> Curve::GetPointIDs() const {
	Array<ID> result = Array<ID>(points.GetSize());
	for (int i = 0; i < points.GetSize(); ++i) {
		result[i] = points[i]->GetID();
	}
	return result;
}
Array<Vector2> Curve::GetPointPositions() const {
	Array<Vector2> result = Array<Vector2>(points.GetSize());
	for (int i = 0; i < points.GetSize(); ++i) {
		result[i] = points[i]->GetPos();
	}
	return result;
}
Array<double> Curve::GetPointDoubles() const {
	Array<double> result = Array<double>(points.GetSize() * 6 - 4);
	int index = 0;
	double t = 0;
	for (size_t i = 0; i < points.GetSize(); i++)
	{
		if (i == 0)
		{
			result[index++] = points[i]->GetPos().x;
			result[index++] = points[i]->GetPos().y;
			result[index++] = orts[i].x * coefControls_2[i] + points[i]->GetPos().x;
			result[index++] = orts[i].y * coefControls_2[i] + points[i]->GetPos().y;
		}
		else if (i == points.GetSize() - 1)
		{
			result[index++] = orts[i].x * coefControls_1[i - 1] + points[i]->GetPos().x;
			result[index++] = orts[i].y * coefControls_1[i - 1] + points[i]->GetPos().y;
			result[index++] = points[i]->GetPos().x;
			result[index++] = points[i]->GetPos().y;
		}
		else
		{
			result[index++] = orts[i].x * coefControls_1[i - 1] + points[i]->GetPos().x;
			result[index++] = orts[i].y * coefControls_1[i - 1] + points[i]->GetPos().y;
			result[index++] = points[i]->GetPos().x;
			result[index++] = points[i]->GetPos().y;
			result[index++] = orts[i].x * coefControls_2[i] + points[i]->GetPos().x;
			result[index++] = orts[i].y * coefControls_2[i] + points[i]->GetPos().y;
		}
	}
	return result;
}
void Curve::SetPointPositions(const Array<Vector2>& vectors) {
	if (vectors.GetSize() != points.GetSize()) {
		throw std::invalid_argument("Curve::invalid size");
	}
	for (int i = 0; i < points.GetSize(); ++i) {
		points[i]->SetPos(vectors[i]);
	}
}
void Curve::SetPointPositions(const Array<double> params) {
	if (params.GetSize() != points.GetSize() * 2) {
		throw std::invalid_argument("Curve::invalid size");
	}
	for (int i = 0; i < points.GetSize(); ++i) {
		points[i]->SetPos(params[2 * i ], params[2 * i + 1]);
	}
}
#pragma endregion