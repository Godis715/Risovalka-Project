#include "View.h"
#include <ctime>

Presenter presenter;
Model model;
 /*void PrintPoints(Array<ID> points) {
	for (int i = 0; i < points.getSize(); ++i) {
		Array<double> params;
		std::cout << i << ")";
		model.getObjParam(points[i], params);
		for (int j = 0; j < params.getSize(); ++j) {
			std::cout << params[j] << " ";
		}
		std::cout << "\n";
	}
}*/

void CreateDrowTriangles(int count) {
	for (int i = 0; i < count; ++i) {
		double x1 = (double)rand() / (rand() % 100 + 1);
		double y1 = (double)rand() / (rand() % 100 + 1);
		double x2 = (double)rand() / (rand() % 100 + 1);
		double y2 = (double)rand() / (rand() % 100 + 1);
		std::cout << i << " segment 1) " << x1 << ' ' << y1 << " ; " << x2 << ' ' << y2 << "\n";
		ID segment1 = presenter.CreateSegment(x1, y1, x2, y2);
		x1 = (double)rand() / (rand() % 100 + 1);
		y1 = (double)rand() / (rand() % 100 + 1);
		x2 = (double)rand() / (rand() % 100 + 1);
		y2 = (double)rand() / (rand() % 100 + 1);
		std::cout << i << " segment 2) " << x1 << ' ' << y1 << " ; " << x2 << ' ' << y2 << "\n";
		ID segment2 = presenter.CreateSegment(x1, y1, x2, y2);
		x1 = (double)rand() / (rand() % 100 + 1);
		y1 = (double)rand() / (rand() % 100 + 1);
		x2 = (double)rand() / (rand() % 100 + 1);
		y2 = (double)rand() / (rand() % 100 + 1);
		std::cout << i << " segment 3) " << x1 << ' ' << y1 << " ; " << x2 << ' ' << y2 << "\n\n";
		ID segment3 = presenter.CreateSegment(x1, y1, x2, y2);
		presenter.CreateRequirmentTriangle(segment1, segment2, segment3);
	}
	std::cout << presenter.Optimize();
	//presenter.PrintSystemRequirement();
}

void CreateDrowBestTriangles(int count) {
	for (int i = 0; i < count; ++i) {
		double x1 = (double)rand() / (rand() % 100 + 1);
		double y1 = (double)rand() / (rand() % 100 + 1);
		double x2 = (double)rand() / (rand() % 100 + 1);
		double y2 = (double)rand() / (rand() % 100 + 1);
		std::cout << i << " segment 1) " << x1 << ' ' << y1 << " ; " << x2 << ' ' << y2 << "\n";
		ID segment1 = presenter.CreateSegment(x1, y1, x2, y2);
		x1 = (double)rand() / (rand() % 100 + 1);
		y1 = (double)rand() / (rand() % 100 + 1);
		x2 = (double)rand() / (rand() % 100 + 1);
		y2 = (double)rand() / (rand() % 100 + 1);
		std::cout << i << " segment 2) " << x1 << ' ' << y1 << " ; " << x2 << ' ' << y2 << "\n";
		ID segment2 = presenter.CreateSegment(x1, y1, x2, y2);
		x1 = (double)rand() / (rand() % 100 + 1);
		y1 = (double)rand() / (rand() % 100 + 1);
		x2 = (double)rand() / (rand() % 100 + 1);
		y2 = (double)rand() / (rand() % 100 + 1);
		std::cout << i << " segment 3) " << x1 << ' ' << y1 << " ; " << x2 << ' ' << y2 << "\n";
		ID segment3 = presenter.CreateSegment(x1, y1, x2, y2);
		double size = (double)(rand() % 100 + 1);
		std::cout << i << " size " << size << "\n\n";
		presenter.CreateRequirmentBestTriangle(segment1, segment2, segment3, size);
	}
	std::cout << presenter.Optimize();
	//presenter.PrintSystemRequirement();
}

void AngleSegments(int count) {
	for (int i = 0; i < count; ++i) {
		double x1 = (double)rand() / (rand() % 100 + 1);
		double y1 = (double)rand() / (rand() % 100 + 1);
		double x2 = (double)rand() / (rand() % 100 + 1);
		double y2 = (double)rand() / (rand() % 100 + 1);
		std::cout << i << " segment 1) " << x1 << ' ' << y1 << " ; " << x2 << ' ' << y2 << "\n";
		ID segment1 = presenter.CreateSegment(x1, y1, x2, y2);
		x1 = (double)rand() / (rand() % 100 + 1);
		y1 = (double)rand() / (rand() % 100 + 1);
		x2 = (double)rand() / (rand() % 100 + 1);
		y2 = (double)rand() / (rand() % 100 + 1);
		std::cout << i << " segment 2) " << x1 << ' ' << y1 << " ; " << x2 << ' ' << y2 << "\n";
		ID segment2 = presenter.CreateSegment(x1, y1, x2, y2);
		double angle = (double)rand();
		

		if (angle > PI / 2) {
			angle = angle - (double)(int)(angle / (PI / 2)) * PI / 2;
		}
		if (angle < 0.0) {
			angle = angle + ((double)((int)(abs(angle) / (2 * PI)) + 1) * 2 * PI);
		}
		std::cout << i << " angle  " << angle << "\n\n";
		presenter.CreateRequirmentAngleBetweenSegments(segment1, segment2, angle);
	}
	std::cout << presenter.Optimize();
	//presenter.PrintSystemRequirement();
}

void PointsOnOneSide(int count) {
	for (int i = 0; i < count; ++i) {
		double x1 = (double)rand() / (rand() % 100 + 1);
		double y1 = (double)rand() / (rand() % 100 + 1);
		double x2 = (double)rand() / (rand() % 100 + 1);
		double y2 = (double)rand() / (rand() % 100 + 1);
		std::cout << i << " segment 1) " << x1 << ' ' << y1 << " ; " << x2 << ' ' << y2 << "\n";
		ID segment = presenter.CreateSegment(x1, y1, x2, y2);
		x1 = (double)rand() / (rand() % 100 + 1);
		y1 = (double)rand() / (rand() % 100 + 1);
		std::cout << i << " point1) " << x1 << ' ' << y1 << "\n";
		ID point1 = presenter.CreatePoint(x1, y1);
		x1 = (double)rand() / (rand() % 100 + 1);
		y1 = (double)rand() / (rand() % 100 + 1);
		std::cout << i << " point2) " << x1 << ' ' << y1 << "\n\n";
		ID point2 = presenter.CreatePoint(x1, y1);
		presenter.CreateRequirmentPointsOnTheOneHand(segment, point1, point2);
	}
	std::cout << presenter.Optimize();
	//presenter.PrintSystemRequirement();
}

void DistancePointSegment(int count) {
	for (int i = 0; i < count; ++i) {
		double x1 = (double)rand() / (rand() % 100 + 1);
		double y1 = (double)rand() / (rand() % 100 + 1);
		double x2 = (double)rand() / (rand() % 100 + 1);
		double y2 = (double)rand() / (rand() % 100 + 1);
		std::cout << i << " segment 1) " << x1 << ' ' << y1 << " ; " << x2 << ' ' << y2 << "\n";
		ID segment = presenter.CreateSegment(x1, y1, x2, y2);
		x1 = (double)rand() / (rand() % 100 + 1);
		y1 = (double)rand() / (rand() % 100 + 1);
		std::cout << i << " point1) " << x1 << ' ' << y1 << "\n";
		ID point1 = presenter.CreatePoint(x1, y1);
		double distance = (double)(rand() % 100 + 1);
		std::cout << i << " distance) " << distance << "\n\n";
		presenter.CreateRequirmentDistanceBetweenPointSegment(segment, point1, distance);
	}
	std::cout << presenter.Optimize();
	//presenter.PrintSystemRequirement();
}

void CreateBrokenLine(int count) {
	int countOptimize = 0;
	ID prev;
	ID p1;
	ID p2;
	double x1 = (double)rand() / (rand() % 100 + 1);
	double y1 = (double)rand() / (rand() % 100 + 1);
	double x2 = (double)rand() / (rand() % 100 + 1);
	double y2 = (double)rand() / (rand() % 100 + 1);
	p1 = presenter.CreatePoint(x1, y1);
	p2 = presenter.CreatePoint(x2, y2);
	presenter.CreateSegment(p1, p2);
	std::cout << 0 << " segment 1) " << x1 << ' ' << y1 << " ; " << x2 << ' ' << y2 << "\n";
	prev = p2;
	for (int i = 1; i < count; ++i) {
		x1 = (double)rand() / (rand() % 100 + 1);
		y1 = (double)rand() / (rand() % 100 + 1);
		x2 = (double)rand() / (rand() % 100 + 1);
		y2 = (double)rand() / (rand() % 100 + 1);
		p1 = presenter.CreatePoint(x1, y1);
		p2 = presenter.CreatePoint(x2, y2);
		std::cout << i << " segment) " << x1 << ' ' << y1 << " ; " << x2 << ' ' << y2 << "\n";
		presenter.CreateRequirmentDistBetPoints(prev, p1, 0);
		countOptimize += presenter.Optimize();
		prev = p2;
	}
	std::cout << "countOptimize - " << countOptimize << "\n";
	//presenter.PrintSystemRequirement();
}


ID CreatePoint(double x, double y) {
	Array<double> params;
	params.pushBack(x);
	params.pushBack(y);
	ID id;

	model.createObject(point, params, id);
	return id;

}

ID CreateSegment(double x1, double y1, double x2, double y2) {
	ID id;
	Array<double> params;
	params.pushBack(x1);
	params.pushBack(y1);
	params.pushBack(x2);
	params.pushBack(y2);

	model.createObject(segment, params, id);
	return id;
}

void CreateRequirmentDistBetPoints(ID point1, ID point2, double d) {
	Array<double> dist;
	Array<ID> points;
	points.pushBack(point1);
	points.pushBack(point2);
	dist.pushBack(d);

	model.createRequirement(distBetPoints, points, dist);
}

void PrintPoints(Array<ID> points) {
	for (int i = 0; i < points.getSize(); ++i) {
		Array<double> params;
		std::cout << i << ")";
		model.getObjParam(points[i], params);
		for (int j = 0; j < params.getSize(); ++j) {
			std::cout << params[j] << " ";
		}
		std::cout << "\n";
	}
}

class MySegment {
public:
	MySegment(double x1, double y1, double x2, double y2) {
		segment = CreateSegment(x1, y1, x2, y2);
		Array<ID> points;
		model.GetSegmentPoints(segment, points);
		point1 = points[0];
		point2 = points[1];
	}
	ID segment;
	ID point1;
	ID point2;
};

int main()
{
	IView* view = new View();

	while (true) {
		
	}

	return 0;
}

