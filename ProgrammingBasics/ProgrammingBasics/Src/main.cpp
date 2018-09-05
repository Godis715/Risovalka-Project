#include <ctime>
#include "ViewFLTK.h"
#include <vector>
#include <regex>

//Model model;
//
//ID CreatePoint(double x, double y) {
//	ID id;
//	Array<double> params(2);
//	params[0] = x;
//	params[1] = y;
//
//	if (!model.CreateObject(point_t, params, id)) {
//		throw std::exception("Creating point failed");
//	}
//	return id;
//}
//ID CreateSegment(double x1, double y1, double x2, double y2) {
//	ID id;
//	Array<double> params(4);
//	params[0] = x1;
//	params[1] = y1;
//	params[2] = x2;
//	params[3] = y2;
//
//	if (!model.CreateObject(segment_t, params, id)) {
//		throw std::exception("Creating segment failed");
//	}
//	return id;
//}
//ID CreateArc(double x1, double y1, double x2, double y2, double angle) {
//	ID id;
//	Array<double> params(5);
//	params[0] = x1;
//	params[1] = y1;
//	params[2] = x2;
//	params[3] = y2;
//	params[4] = angle;
//
//	if (!model.CreateObject(arc_t, params, id)) {
//		throw std::exception("Creating arc failed");
//	}
//	return id;
//}
//ID EqualSegmentLenReq(const ID& seg1, const ID& seg2) {
//	Array<ID> segments(2);
//	segments[0] = seg1;
//	segments[1] = seg2;
//
//	Array<double> params(0);
//
//	ID id;
//	if (!model.CreateRequirementByID(equalSegmentLen_t, segments, params, id)) {
//		throw std::exception("Creating equalSegmentLen requirement failed");
//	}
//	return id;
//}
//ID DistBetPointsReq(const ID& point1, const ID& point2, double dist) {
//	Array<ID> points(2);
//	points[0] = point1;
//	points[1] = point2;
//
//	Array<double> params(1);
//	params[0] = dist;
//
//	ID id;
//	if (!model.CreateRequirementByID(distBetPoints_t, points, params, id)) {
//		throw std::exception("Creating distBetPoints requirement failed");
//	}
//	return id;
//}
//
//ID PointPos(const ID& point1, double x, double y) {
//	Array<ID> points(1);
//	points[0] = point1;
//
//	Array<double> params(2);
//	params[0] = x;
//	params[1] = y;
//
//	ID id;
//	if (!model.CreateRequirementByID(pointPosReq_t, points, params, id)) {
//		throw std::exception("Creating pointPos requirement failed");
//	}
//	return id;
//}

/*ID segment1 = CreateSegment(6, -7, 5, 4);
ID segment2 = CreateSegment(2, 2, 5, -4);
ID segment3 = CreateSegment(-3, -3, 2, 5);

DistBetPointsReq(ID(1), ID(2), 5.5);
DistBetPointsReq(ID(2), ID(
5), 0.0);
DistBetPointsReq(ID(5), ID(6), 5.5);
DistBetPointsReq(ID(6), ID(9), 0.0);
DistBetPointsReq(ID(9), ID(10), 5.5);
DistBetPointsReq(ID(10), ID(1), 0.0);

model.OptimizeByID(ID(1));

Array<ID> arr(3);
arr[0] = segment1;
arr[1] = segment2;
arr[2] = segment3;

model.Scale(arr, 5);

ID point1 = CreatePoint(0, 500);
ID point2 = CreatePoint(0, 0);

ID req = DistBetPointsReq(point1, point2, 500);
model.OptimizeByID(req);

Array<double> params1;
model.GetObjParam(point1, params1);

Array<double> params2;
model.GetObjParam(point2, params2);

{Vector2 pos1(params1[0], params1[1]);
Vector2 pos2(params2[0], params2[1]);
int b = 0;
}

Array<ID> objects(1);
objects[0] = point1;

model.Move(objects, Vector2(0, 100));

model.GetObjParam(point1, params1);
model.GetObjParam(point2, params2);

{Vector2 pos1(params1[0], params1[1]);
Vector2 pos2(params2[0], params2[1]);
int a = 0; }*/

/*ID segment1 = CreateSegment(0.0, 0.0, 0.0, 20.0);
ID segment2 = CreateSegment(0.0, 0.0, 0.0, 5.0);
EqualSegmentLenReq(segment1, segment2);
ID point1 = CreatePoint(0.0, 0.0);
ID point2 = CreatePoint(1.0, 1.0);
DistBetPointsReq(point1, point2, 9.0);

BinSearchTree<ID, ID>* component = new BinSearchTree<ID, ID>;
model.GetComponent(segment1, *component);
model.GetComponent(point1, *component);*/

void LoggerInit() {
	std::ofstream* out = new std::ofstream("log.txt");
	if (!out->is_open()) {
		int a = 5;
	}
	Logger::InitLogger(out, LEVEL_1);
}

int main()
{
	/*string str("Comp(hhuhf, fwf, s)(..., 5.0);");

	std::cmatch result;
	std::regex regul("[A-Z]"
		"([a-z0-9_])*"
		"\\("
		"(([a-z0-9_])*, )*"
		"(([a-z0-9_])*\\))"
		"\\("
		"(([0-9.])*, )*"
		"(([0-9.])*\\))"
		";"
	);
	if (regex_match(str.c_str(), result, regul))
 		for (int i = 0;i < result.size();i++)
			std::cout << result[i] << std::endl;

	string str2("Comp(da, d, fsfes)(2)->udd;");
	std::regex regul2("[A-Z]"
		"([a-z0-9_])*"
		"\\("
		"(([a-z0-9_])*, )*"
		"(([a-z0-9_])*\\))"
		"\\("
		"(([0-9.])*, )*"
		"(([0-9.])*\\))"
		"->"
		"[a-z]"
		"([a-z0-9_])*"
		";"
	);
	if (regex_match(str2.c_str(), result, regul2))
		for (int i = 0;i < result.size();i++)
			std::cout << result[i] << std::endl;

*/
	LoggerInit();
	/*try {
		IView* view = new ViewFLTK();
		return view->Run();
	}
	catch (...) {
	std::regex regul1("[A-Z]"
	"([a-zA-Z0-9_])*"
	"\\("
	"(([a-zA-Z0-9_])*, )*"
	"(([a-zA-Z0-9_ ])*\\))"
	";"
	);
	}*/
}