#include "Primitives.h"

PrimController* PrimController::instance = nullptr;

PrimController::PrimController() {
	objCtrl = ObjectController::GetInstance();
}

bool PrimController::IsPrimitive(object_type type) const {
	return	(type == ot_point) ||
		(type == ot_segment) ||
		(type == ot_arc) ||
		(type == ot_circle);
}

Primitive* PrimController::ConvertToPrimitive(Object* obj) const {
	bool isPrim = IsPrimitive(obj->GetType());
	if (!isPrim) {
		LOGERROR("ConvertToPrimitive: the object is not primitive", LEVEL_1);
	}
	return static_cast<Primitive*>(obj);
}

Primitive* PrimController::GetPrimitive(const ID& id) const {
	Object* obj = objCtrl->GetObject(id);
	return ConvertToPrimitive(obj);
}

PrimController* PrimController::GetInstance() {
	if (instance == nullptr) {
		instance = new PrimController;
	}
	return instance;
}

Array<double> PrimController::GetPrimitiveParamsAsValues(const ID& id) const {
	object_type type = objCtrl->GetType(id);
	switch (type) {
	case ot_point: {

		Object* obj = objCtrl->GetObject(id);
		Point* point = static_cast<Point*>(obj);

		Array<double> params = CreateArr(point->x, point->y);
		
		return params;
	}
	case ot_segment: {
		return Array<double>(0);
	}
	case ot_arc: {
		return Array<double>(0);
	}
	case ot_circle: {
		Object* obj = objCtrl->GetObject(id);
		Circle* circle = static_cast<Circle*>(obj);

		Array<double> params = CreateArr(circle->radius);
		
		return params;
		break;
	}
	default: {
		LOGERROR("GetPrimitiveParamsAsValues: object is not primitive", LEVEL_1);
	}
	}
	return Array<double>(0);
}

Array<double*> PrimController::GetPrimitiveParamsAsPointers(const ID& id) const {
	object_type type = objCtrl->GetType(id);
	switch (type) {
	case ot_point: {

		Object* obj = objCtrl->GetObject(id);
		Point* point = static_cast<Point*>(obj);

		Array<double*> params = CreateArr(&point->x, &point->y);

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

		Array<double*> params = CreateArr(&circle->radius);
		
		return params;
		break;
	}
	default: {
		LOGERROR("GetPrimitiveParamsAsPointers: object is not primitive", LEVEL_1);
	}
	}
	return Array<double*>(0);
}

Array<double*> PrimController::GetPrimitiveParamsAsPointers(const Array<ID>& ids, int paramsNumber) const {
	Array<double*> allParams(paramsNumber);
	int allParamsIter = 0;
	for (int i = 0; i < ids.GetSize(); ++i) {
		Array<double*> objParams = GetPrimitiveParamsAsPointers(ids[i]);
		for (int j = 0; j < objParams.GetSize(); ++j, ++allParamsIter) {
			allParams[allParamsIter] = objParams[j];
		}
	}
	if (allParamsIter != paramsNumber) {
		LOGERROR("GetPrimitiveParamsAsPointers: paramsNumber is not correct", LEVEL_1);
	}
	return allParams;
}

void PrimController::SetPrimitiveParams(const ID&, const Array<double>&) const {}

ID PrimController::CreatePrimitive(object_type type, const Array<ID>& dependObjs, const Array<double>& params) const {
	Primitive* prim = nullptr;
	switch (type) {
	case ot_point: {
		if (params.GetSize() != 2) {
			LOGERROR("CreatePrimitive: bad size of params", LEVEL_1);
		}
		prim = new Point(params[0], params[1]);
		LOG("CreatePrimitive: created point", LEVEL_2);
		break;
	}
	case ot_segment: {
		if (dependObjs.GetSize() == 0) {
			if (params.GetSize() != 4) {
				LOGERROR("CreatePrimitive: bad size of params", LEVEL_1);
			}
			Point* point1 = new Point(params[0], params[1]);
			Point* point2 = new Point(params[2], params[3]);
			prim = new Segment(point1, point2);
		}
		else {
			if (params.GetSize() != 0) {
				LOGERROR("CreatePrimitive: bad size of params", LEVEL_1);
			}
			if (dependObjs.GetSize() != 2) {
				LOGERROR("CreatePrimitive: bad size of dependent objs", LEVEL_1);
			}
			if (objCtrl->GetType(dependObjs[0]) != ot_point ||
				objCtrl->GetType(dependObjs[1]) != ot_point) {
				LOGERROR("CreatePrimitive: bad type of dependent object", LEVEL_1);
			}
			Point* point1 = dynamic_cast<Point*>(GetPrimitive(dependObjs[0]));
			Point* point2 = dynamic_cast<Point*>(GetPrimitive(dependObjs[1]));
			prim = new Segment(point1, point2);
		}
		LOG("CreatePrimitive: created segment", LEVEL_2);
		break;
	}
	case ot_arc: {
		if (dependObjs.GetSize() == 0) {
			if (params.GetSize() != 5) {
				LOGERROR("CreatePrimitive: bad size of params", LEVEL_1);
			}
			Point* point1 = new Point(params[0], params[1]);
			Point* point2 = new Point(params[2], params[3]);
			prim = new Arc(point1, point2, params[4]);
		}
		else {
			if (params.GetSize() != 1) {
				LOGERROR("CreatePrimitive: bad size of params", LEVEL_1);
			}
			if (dependObjs.GetSize() != 2) {
				LOGERROR("CreatePrimitive: bad size of dependent objs", LEVEL_1);
			}
			if (objCtrl->GetType(dependObjs[0]) != ot_point ||
				objCtrl->GetType(dependObjs[1]) != ot_point) {
				LOGERROR("CreatePrimitive: bad type of dependent object", LEVEL_1);
			}
			Point* point1 = dynamic_cast<Point*>(GetPrimitive(dependObjs[0]));
			Point* point2 = dynamic_cast<Point*>(GetPrimitive(dependObjs[1]));
			prim = new Arc(point1, point2, params[0]);
		}
		LOG("CreatePrimitive: created arc", LEVEL_2);

		break;
	}
	case ot_circle: {
		if (dependObjs.GetSize() == 0) {
			if (params.GetSize() != 3) {
				LOGERROR("CreatePrimitive: bad size of params", LEVEL_1);
			}
			Point* point = new Point(params[0], params[1]);
			prim = new Circle(point, params[2]);
		}
		else {
			if (params.GetSize() != 1) {
				LOGERROR("CreatePrimitive: bad size of params", LEVEL_1);
			}
			if (dependObjs.GetSize() != 1) {
				LOGERROR("CreatePrimitive: bad size of dependent objs", LEVEL_1);
			}
			if (objCtrl->GetType(dependObjs[0]) != ot_point) {
				LOGERROR("CreatePrimitive: bad type of dependent object", LEVEL_1);
			}
			Point* point = dynamic_cast<Point*>(GetPrimitive(dependObjs[0]));
			prim = new Circle(point, params[0]);
		}
		LOG("CreatePrimitive: created circle", LEVEL_2);

		break;
	}
	default: {
		LOGERROR("CreatePrimitive: bad type of primitive", LEVEL_1);
	}
	}
	return prim->GetID();
}

Array<ID> PrimController::GetChildren(const ID& obj) {
	switch (objCtrl->GetType(obj)) {
	case ot_point: {
		return Array<ID>(0);
	}
	case ot_segment: {
		Segment* seg = static_cast<Segment*>(GetPrimitive(obj));
		Array<ID> children = CreateArr(seg->point1->GetID(), seg->point2->GetID());
		return children;
	}
	case ot_arc: {
		Arc* arc = static_cast<Arc*>(GetPrimitive(obj));
		Array<ID> children = CreateArr(arc->point1->GetID(), arc->point2->GetID());
		return children;
	}
	case ot_circle: {
		Circle* circle = static_cast<Circle*>(GetPrimitive(obj));
		Array<ID> children = CreateArr(circle->center->GetID());
		return children;
	}
	default: {
		LOGERROR("GetChildren: object was not primitive", LEVEL_1);
	}
	}
	return Array<ID>(0);
}