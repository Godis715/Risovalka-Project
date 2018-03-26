#include "Vector2.h"
#include <cmath>

Vector2::Vector2(double _x, double _y) {
	x = _x;
	y = _y;
}

Vector2::Vector2() {
	x = 0.0f;
	y = 0.0f;
}

Vector2 Vector2::operator -(const Vector2& vector) {
	return Vector2(this->x - vector.x, this->y - vector.y);
}

Vector2 Vector2::operator +(const Vector2& vector) {
	return Vector2(this->x + vector.x, this->y + vector.y);
}

double Vector2::GetLength() {
	return sqrt(this->x * this->x + this->y * this->y);
}

double Vector2::Dot(Vector2 vec1, Vector2 vec2) {
	return vec1.x * vec2.x + vec1.y + vec2.y;
}

double Vector2::Cross(Vector2 vec1, Vector2 vec2) {
	return (vec1.x * vec2.y - vec1.y * vec1.x);
}

Vector2 Vector2::operator*(double val) {
	return Vector2(this->x * val, this->y * val);
}


