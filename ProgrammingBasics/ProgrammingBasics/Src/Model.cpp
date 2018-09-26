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
	return obj;
}
ID Model::GetObjectByClick(double x, double y) const {
	return dataCtrl->GetObjectInCircle(x, y, SEARCHING_AREA);
}

void Model::DeleteObject(const ID& obj) const {
	dataCtrl->DeleteObject(obj);
}

void Model::ChangeRequirement(const ID& req, const Array<double>& params) const {
	reqCtrl->SetReqParams(req, params);
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
