#include "ID.h"

ObjectController* ObjectController::GetInstance() {
	if (instance == nullptr) {
		instance = new ObjectController;
	}
	return instance;
}

ObjectController* ObjectController::instance = nullptr;

ObjectController::ObjectController() { }

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

void ObjectController::DeleteObj(ID& id) const {
	if (id.object != nullptr) {
		delete id.object;
		id.object = nullptr;
		id.hash = 0;
	}
}
