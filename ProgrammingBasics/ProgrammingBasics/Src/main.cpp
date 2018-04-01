#include <iostream>
#include "Model.h"

Model model;

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

int main()
{
	ID segment1 = CreateSegment(35.0, 1.0, -1.0, 0.0);
	ID segment2 = CreateSegment(90.0, 60.0, 90.0, 0.0);
	ID segment3 = CreateSegment(-5.0, -5.0, 20.0, 30.0);

	Array<ID> points1;
	Array<ID> points2;
	Array<ID> points3;

	model.GetSegmentPoints(segment1, points1);
	model.GetSegmentPoints(segment2, points2);
	model.GetSegmentPoints(segment3, points3);

	CreateRequirmentDistBetPoints(points1[1], points3[0], 0.0);
	CreateRequirmentDistBetPoints(points1[0], points2[1], 0.0);
	CreateRequirmentDistBetPoints(points3[1], points2[0], 0.0);

	CreateRequirmentDistBetPoints(points1[1], points1[0], 35.0);
	CreateRequirmentDistBetPoints(points2[0], points2[1], 35.0);
	CreateRequirmentDistBetPoints(points3[1], points3[0], 35.0);

	model.Optimize();

	PrintPoints(points1);
	PrintPoints(points2);
	PrintPoints(points3);

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