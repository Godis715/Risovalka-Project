#ifndef __VECTOR2
#define __VECTOR2

class Vector2 {
private:

public:

	Vector2(double, double);
	Vector2();
	static double Dot(Vector2, Vector2);
	static double Cross(Vector2, Vector2);
	Vector2 operator -(const Vector2&);
	Vector2 operator +(const Vector2&);
	Vector2 operator *(double);
	double GetLength() const;

	double x;
	double y;
};

#endif