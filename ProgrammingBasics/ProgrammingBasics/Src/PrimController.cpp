#include "Primitives.h"

using namespace DrawProject;

PrimController* PrimController::instance = nullptr;

PrimController::PrimController() {
	objCtrl = ObjectController::GetInstance();
}

void PrimController::Activate(const ID& obj) const {
	Primitive* prim = GetPrimitive(obj);
	prim->Activate();
}

void PrimController::Deactivate(const ID& obj) const {
	Primitive* prim = GetPrimitive(obj);
	prim->Deactivate();
}

bool PrimController::IsActivated(const ID& obj) const {
	Primitive* prim = GetPrimitive(obj);
	return prim->IsActivated();
}

Array<double*> PrimController::GetPrimitiveDoubleParamsAsPointers(const ID& obj) const {
	if (IsActivated(obj)) {
		Primitive* prim = GetPrimitive(obj);
		return prim->GetDoubleParamsAsPointers();
	}
	else {
		return Array<double*>(0);
	}
}

bool PrimController::IsPrimitive(object_type type) const {
	return	(type == ot_point) ||
		(type == ot_segment) ||
		(type == ot_arc) ||
		(type == ot_circle) ||
		(type == ot_curve);
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
		params += GetPrimitiveParamsAsValues(children[i]);
	}
	params += GetPrimitiveParamsAsValues(id);
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
				params += CreateArr(pos1.x, pos1.y, pos2.x, pos2.y);
				break;
			}
			case CENTER: {
				auto center = arc->GetCenter();
				params += CreateArr(center.x, center.y);
				break;
			}
			case ANGLE: {
				auto angle = arc->GetAngle();
				params += CreateArr(angle);
				break;
			}
			case RADIUS: {
				auto center = arc->GetCenter();
				auto pos1 = arc->GetPointPos1();
				params += CreateArr((center - pos1).GetLength());
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
	case ot_curve: {
		Curve* curve = dynamic_cast<Curve*>(GetPrimitive(obj));
		for (int i = 0; modifiers[i] != 0; ++i) {
			switch (modifiers[i]) {
			case VERTEX: {
				params = curve->GetPointDoubles();
				break;
			}
			case CURVE_AS_IT_IS: {
				params = curve->GetCurveAsItIs();
				break;
			}
			case CURVE_PARAMS: {
				params = curve->GetCurveParams();
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

void PrimController::SetVariableObjParam(const ID& obj, const Array<double>& params, int modifiers...) const {
	SetVariableObjParam(obj, params, &modifiers);
}

void PrimController::SetVariableObjParam(const ID& obj, const Array<double>& params, int modifiers[]) const {
	switch (objCtrl->GetType(obj)) {
	case ot_point: {
		for (int i = 0; modifiers[i] != 0; ++i) {
			switch (modifiers[i]) {
			case VERTEX: {
				Point* point = dynamic_cast<Point*>(GetPrimitive(obj));
				point->SetPos(params[0], params[1]);
				break;
			}
			default: {
				LOGERROR("PrimController:SetVariableObjParam: not appropriate param modifier", LEVEL_1);
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
				segment->SetPointPos1(params[0], params[1]);
				segment->SetPointPos2(params[2], params[3]);
				break;
			}
			default: {
				LOGERROR("PrimController:SetVariableObjParam: not appropriate param modifier", LEVEL_1);
			}
			}
		}
		break;
	}
	case ot_arc: {
		int index = 0;
		Arc* arc = dynamic_cast<Arc*>(GetPrimitive(obj));
		for (int i = 0; modifiers[i] != 0; ++i) {
			switch (modifiers[i]) {
			case VERTEX: {
				arc->SetPointPos1(params[index], params[index + 1]);
				index += 2;
				arc->SetPointPos2(params[index], params[index + 1]);
				index += 2;
				break;
			}
			case CENTER: {
			/*	auto center = arc->GetCenter();
				params = params + CreateArr(center.x, center.y);*/
				break;
			}
			case ANGLE: {
				arc->SetAngle(params[index++]);
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
		int index = 0;
		Circle* circle = dynamic_cast<Circle*>(GetPrimitive(obj));
		for (int i = 0; modifiers[i] != 0; ++i) {
			switch (modifiers[i]) {
			case CENTER: {

				circle->SetCenterPos(params[index], params[index + 1]);
				index += 2;
				break;
			}
			case RADIUS: {
				auto radius = circle->GetRadius();
				circle->SetRadius(params[index++]);
				break;
			}
			default: {
				LOGERROR("PrimController:GetVariableObjParam: not appropriate param modifier", LEVEL_1);
			}
			}
		}
		break;
	}
	case ot_curve: {
		Curve* curve = dynamic_cast<Curve*>(GetPrimitive(obj));
		for (int i = 0; modifiers[i] != 0; ++i) {
			switch (modifiers[i]) {
			case VERTEX: {
				//curve->SetPointPositions(params);
				break;
			}
			case CURVE_AS_IT_IS: {
				curve->SetCurveAsItIs(params);
				break;
			}
			case CURVE_PARAMS: {
				curve->SetCurveParams(params);
				break;
			}
			default: {
				LOGERROR("PrimController:SetVariableObjParam: not appropriate param modifier", LEVEL_1);
			}
			}
		}
		break;
	}
	default: {
		LOGERROR("PrimController:GetVariableObjParam: unexpected type", LEVEL_1);
	}
	}
}

Array<double*> PrimController::GetPrimitiveParamsAsPointers(const ID& id) const {
	if (IsActivated(id)) {
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
	else {
		return Array<double*>(0);
	}
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
	auto paramsPointers = GetPrimitiveDoubleParamsAsPointers(obj);
	if (paramsPointers.GetSize() != params.GetSize()) {
		LOG("SetPrimitiveParams: incorrect number of params", LEVEL_1);
	}
	for (int i = 0; i < params.GetSize(); ++i) {
		*paramsPointers[i] = params[i];
	}
	ApplyPrimitiveDoubleParams(obj);
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
	case ot_curve: {
		if (dependObjs.GetSize() == 0) {
			if (params.GetSize() < 6 || params.GetSize() % 2 == 1) {
				LOGERROR("CreatePrimitive: bad size of params", LEVEL_1);
			}
			int countParams = params.GetSize();
			Array<Point*> points = Array<Point*>((countParams + 4) / 6);
			Array<double> coordControlPoints = Array<double>(countParams - points.GetSize() * 2);
			int indexControlPoints = 0;
			int indexPoints = 0;
			for (int i = 0; i < countParams - 2; i += 6) {
				points[indexPoints++] = new Point(params[i], params[i + 1]);
				coordControlPoints[indexControlPoints++] = params[i + 2];
				coordControlPoints[indexControlPoints++] = params[i + 3];
				coordControlPoints[indexControlPoints++] = params[i + 4];
				coordControlPoints[indexControlPoints++] = params[i + 5];
			}
			points[indexPoints] = new Point(params[countParams - 2], params[countParams - 1]);
			prim = new Curve(points, coordControlPoints);
		}
		else {
			if (params.GetSize() != 0) {
				LOGERROR("CreatePrimitive: bad size of params", LEVEL_1);
			}
			Array<Point*> points = Array<Point*>(dependObjs.GetSize());
			for (int i = 0; i < points.GetSize(); ++i) {
				points[i] = dynamic_cast<Point*>(GetPrimitive(dependObjs[i]));
			}
			prim = new Curve(points, params);
		}
		LOG("CreatePrimitive: created segment", LEVEL_2);
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
	case ot_curve: {
		Curve* curve = static_cast<Curve*>(GetPrimitive(obj));
		return curve->GetPointIDs();
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

