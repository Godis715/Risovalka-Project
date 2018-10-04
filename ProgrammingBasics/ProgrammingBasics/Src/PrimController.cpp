#include "Primitives.h"

PrimController* PrimController::instance = nullptr;

PrimController::PrimController() {
	objCtrl = ObjectController::GetInstance();
}

Array<double*> PrimController::GetPrimitiveDoubleParamsAsPointers(const ID& obj) const {
	Primitive* prim = GetPrimitive(obj);
	return prim->GetDoubleParamsAsPointers();
}

bool PrimController::IsPrimitive(object_type type) const {
	return	(type == ot_point) ||
		(type == ot_segment) ||
		(type == ot_arc) ||
		(type == ot_circle);
}

bool PrimController::IsPrimitive(const ID& obj) const {
	return IsPrimitive(objCtrl->GetType(obj));
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

Array<double> PrimController::GetPrimParamsForDrawing(const ID& id) const {
	if (!IsPrimitive(id)) {
		LOGERROR("GetPrimParamsForDrawing: object is not primitive", LEVEL_1);
	}
	Array<ID> children = GetChildren(id);
	Array<double> params(0);
	for (int i = 0; i < children.GetSize(); ++i) {
		params = params + GetPrimitiveParamsAsValues(children[i]);
	}
	params = params + GetPrimitiveParamsAsValues(id);
	if (objCtrl->GetType(id) == ot_arc) {
		Arc* arc = dynamic_cast<Arc*>(GetPrimitive(id));
		params = params + arc->cx + arc->cy;
	}
	return params;
}

Array<double> PrimController::GetPrimitiveParamsAsValues(const ID& id) const {
	/*
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
	} */
	return objCtrl->GetObjParam(id);
}

Array<double> PrimController::GetVariableObjParam(const ID& obj, int modifiers... ) const {
	return GetVariableObjParam(obj, &modifiers);
}

/*
support method
takes mofidiers of expected parameters
such as COORDS, CENTER...
*/
Array<double> PrimController::GetVariableObjParam(const ID& obj, int modifiers[]) const {
	Array<double> params(0);
	switch (objCtrl->GetType(obj)) {
	case ot_point: {
		for (int i = 0; modifiers[i] != 0; ++i) {
			switch (modifiers[i]) {
			case VERTEX: {
				Point* point = dynamic_cast<Point*>(GetPrimitive(obj));
				auto pos = point->GetPos();
				params = params + CreateArr(pos.x, pos.y);
				break;
			}
			default: {
				LOGERROR("PrimController:GetVariableObjParam: not appropriate param modifier", LEVEL_1);
			}
			}
		}
		break;
	}
	case ot_segment: {
		Segment* segment = dynamic_cast<Segment*>(GetPrimitive(obj));
		for (int i = 0; modifiers[i] != 0; ++i) {
			switch (modifiers[i]) {
			case VERTEX: {
				auto pos1 = segment->GetPointPos1();
				auto pos2 = segment->GetPointPos2();
				params = params + CreateArr(pos1.x, pos1.y, pos2.x, pos2.y);
				break;
			}
			default: {
				LOGERROR("PrimController:GetVariableObjParam: not appropriate param modifier", LEVEL_1);
			}
			}
		}
		break;
	}
	case ot_arc: {
		Arc* arc = dynamic_cast<Arc*>(GetPrimitive(obj));
		for (int i = 0; modifiers[i] != 0; ++i) {
			switch (modifiers[i]) {
			case VERTEX: {
				auto pos1 = arc->GetPointPos1();
				auto pos2 = arc->GetPointPos2();
				params = params + CreateArr(pos1.x, pos1.y, pos2.x, pos2.y);
				break;
			}
			case CENTER: {
				auto center = arc->GetCenter();
				params = params + CreateArr(center.x, center.y);
				break;
			}
			case ANGLE: {
				auto angle = arc->GetAngle();
				params = params + CreateArr(angle);
				break;
			}
			case RADIUS: {
				// ...
				break;
			}
			default: {
				LOGERROR("PrimController:GetVariableObjParam: not appropriate param modifier", LEVEL_1);
			}
			}
		}
		break;
	}
	case ot_circle: {
		Circle* circle = dynamic_cast<Circle*>(GetPrimitive(obj));
		for (int i = 0; modifiers[i] != 0; ++i) {
			switch (modifiers[i]) {
			case CENTER: {
				auto center = circle->GetCenter();
				params = params + CreateArr(center.x, center.y);
				break;
			}
			case RADIUS: {
				auto radius = circle->GetRadius();
				params = params + CreateArr(radius);
				break;
			}
			default: {
				LOGERROR("PrimController:GetVariableObjParam: not appropriate param modifier", LEVEL_1);
			}
			}
		}
		break;
	}
	default: {
		LOGERROR("PrimController:GetVariableObjParam: unexpected type", LEVEL_1);
	}
	}
	return params;
}

Array<double*> PrimController::GetPrimitiveParamsAsPointers(const ID& id) const {
	object_type type = objCtrl->GetType(id);
	switch (type) {
	case ot_point: {

		Object* obj = objCtrl->GetObject(id);
		Point* point = static_cast<Point*>(obj);

		Array<double*> params = CreateArr(point->x, point->y);

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

		Array<double*> params = CreateArr(circle->radius);
		
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

void PrimController::SetPrimitiveParams(const ID& obj, const Array<double>& params) const {
	
}

void PrimController::ApplyPrimitiveDoubleParams(const ID& obj) const {
	Primitive* prim = GetPrimitive(obj);
	prim->ApplyDoubleParams();
}

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

Array<ID> PrimController::GetChildren(const ID& obj) const {
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

double PrimController::GetDistanceToPoint(const ID& obj, double x, double y) const {
	Primitive* prim = GetPrimitive(obj);
	return prim->GetDist(Vector2(x, y));
}
