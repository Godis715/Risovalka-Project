#include <ctime>
#include "ViewFLTK.h"
#include <vector>
#include <regex>

//ID CreatePoint(const Array<ID>& obj, const Array<double>& params) {
//	return Presenter::CreateObject(ot_point, params);
//}
//ID CreateSegment(const Array<ID>& obj, const Array<double>& params) {
//	return Presenter::CreateObject(ot_segment, params);
//}
//ID CreateArc(const Array<ID>& obj, const Array<double>& params) {
//	return Presenter::CreateObject(ot_arc, params);
//}
//ID CreateCircle(const Array<ID>& obj, const Array<double>& params) {
//	return Presenter::CreateObject(ot_circle, params);
//}
//ID Move(const Array<ID>& obj, const Array<double>& params) {
//	if (params.GetSize() != 2) {
//		throw std::exception("invalid arguments");
//	}
//	Presenter::MoveObject(obj, Vector2(params[0], params[1]));
//	return ID();
//
//}
//ID Scale(const Array<ID>& obj, const Array<double>& params) {
//	if (params.GetSize() != 1) {
//		throw std::exception("invalid arguments");
//	}
//	Presenter::ScaleObjects(obj, params[0]);
//	return ID();
//}
//ID DistBetPoints(const Array<ID>& obj, const Array<double>& params) {
//	return Presenter::CreateRequirement(ot_distBetPoints, obj, params);
//}
//ID EqualSegment(const Array<ID>& obj, const Array<double>& params) {
//	return Presenter::CreateRequirement(ot_equalSegmentLen, obj, params);
//}
//ID DistanceBetPointSegment(const Array<ID>& obj, const Array<double>& params) {
//	return Presenter::CreateRequirement(ot_distBetPoints, obj, params);
//}
//ID Delete(const Array<ID>& obj, const Array<double>& params) {
//	Presenter::DeletePrimitives(obj);
//	return ID();
//}


//ID CreatePoint(const Array<ID>& obj, const Array<double>& params) {
//	
//	for (int i = 0; i < params.GetSize(); ++i) {
//		std::cout << params[i] << " ";
//	}
//	std::cout << "CreatePoint" << std::endl;
//	return ID();
//}
//ID CreateSegment(const Array<ID>& obj, const Array<double>& params) {
//	for (int i = 0; i < params.GetSize(); ++i) {
//		std::cout << params[i] << " ";
//	}
//	std::cout << "CreateSegment" << std::endl;
//	return ID();
//}
//ID CreateArc(const Array<ID>& obj, const Array<double>& params) {
//	std::cout << "CreateArc" << std::endl;
//	return ID();
//}
//ID CreateCircle(const Array<ID>& obj, const Array<double>& params) {
//	std::cout << "CreateCircle" << std::endl;
//	return ID();
//}
//ID Move(const Array<ID>& obj, const Array<double>& params) {
//	std::cout << "Move" << std::endl;
//	return ID();
//}
//ID Scale(const Array<ID>& obj, const Array<double>& params) {
//	std::cout << "Scale" << std::endl;
//	return ID();
//}
//ID DistBetPoints(const Array<ID>& obj, const Array<double>& params) {
//	std::cout << "DistBetPoints" << std::endl;
//	return ID();
//}
//ID EqualSegment(const Array<ID>& obj, const Array<double>& params) {
//	std::cout << "EqualSegment" << std::endl;
//	return ID();
//}
//ID DistanceBetPointSegment(const Array<ID>& obj, const Array<double>& params) {
//	std::cout << "DistanceBetPointSegment" << std::endl;
//	return ID();
//}
//ID Delete(const Array<ID>& obj, const Array<double>& params) {
//	std::cout << "Delete" << std::endl;
//	return ID();
//}

void LoggerInit() {
	std::ofstream* out = new std::ofstream("log.txt");
	if (!out->is_open()) {
		int a = 5;
	}
	Logger::InitLogger(out, LEVEL_1);
}

int main()
{
	
	LoggerInit();
	try {
		IView* view = ViewFLTK::GetInstance();
		return view->Run();
	}
	catch (...) {}
}