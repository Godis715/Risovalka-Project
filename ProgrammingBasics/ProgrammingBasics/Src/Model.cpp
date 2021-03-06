﻿#include "Model.h"
#include <list>

Model* Model::instance = nullptr;

Model* Model::GetInstance() {
	if(instance == nullptr) {
		instance = new Model;
	}
	return instance;
}

Model::Model() {
	dataCtrl = DataController::GetInstance();
	primCtrl = PrimController::GetInstance();
	reqCtrl = ReqController::GetInstance();
	objCtrl = ObjectController::GetInstance();
}

ID Model::CreatePrimitive(object_type type, const Array<double>& params) const {
	ID obj = primCtrl->CreatePrimitive(type, Array<ID>(0), params);
	dataCtrl->AddObject(obj);
	Array<ID> children = primCtrl->GetChildren(obj);
	if (children.GetSize() != 0) {
		for (int i = 0; i < children.GetSize(); ++i) {
			dataCtrl->AddObject(children[i]);
		}
		dataCtrl->Connect(obj, children);
	}
	return obj;
}

ID Model::AddPointToCurve(const ID& obj, const int index, const Array<double>& params) const {
	ID id = CreatePrimitive(ot_point, CreateArr(params[0], params[1]));
	Point* point = dynamic_cast<Point*>(primCtrl->GetPrimitive(id));
	Curve* curve = dynamic_cast<Curve*>(primCtrl->GetPrimitive(obj));
	curve->AddPoint(index, point, CreateArr(params[2], params[3], params[4]));
	dataCtrl->Connect(obj, CreateArr(id));
	return id;
}

Array<ID> Model::OrderedCreateRequirement(const Array<ID>& IDs) const {
	Array<ID> orderedID = Array<ID>(IDs.GetSize());
	int index = 0;
	Queue<ID> circle;
	Queue<ID> segment;
	Queue<ID> point;

	for (int i = 0; i < IDs.GetSize(); ++i) {
		auto type = objCtrl->GetType(IDs[i]);

		switch (type)
		{
		case ot_point: {
			point.Push(IDs[i]);
			break;
		}
		case ot_segment: {
			segment.Push(IDs[i]);
			break;
		}
		case ot_circle: {
			circle.Push(IDs[i]);
			break;
		}
		case ot_arc: {
			orderedID[index] = IDs[i];
			++index;
			break;
		}
		default:
			break;
		}
	}

	// cicrle

	while (!circle.IsEmpty())
	{
		orderedID[index] = circle.Pop();
		++index;
	}

	// segment

	while (!segment.IsEmpty())
	{
		orderedID[index] = segment.Pop();
		++index;
	}

	// point

	while (!point.IsEmpty())
	{
		orderedID[index] = point.Pop();
		++index;
	}

	return orderedID;
}

ID Model::CreateRequirement(object_type type, const Array<ID>& IDs, const Array<double>& params) const {
	Array<ID> children = OrderedCreateRequirement(IDs);
	ID obj = reqCtrl->CreateReq(type, children, params);
	dataCtrl->AddObject(obj);
	dataCtrl->Connect(obj, children);

	OptimizeByID(obj);

	return obj;
}

ID Model::GetObjectByClick(double x, double y) const {
	return dataCtrl->GetObjectInCircle(x, y, SEARCHING_AREA);
}

Array<ID> Model::GetObjectsByArea(double x1, double y1, double x2, double y2) const {
	return dataCtrl->GetObjectsByArea(x1, y1, x2, y2);
}

void Model::DeleteObject(ID& obj) const {
	dataCtrl->MakeInValid(obj);
}

void Model::DeleteObjects(Array<ID>& objs) const {
	for (int i = 0; i < objs.GetSize(); ++i) {
		DeleteObject(objs[i]);
	}
}

void Model::ChangeRequirement(const ID& req, const Array<double>& params) const {
	reqCtrl->SetReqParams(req, params);
	OptimizeByID(req);
}

void Model::Save(const std::string& path) const {
	SVGformat downloader;
	downloader.Save(path, true);
}

void Model::Download(const std::string& path) const {
	SVGformat downloader;
	downloader.Download(path);
}

Array<ID> Model::GetRelatedObjects(const ID& obj) const {
	return dataCtrl->GetRelatedObjects(obj);
}

void Model::OptimizeByID(const ID& obj) const {
	auto component = dataCtrl->GetComponent(obj);
	
	Array<ID> req(0);

	List<ID> arcs;

	auto compIt = component.GetMarker();
	while (compIt.IsValid()) {
		ID currID = *compIt;
		if (reqCtrl->IsReq(currID)) {
			req.PushBack(currID);
		}
		if (objCtrl->GetType(currID) == ot_arc) {
			arcs.Push(currID);
		}
		++compIt;
	}
	if (req.GetSize() != 0) {
		Optimizer optimizer;
		optimizer.OptimizeRequirements(req);

	}

	for (auto i = arcs.Begin(); i != arcs.AfterEnd(); ++i) {
		auto arc = dynamic_cast<Arc*>(primCtrl->GetPrimitive(*i));
		arc->RestoreCenter();
	}
}

void Model::Optimize() const {
	auto component = dataCtrl->GetComponent();

	Array<ID> req(0);

	List<ID> arcs;

	auto compIt = component->GetMarker();
	while (compIt.IsValid()) {
		ID currID = *compIt;
		if (reqCtrl->IsReq(currID)) {
			req.PushBack(currID);
		}
		if (objCtrl->GetType(currID) == ot_arc) {
			arcs.Push(currID);
		}
		++compIt;
	}
	if (req.GetSize() != 0) {
		Optimizer optimizer;
		optimizer.OptimizeRequirements(req);

	}

	for (auto i = arcs.Begin(); i != arcs.AfterEnd(); ++i) {
		auto arc = dynamic_cast<Arc*>(primCtrl->GetPrimitive(*i));
		arc->RestoreCenter();
	}
}

Array<double> Model::GetObjParam(const ID& obj) const {
	if (primCtrl->IsPrimitive(obj)) {
		return primCtrl->GetPrimitiveParamsAsValues(obj);
	}
	if (reqCtrl->IsReq(obj)) {
		return reqCtrl->GetReqParamsAsValues(obj);
	}
	LOGERROR("GetObjParam: unknown type", LEVEL_1);
	
}

void Model::SetVariableObjParam(const ID& obj, const Array<double>& params, int modifiers...) const {
	primCtrl->SetVariableObjParam(obj, params, &modifiers);
}

Array<double> Model::GetVariableObjParam(const ID& obj, int modifiers...) const {
	return primCtrl->GetVariableObjParam(obj, &modifiers);
}

bool Model::IsPrim(const ID& obj) const {
	return primCtrl->IsPrimitive(obj);
}
bool Model::IsReq(const ID& obj) const {
	return reqCtrl->IsReq(obj);
}

void Model::CashNewComponent(const Array<ID>& IDs) const {
	dataCtrl->CashComponent(IDs);
}

void Model::Scale(const Array<ID>& objs, const double coef) const {
	Set<ID> points;
	List<ID> circles;
	double x = 0;
	double y = 0;
	for (int i = 0; i < objs.GetSize(); ++i) {
		if (objCtrl->GetType(objs[i]) == ot_point) {
			points.Add(objs[i]);
		}
		else {
			if (objCtrl->GetType(objs[i]) == ot_circle) {
				circles.Push(objs[i]);
			}
			Array<ID> children = primCtrl->GetChildren(objs[i]);
			for (int j = 0; j < children.GetSize(); ++j) {
				auto params = primCtrl->GETVARPARAMS(children[j], VERTEX);
				x += params[0];
				y += params[1];
				points.Add(children[j]);
			}
		}
	}
	x /= points.GetSize();
	y /= points.GetSize();
	auto point = points.GetMarker();
	while (point.IsValid()) {
		auto params = primCtrl->GETVARPARAMS(*point, VERTEX);

		params[0] = (params[0] - x) * coef + x;
		params[1] = (params[1] - y) * coef + y;

		primCtrl->SetPrimitiveParams(*point, params);

		primCtrl->Deactivate(*point);

		++point;
	}

	auto circle = circles.Begin();
	while (circle.IsValid())
	{
		auto params = primCtrl->GETVARPARAMS(*circle, RADIUS);
		params[0] = params[0] * coef;
		primCtrl->SetPrimitiveParams(*circle, params);
		++circle;
	}

	Optimize();

	auto it = points.GetMarker();

	while (it.IsValid()) {
		primCtrl->Activate(*it);
		++it;
	}
} 

void Model::Move(const Array<ID>& objs, const Vector2& direction) const {
	Set<ID> points;
	for (int i = 0; i < objs.GetSize(); ++i) {
		if (objCtrl->GetType(objs[i]) == ot_point) {
				points.Add(objs[i]);
		}
		else {
			Array<ID> children = primCtrl->GetChildren(objs[i]);
			for (int j = 0; j < children.GetSize(); ++j) {
				points.Add(children[j]);
			}
		}
	}

	auto point = points.GetMarker();
	while (point.IsValid()) {
		auto params = primCtrl->GETVARPARAMS(*point, VERTEX);

		params[0] += direction.x;
		params[1] += direction.y;

		primCtrl->SetPrimitiveParams(*point, params);
		
		primCtrl->Deactivate(*point);

		++point;
	}

	/*auto it = points.GetMarker();
	
	while (it.IsValid()) {
		OptimizeByID(*it);
		++it;
	}*/

	Optimize();

	auto it = points.GetMarker();

	while (it.IsValid()) {
		primCtrl->Activate(*it);
		++it;
	}
}

void Model::Rotate(const Array<ID>& objs, const double angle) const {
	Set<ID> points;
	double centerX = 0;
	double centerY = 0;
	for (int i = 0; i < objs.GetSize(); ++i) {
		if (objCtrl->GetType(objs[i]) == ot_point) {
			points.Add(objs[i]);
		}
		else {
			Array<ID> children = primCtrl->GetChildren(objs[i]);
			for (int j = 0; j < children.GetSize(); ++j) {
				auto params = primCtrl->GETVARPARAMS(children[j], VERTEX);
				centerX += params[0];
				centerY += params[1];
				points.Add(children[j]);
			}
		}
	}

	centerX /= points.GetSize();
	centerY /= points.GetSize();
	double sinus = sin(angle);
	double cosinus = cos(angle);

	auto point = points.GetMarker();
	while (point.IsValid()) {
		auto params = primCtrl->GETVARPARAMS(*point, VERTEX);
		double x = params[0] - centerX;
		double y = params[1] - centerY;
		params[0] = cosinus * x + sinus * y + centerX;
		params[1] = cosinus * y - sinus * x + centerY;

		primCtrl->SetPrimitiveParams(*point, params);

		primCtrl->Deactivate(*point);

		++point;
	}
	Optimize();

	auto it = points.GetMarker();

	while (it.IsValid()) {
		primCtrl->Activate(*it);
		++it;
	}
}

void Model::Rotate(const Array<ID>& objs, const Vector2& center, const double angle) const {
	Set<ID> points;
	for (int i = 0; i < objs.GetSize(); ++i) {
		if (objCtrl->GetType(objs[i]) == ot_point) {
			points.Add(objs[i]);
		}
		else {
			Array<ID> children = primCtrl->GetChildren(objs[i]);
			for (int j = 0; j < children.GetSize(); ++j) {
				points.Add(children[j]);
			}
		}
	}

	double sinus = sin(angle);
	double cosinus = cos(angle);

	auto point = points.GetMarker();
	while (point.IsValid()) {
		auto params = primCtrl->GETVARPARAMS(*point, VERTEX);
		double x = params[0] - center.x;
		double y = params[1] - center.y;
		params[0] = cosinus * x + sinus * y + center.x;
		params[1] = cosinus * y - sinus * x + center.y;

		primCtrl->SetPrimitiveParams(*point, params);

		primCtrl->Deactivate(*point);

		++point;
	}
	Optimize();

	auto it = points.GetMarker();

	while (it.IsValid()) {
		primCtrl->Activate(*it);
		++it;
	}
}

void Model::Clear() const { 
	dataCtrl->Clear();
}

Component Model::GetComponent(const ID& obj) {
	return dataCtrl->GetComponent(obj);
}

object_type Model::GetObjType(const ID& obj) const {
	return objCtrl->GetType(obj);
}

Set<ID>::bst_iterator Model::GetPrimIterator() {
	return dataCtrl->GetPrimIterator();
}

Array<double> Model::GetPrimParamsForDrawing(const ID& obj) const {
	Array<double> arr = primCtrl->GetPrimParamsForDrawing(obj);
	return arr;
}