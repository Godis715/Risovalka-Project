#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;

struct Point
{
	double x;
	double y;
};

double dist(Point p1, Point p2) {
	return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

double GetMidLength(Point p[6], int size) {
	double length[3];
	for (int i = 0; i < 3; ++i) {
		length[i] = dist(p[i * 2], p[i * 2 + 1]);
	}
	double lengthSum = length[0] + length[1] + length[2];
	double midLength = lengthSum / 3.0;
	return midLength;
}

double stateFunction(Point p[6], double midLength) {
	double length[3];
	for (int i = 0; i < 3; ++i) {
		length[i] = dist(p[i * 2], p[i * 2 + 1]);
	}

	double sumDist = 0;
	double minDist = dist(p[0], p[2]);
	int iMin = 2;
	for (int i = 3; i < 6; ++i) {
		double d = dist(p[0], p[i]);
		if (d < minDist) {
			minDist = d;
			iMin = i;
		}
	}
	sumDist += minDist;
	switch (iMin) {
	case 2: {
		if (dist(p[1], p[5]) < dist(p[1], p[4])) {
			sumDist += dist(p[1], p[5]) + dist(p[3], p[4]);
		}
		else {
			sumDist += dist(p[1], p[4]) + dist(p[3], p[5]);
		}
		break;
	}
	case 3: {
		if (dist(p[2], p[5]) < dist(p[2], p[4])) {
			sumDist += dist(p[2], p[5]) + dist(p[1], p[4]);
		}
		else {
			sumDist += dist(p[2], p[4]) + dist(p[1], p[5]);
		}
		break;
	}
	case 4: {
		if (dist(p[1], p[2]) < dist(p[1], p[3])) {
			sumDist += dist(p[1], p[2]) + dist(p[5], p[3]);
		}
		else {
			sumDist += dist(p[1], p[3]) + dist(p[5], p[2]);
		}
		break;
	}
	case 5: {
		if (dist(p[1], p[2]) < dist(p[1], p[3])) {
			sumDist += dist(p[1], p[2]) + dist(p[4], p[3]);
		}
		else {
			sumDist += dist(p[1], p[3]) + dist(p[4], p[2]);
		}
		break;
	}
	}

	double lengthSum = length[0] + length[1] + length[2];
	//double midLength = lengthSum / 3.0;
	//double lengthDeviation = (abs(length[0] - length[1]) + abs(length[1] - length[2]) + abs(length[2] - length[0])) / 3;
	double lengthDeviation = abs(length[0] - midLength) + abs(length[1] - midLength) + abs(length[2] - midLength);
	double result = (lengthDeviation + sumDist) / midLength;
	return result;

};

void GeneratePoint(Point p[6], int size) {
	srand(time(nullptr));
	double xMin = p[0].x;
	double yMin = p[0].y;
	double xDelta = xMin, yDelta = yMin;
	for (int i = 1; i < size; ++i) {
		if (xMin > p[i].x) {
			xMin = p[i].x;
		}
		if (yMin > p[i].y) {
			yMin = p[i].y;
		}
		if (xDelta < p[i].x) {
			xDelta = p[i].x;
		}
		if (yDelta < p[i].y) {
			yDelta = p[i].y;
		}
	}
	xDelta = xDelta - xMin;
	yDelta = yDelta - yMin;
	if (xDelta < 5) {
		xDelta = 5;
	}
	if (yDelta < 5) {
		yDelta = 5;
	}
	for (int i = 0; i < size; ++i) {
		p[i].x = rand() % int(xDelta) + xMin;
		p[i].y = rand() % int(yDelta) + yMin;
	}
	return;
}

void func(Point* p, double fault, int size) {
	double midLength = GetMidLength(p, size);
	int CountIter = 0;
	double statefunc = stateFunction(p, midLength);
	double f, fmin, ffirst, delta;
	Point* pmin = new Point;
	while (statefunc > fault)
	{
		++CountIter;
		for (int index = 0; index < size; ++index) {
			pmin->x = p[index].x;
			pmin->y = p[index].y;
			fmin = stateFunction(p, midLength);
			ffirst = fmin;
			delta = fmin * midLength / 10;
			for (int ind = 0; ind < 5; ++ind) {
				p[index].y += delta;
				p[index].x -= delta;
				for (int i = 0; i < 3; ++i) {
					for (int j = 0; j < 3; ++j) {
						f = stateFunction(p, midLength);
						if (f < fmin) {
							fmin = f;
							pmin->x = p[index].x;
							pmin->y = p[index].y;
						}
						p[index].x += delta;
					}
					p[index].x -= (delta * 3);
					p[index].y -= delta;
				}
				p[index].x = pmin->x;
				p[index].y = pmin->y;
				if (fmin == ffirst) {
					ffirst = fmin;
					delta /= 2;
				}
			}
		}
		if (statefunc == fmin) {
			if (statefunc > 0.01) {
				GeneratePoint(p, size);
				statefunc = stateFunction(p, midLength);
			}
			else {
				break;
			}
		}
		statefunc = fmin;
	}
	cout << endl << CountIter;
	delete pmin;
	return;
}

int not_main() {
	Point* p = new Point[6];
	for (int i = 0; i < 6; ++i) {
		cin >> p[i].x >> p[i].y;
	}
	double E = 0.0000001;
	func(p, E, 6);
	cout << endl << endl;
	for (int i = 0; i < 6; ++i) {
		cout << p[i].x << ' ' << p[i].y << endl;
	}
	system("pause");
	return 0;
}
