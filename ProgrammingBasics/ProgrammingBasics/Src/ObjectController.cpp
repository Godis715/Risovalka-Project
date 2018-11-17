#include "ID.h"

ObjectController* ObjectController::GetInstance() {
	if (instance == nullptr) {
		instance = new ObjectController;
	}
	return instance;
}

ObjectController* ObjectController::instance = nullptr;

ObjectController::ObjectController() {

}

Object* ObjectController::GetObject(const ID& id) const {
	return id.object;
}

object_type ObjectController::GetType(const ID& id) const {
	Object* obj = id.object;
	if (obj != nullptr) {
		return obj->GetType();
	}
	else {
		LOGERROR("GetType: object is not exist", LEVEL_1);
	}
}

void ObjectController::SetObjParam(const ID& obj, const Array<double>& params) {
	obj.object->SetParams(params);
}

Array<double> ObjectController::GetObjParam(const ID& obj) {
	return obj.object->GetParams();
}

Array<ID> ObjectController::GetObjChildren(const ID& obj) {
	return obj.object->GetChildren();
}

void ObjectController::DeleteObj(ID& id) const {
	Object* obj = id.object;
	if (obj != nullptr) {
		delete obj;
		id.object = nullptr;
		id.hash = 0;
	}
}


bool ObjectController::IsValid(const ID& id) {
	return ((id.hash > 0) && (id.object->isValid));
}

void ObjectController::MakeInValid(ID& id) {
	id.object->isValid = false;
}

void ObjectController::MakeValid(ID& id) {
	if (id.hash > 0) {
		id.object->isValid = true;
	}
}