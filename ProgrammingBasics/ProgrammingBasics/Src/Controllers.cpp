#include "ID.h"
#include "Primitives.h"
#include "Requirement.h"

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

	}
}


PrimController* PrimController::instance = nullptr;

PrimController::PrimController() {
	objCtrl = ObjectController::GetInstance();
}

bool PrimController::IsPrimitive(object_type type) {
	return	(type == ot_point)		||
			(type == ot_segment)	||
			(type == ot_arc)		||
			(type == ot_circle);
}

Primitive* PrimController::ConvertToPrimitive(Object* obj) {
	bool isPrim = IsPrimitive(obj->GetType());
	if (!isPrim) {
		// ERROR
	}
	return static_cast<Primitive*>(obj);
}

Primitive* PrimController::GetPrimitive(const ID& id) {
	Object* obj = objCtrl->GetObject(id);
	return ConvertToPrimitive(obj);
}

PrimController* PrimController::GetInstance() {
	if (instance == nullptr) {
		instance = new PrimController;
	}
	return instance;
}

Array<double*> PrimController::GetPrimitiveParamsAsPointers(const ID& id) {
	object_type type = objCtrl->GetType(id);
	switch (type) {
	case ot_point: {
		Object* obj = objCtrl->GetObject(id);
		Point* point = static_cast<Point*>(obj);

		Array<double*> params(2);
		params[0] = &point->x;
		params[1] = &point->y;

		return params;
	}
	case ot_segment: {
		return Array<double*>(0);
	}
	case ot_arc: {
		return Array<double*>(0);
	}
	case ot_circle: {
		Object* obj = objCtrl->GetObject(id);
		Circle* circle = static_cast<Circle*>(obj);

		Array<double*> params(1);
		params[0] = &circle->radius;

		return params;
		break;
	}
	default: {
		// ERROR
	}
	}
}

void PrimController::SetPrimitiveParams(const ID&, const Array<double>&) {}

ID PrimController::CreatePrimitive(object_type type, const Array<double>& params) {
	Object* obj;
	switch (type) {
	case ot_point: {
		obj = new Point(params[0], params[1]);
		break;
	}
	case ot_segment: {
		Point* point1 = new Point(params[0], params[1]);
		Point* point2 = new Point(params[2], params[3]);
		obj = new Segment(point1, point2);
		break;
	}
	case ot_arc: {
		Point* point1 = new Point(params[0], params[1]);
		Point* point2 = new Point(params[2], params[3]);
		obj = new Arc(point1, point2, params[4]);
		break;
	}
	case ot_circle: {
		Point* point = new Point(params[0], params[1]);
		obj = new Circle(point, params[2]);
		break;
	}
	default: {
		// ERROR
	}
	}
	return obj->GetID();
}





