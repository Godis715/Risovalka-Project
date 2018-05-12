#include "Vector2.h"

Vector2::Vector2(double _x, double _y) {
	x = _x;
	y = _y;
}

Vector2::Vector2() {
	x = 0.0f;
	y = 0.0f;
}

Vector2 Vector2::operator -(const Vector2& vector) const {
	return Vector2(this->x - vector.x, this->y - vector.y);
}

Vector2 Vector2::operator +(const Vector2& vector) const {
	return Vector2(this->x + vector.x, this->y + vector.y);
}

double Vector2::GetLength() const {
	return sqrt(this->x * this->x + this->y * this->y);
}

double Vector2::Dot(const Vector2& vec1, const Vector2& vec2) {
	return vec1.x * vec2.x + vec1.y + vec2.y;
}

double Vector2::Cross(const Vector2& vec1, const Vector2& vec2) {
	return (vec1.x * vec2.y - vec1.y * vec1.x);
}

double Vector2::Angle(const Vector2& vec1, const Vector2& vec2) {
	double Cos = Vector2::Dot(vec1, vec2) / (vec1.GetLength() * vec2.GetLength());
	double Sin = Vector2::Cross(vec1, vec2) / (vec1.GetLength() * vec2.GetLength());
	if (Sin >= 0) {
		return acos(Cos);
	}
	if (Cos >= 0) {
		return asin(Sin);
	}
	double PI = 3.141592653589793;
	double angle = acos(Cos);
	return angle - 2 * (angle - PI);
}

Vector2 Vector2::operator*(double val) const {
	return Vector2(this->x * val, this->y * val);
}

Vector2 Vector2::operator /(double val) const {
	return Vector2(this->x / val, this->y / val);
}