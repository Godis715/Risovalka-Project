#include "Model.h"

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

ID Model::CreateRequirement(object_type type, const Array<ID>& children, const Array<double>& params) const {
	ID obj = reqCtrl->CreateReq(type, children, params);
	dataCtrl->AddObject(obj);
	dataCtrl->Connect(obj, children);

	OptimizeByID(obj);

	return obj;
}

ID Model::GetObjectByClick(double x, double y) const {
	return dataCtrl->GetObjectInCircle(x, y, SEARCHING_AREA);
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

void Model::ChangePrimitive(const ID& prim, const Array<double>& params) const {
	primCtrl->SetPrimitiveParams(prim, params);
	OptimizeByID(prim);
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

	auto compIt = component.GetMarker();
	while (compIt.IsValid()) {
		ID currID = *compIt;
		if (reqCtrl->IsReq(currID)) {
			req.PushBack(currID);
		}
		++compIt;
	}
	if (req.GetSize() != 0) {
		Optimizer optimizer;
		optimizer.OptimizeRequirements(req);
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

Array<double> Model::GetVariableObjParam(const ID& obj, int modifiers...) const {
	return primCtrl->GetVariableObjParam(obj, &modifiers);
}

bool Model::IsPrim(const ID& obj) const {
	return primCtrl->IsPrimitive(obj);
}
bool Model::IsReq(const ID& obj) const {
	return reqCtrl->IsReq(obj);
}

Array<ID> Model::GetObjectsByArea(double, double, double, double) const { 
	return Array<ID>(0);
}

void Model::Scale(const Array<ID>&, const double) const { }

void Model::Move(const Array<ID>&, const Vector2&) const { }

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