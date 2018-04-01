#include "Presenter.h"
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
		double x1 = (double)rand() / (rand() % 100);
		double y1 = (double)rand() / (rand() % 100);
		double x2 = (double)rand() / (rand() % 100);
		double y2 = (double)rand() / (rand() % 100);
		std::cout << count << " segment 1) " << x1 << ' ' << y1 << " ; " << x2 << ' ' << y2 << "\n";
		ID segment1 = presenter.CreateSegment(x1, y1, x2, y2);
		x1 = (double)rand() / (rand() % 100);
		y1 = (double)rand() / (rand() % 100);
		x2 = (double)rand() / (rand() % 100);
		y2 = (double)rand() / (rand() % 100);
		std::cout << count << " segment 2) " << x1 << ' ' << y1 << " ; " << x2 << ' ' << y2 << "\n";
		ID segment2 = presenter.CreateSegment(x1, y1, x2, y2);
		x1 = (double)rand() / (rand() % 100);
		y1 = (double)rand() / (rand() % 100);
		x2 = (double)rand() / (rand() % 100);
		y2 = (double)rand() / (rand() % 100);
		std::cout << count << " segment 3) " << x1 << ' ' << y1 << " ; " << x2 << ' ' << y2 << "\n\n";
		ID segment3 = presenter.CreateSegment(x1, y1, x2, y2);
		presenter.CreateRequirmentTrianle(segment1, segment2, segment3);
		std::cout << presenter.Optimize();
		presenter.PrintSystemRequirement();
	}
}

void CreateDrowBestTriangles(int count) {
	for (int i = 0; i < count; ++i) {
		double x1 = (double)rand() / (rand() % 100);
		double y1 = (double)rand() / (rand() % 100);
		double x2 = (double)rand() / (rand() % 100);
		double y2 = (double)rand() / (rand() % 100);
		std::cout << count << " segment 1) " << x1 << ' ' << y1 << " ; " << x2 << ' ' << y2 << "\n";
		ID segment1 = presenter.CreateSegment(x1, y1, x2, y2);
		x1 = (double)rand() / (rand() % 100);
		y1 = (double)rand() / (rand() % 100);
		x2 = (double)rand() / (rand() % 100);
		y2 = (double)rand() / (rand() % 100);
		std::cout << count << " segment 2) " << x1 << ' ' << y1 << " ; " << x2 << ' ' << y2 << "\n";
		ID segment2 = presenter.CreateSegment(x1, y1, x2, y2);
		x1 = (double)rand() / (rand() % 100);
		y1 = (double)rand() / (rand() % 100);
		x2 = (double)rand() / (rand() % 100);
		y2 = (double)rand() / (rand() % 100);
		std::cout << count << " segment 3) " << x1 << ' ' << y1 << " ; " << x2 << ' ' << y2 << "\n\n";
		ID segment3 = presenter.CreateSegment(x1, y1, x2, y2);
		double size = (double)(rand() % 100);
		presenter.CreateRequirmentBestTrianle(segment1, segment2, segment3, size);
		std::cout << presenter.Optimize();
		std::cout << std::endl;
		presenter.PrintSystemRequirement();
	}
}

void AngleSegments(int count) {
	for (int i = 0; i < count; ++i) {
		double x1 = (double)rand() / (rand() % 100);
		double y1 = (double)rand() / (rand() % 100);
		double x2 = (double)rand() / (rand() % 100);
		double y2 = (double)rand() / (rand() % 100);
		std::cout << count << " segment 1) " << x1 << ' ' << y1 << " ; " << x2 << ' ' << y2 << "\n";
		ID segment1 = presenter.CreateSegment(x1, y1, x2, y2);
		x1 = (double)rand() / (rand() % 100);
		y1 = (double)rand() / (rand() % 100);
		x2 = (double)rand() / (rand() % 100);
		y2 = (double)rand() / (rand() % 100);
		std::cout << count << " segment 2) " << x1 << ' ' << y1 << " ; " << x2 << ' ' << y2 << "\n";
		ID segment2 = presenter.CreateSegment(x1, y1, x2, y2);
		x1 = (double)rand() / (rand() % 100);
		y1 = (double)rand() / (rand() % 100);
		x2 = (double)rand() / (rand() % 100);
		y2 = (double)rand() / (rand() % 100);
		std::cout << count << " segment 3) " << x1 << ' ' << y1 << " ; " << x2 << ' ' << y2 << "\n\n";
		ID segment3 = presenter.CreateSegment(x1, y1, x2, y2);
		double angle = (double)rand();
		if (angle > PI / 2) {
			angle = angle - (double)(int)(angle / (PI / 2)) * PI / 2;
			return;
		}
		if (angle < 0.0) {
			angle = angle + ((double)((int)(abs(angle) / (2 * PI)) + 1) * 2 * PI);
			return;
		}
		presenter.CreateRequirmentAngleBetweenSegments(segment1, segment2, angle);
		std::cout << presenter.Optimize();
		presenter.PrintSystemRequirement();
	}
}

void PointsOnOneSide(int count) {
	for (int i = 0; i < count; ++i) {
		double x1 = (double)rand() / (rand() % 100);
		double y1 = (double)rand() / (rand() % 100);
		double x2 = (double)rand() / (rand() % 100);
		double y2 = (double)rand() / (rand() % 100);
		std::cout << count << " segment 1) " << x1 << ' ' << y1 << " ; " << x2 << ' ' << y2 << "\n";
		ID segment = presenter.CreateSegment(x1, y1, x2, y2);
		x1 = (double)rand() / (rand() % 100);
		y1 = (double)rand() / (rand() % 100);
		std::cout << count << " point1) " << x1 << ' ' << y1 << "\n";
		ID point1 = presenter.CreatePoint(x1, y1);
		x1 = (double)rand() / (rand() % 100);
		y1 = (double)rand() / (rand() % 100);
		std::cout << count << " point2) " << x1 << ' ' << y1 << "\n\n";
		ID point2 = presenter.CreatePoint(x1, y1);
		presenter.CreateRequirmentPointsOnTheOneHand(segment, point1, point2);
		std::cout << presenter.Optimize();
		presenter.PrintSystemRequirement();
	}
}

void DistancePointSegment(int count) {
	for (int i = 0; i < count; ++i) {
		double x1 = (double)rand() / (rand() % 100);
		double y1 = (double)rand() / (rand() % 100);
		double x2 = (double)rand() / (rand() % 100);
		double y2 = (double)rand() / (rand() % 100);
		std::cout << count << " segment 1) " << x1 << ' ' << y1 << " ; " << x2 << ' ' << y2 << "\n";
		ID segment = presenter.CreateSegment(x1, y1, x2, y2);
		x1 = (double)rand() / (rand() % 100);
		y1 = (double)rand() / (rand() % 100);
		std::cout << count << " point1) " << x1 << ' ' << y1 << "\n";
		ID point1 = presenter.CreatePoint(x1, y1);
		double distance = (double)(rand() % 100);
		std::cout << count << " distance) " << distance << "\n\n";
		presenter.CreateRequirmentDistanceBetweenPointSegment(segment, point1, distance);
		std::cout << presenter.Optimize();
		presenter.PrintSystemRequirement();
	}
}

void CreateBrokenLine(int count) {
	int countOptimize = 0;
	ID prev;
	ID p1;
	ID p2;
	double x1 = (double)rand() / (rand() % 100);
	double y1 = (double)rand() / (rand() % 100);
	double x2 = (double)rand() / (rand() % 100);
	double y2 = (double)rand() / (rand() % 100);
	p1 = presenter.CreatePoint(x1, y1);
	p2 = presenter.CreatePoint(x2, y2);
	presenter.CreateSegment(p1, p2);
	std::cout << count << " segment 1) " << x1 << ' ' << y1 << " ; " << x2 << ' ' << y2 << "\n";
	prev = p2;
	for (int i = 1; i < count; ++i) {
		x1 = (double)rand() / (rand() % 100);
		y1 = (double)rand() / (rand() % 100);
		x2 = (double)rand() / (rand() % 100);
		y2 = (double)rand() / (rand() % 100);
		p1 = presenter.CreatePoint(x1, y1);
		p2 = presenter.CreatePoint(x2, y2);
		std::cout << count << " - #" << i << " segment) " << x1 << ' ' << y1 << " ; " << x2 << ' ' << y2 << "\n";
		presenter.CreateRequirmentDistBetPoints(prev, p1, 0);
		countOptimize += presenter.Optimize();
		prev = p2;
	}
	std::cout << "countOptimize - " << countOptimize << "\n";
	presenter.PrintSystemRequirement();
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
	srand(time(0));
	const int segNum = 50;
	const int height = 100;
	const double segSize = 10.0;
	const int width = 150;
	MySegment** arr = new MySegment*[segNum];
	Array<ID> points;
	for (int i = 0; i < segNum; ++i) {
		arr[i] = new MySegment(double(rand() % width), double(rand() % height),
			double(rand() % width), double(rand() % height));
		points.pushBack(arr[i]->point1);
		points.pushBack(arr[i]->point2);
	}

	for (int i = 0; i < segNum - 1; ++i) {
		CreateRequirmentDistBetPoints(arr[i]->point2, arr[i + 1]->point1, 0.0);
	}
	int countDown = model.Optimize();
	PrintPoints(points);
	system("pause");
	return 0;
}

//Dict<int, int> dict;
//dict.Add(5, 5);
//dict.Add(3, 3);
//dict.Add(7, 7);
//dict.Add(1, 1);
//dict.Add(2, 2);
//dict.Add(4, 4);
//dict.Add(6, 6);
//dict.Add(8, 8);
//dict.Add(9, 9);
//dict.Erase(9);
//dict.Erase(1);
//dict.find(6);
//int q = -1;
//if (dict.IsCurrent()) {
//	q = dict.GetCurrent();
//}
//std::cout << std::endl << q;
//int size = dict.getsize();
//dict.MoveParent();
//if (dict.IsCurrent()) {
//	q = dict.GetCurrent();
//}
//std::cout << std::endl << q;
//dict.MoveLeft();
//if (dict.IsCurrent()) {
//	q = dict.GetCurrent();
//}
//dict.MoveParent();
//dict.MoveRight();
//if (dict.IsCurrent()) {
//	q = dict.GetCurrent();
//}
//std::cout << std::endl << q;
//dict.MoveHead();
//if (dict.IsCurrent()) {
//	q = dict.GetCurrent();
//}
//std::cout << std::endl << q;
//
//dict.DeleteDict();
//std::cout << std::endl << dict.getsize();
//dict.Add(5, 5);
//dict.Add(3, 3);
//dict.Add(7, 7);