#pragma once

class Point {
private:
public:
	Point() { 
		x = 0.0;
		y = 0.0;
	}
	Point(double _x, double _y) {
		x = _x;
		y = _y;
	}
	double x;
	double y;

};