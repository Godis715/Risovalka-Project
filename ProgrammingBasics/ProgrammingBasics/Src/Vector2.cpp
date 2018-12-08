#include "Vector2.h"

using namespace DrawProject;

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

Vector2 Vector2::Normalized() const {
	double len = sqrt(this->x * this->x + this->y * this->y);
	if (len < 0.0001) {
		return Vector2(0, 0);
	}
	return Vector2(this->x / len, this->y / len);
};

double Vector2::Dot(const Vector2& vec1, const Vector2& vec2) {
	return (vec1.x * vec2.x + vec1.y * vec2.y);
}

double Vector2::Cross(const Vector2& vec1, const Vector2& vec2) {
	return -(vec1.x * vec2.y - vec1.y * vec2.x);
}

double Vector2::Angle(const Vector2& vec1, const Vector2& vec2) {

	double angle = acos(Vector2::Dot(vec1, vec2) / (vec1.GetLength() * vec2.GetLength()));
	if (Vector2::Cross(vec1, vec2) >= 0) {
		return angle;
	}
	else {
		return PI * 2 - angle;
	}
}

Vector2 Vector2::operator*(const double val) const {
	return Vector2(this->x * val, this->y * val);
}

Vector2 Vector2::operator /(const double val) const {
	return Vector2(this->x / val, this->y / val);
}

void Vector2::operator /=(const double val) {
	this->x /= val;
	this->y /= val;
}

void Vector2::operator +=(const Vector2& vector) {
	this->x += vector.x;
	this->y += vector.y;
}

void Vector2::operator *=(const double val) {
	this->x *= val;
	this->y *= val;
}

void Vector2::operator =(const Vector2& vector) {
	this->x = vector.x;
	this->y = vector.y;
}