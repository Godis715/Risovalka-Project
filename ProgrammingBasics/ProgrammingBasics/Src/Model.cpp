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