#ifndef __VECTOR2
#define __VECTOR2

#define PI 3.141592653589793 
#include <cmath>

class Vector2 {
private:
public:
	Vector2(double, double);
	Vector2();
	static double Dot(const Vector2&, const Vector2&);
	static double Cross(const Vector2&, const Vector2&);
	static double Angle(const Vector2&, const Vector2&);
	Vector2 operator -(const Vector2&) const;
	Vector2 operator +(const Vector2&) const;
	Vector2 operator *(const double) const;
	Vector2 operator /(const double) const;
	void operator /=(const double);
	void operator +=(const Vector2&);
	void operator *=(const double);
	void operator =(const Vector2&);
	double GetLength() const;
	Vector2 Normalized() const;

	double x;
	double y;
};

#endif