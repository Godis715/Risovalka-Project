#include "Requirement.h"

ReqController* ReqController::instance = nullptr;

ReqController::ReqController() {
	objCtrl = ObjectController::GetInstance();
	primCtrl = PrimController::GetInstance();
}

Requirement* ReqController::GetReq(const ID& id) const {
	Object* obj = objCtrl->GetObject(id);
	return ConvertToReq(obj);
}

Requirement* ReqController::ConvertToReq(Object* obj) const {
	bool isReq = IsReq(obj->GetType());
	if (!isReq) {
		LOGERROR("ConvertToReq: object is not requirement", LEVEL_1);
	}
	return static_cast<Requirement*>(obj);
}

bool ReqController::IsReq(object_type type) const {
	return type == ot_connection ||
		type == ot_distBetPoints ||
		type == ot_equalSegmentLen ||
		type == ot_pointPosReq ||
		type == ot_pointsOnTheOneHand ||
		type == ot_distBetPointSeg ||
		type == ot_distBetPointArc ||
		type == ot_angleBetSeg ||
		type ==  ot_equalPointPosReq;
}

bool ReqController::IsReq(const ID& obj) const {
	return IsReq(objCtrl->GetType(obj));
}

ReqController* ReqController::GetInstance() {
	if (instance == nullptr) {
		instance = new ReqController;
	}
	return instance;
}

Array<double> ReqController::GetReqParamsAsValues(const ID& id) const {
	Requirement* req = GetReq(id);
	return req->params;
}

Array<double> ReqController::GetGradient(const ID& obj) const {
	Requirement* req = GetReq(obj);
	return req->Gradient();
}

Array<double*> GetReqArgsValues(const ID&);

Array<double*> ReqController::GetReqArgsAsPointers(const ID& obj) const {
	Requirement* req = GetReq(obj);
	Array<double*> activeArgs(0);
	for (int i = 0; i < req->objects.GetSize(); ++i) {
		activeArgs = activeArgs + primCtrl->GetPrimitiveDoubleParamsAsPointers(req->objects[i]);
	}
	return activeArgs;
}

double ReqController::GetReqError(const ID& obj) const {
	Requirement* req = GetReq(obj);
	return req->error();
}

double ReqController::GetReqError(const Array<ID>& objs) const {
	double err = 0.0;
	for (int i = 0; i < objs.GetSize(); ++i) {
		err += GetReqError(objs[i]);
	}
	return err;
}

void ReqController::SetReqParams(const ID& obj, const Array<double>& params) const {
	Requirement* req = GetReq(obj);
	req->SetParams(params);
}

void ReqController::ApplyChanges(const ID& obj) const {
	Requirement* req = GetReq(obj);
	auto children = req->objects;
	for (int i = 0; i < children.GetSize(); ++i) {
		primCtrl->ApplyPrimitiveDoubleParams(children[i]);
	}
}

ID ReqController::CreateReq
	(object_type type,
	const Array<ID>& objects,
	const Array<double>& params) const
{
	Object* obj = nullptr;
	switch (type) {
	case ot_distBetPoints: {
		LOG("CreateReq: started creating distBetPoints", LEVEL_3);
		if (params.GetSize() != 1) {
			LOGERROR("CreateReq: bad size of params", LEVEL_1);
		}
		if (objects.GetSize() != 2) {
			LOGERROR("CreateReq: bad size of objects", LEVEL_1);
		}
		if (objCtrl->GetType(objects[0]) != ot_point ||
			objCtrl->GetType(objects[1]) != ot_point) {
			LOGERROR("CreateReq: bad type of one object", LEVEL_1);
		}
		obj = dynamic_cast<Object*>(new DistBetPointsReq(objects, params));
		LOG("CreateReq: created DistBetPointsReq", LEVEL_2);
		break;
	}
	case ot_equalPointPosReq: {
		LOG("CreateReq: started creating equalPointPosReq", LEVEL_3);
		if (params.GetSize() != 0) {
			LOGERROR("CreateReq: bad size of params", LEVEL_1);
		}
		if (objects.GetSize() != 2) {
			LOGERROR("CreateReq: bad size of objects", LEVEL_1);
		}
		if (objCtrl->GetType(objects[0]) != ot_point ||
			objCtrl->GetType(objects[1]) != ot_point) {
			LOGERROR("CreateReq: bad type of one object", LEVEL_1);
		}
		obj = dynamic_cast<Object*>(new EqualPointsPositionReq(objects, params));
		LOG("CreateReq: created equalPointPosReq", LEVEL_2);
		break;
	}
	case ot_segmentTouchCircle: {
		LOG("CreateReq: started creating segmentTouchCircle", LEVEL_3);
		if (params.GetSize() != 0) {
			LOGERROR("CreateReq: bad size of params", LEVEL_1);
		}
		if (objects.GetSize() != 2) {
			LOGERROR("CreateReq: bad size of objects", LEVEL_1);
		}
		if (objCtrl->GetType(objects[0]) != ot_segment ||
			objCtrl->GetType(objects[1]) != ot_circle) {
			LOGERROR("CreateReq: bad type of one object", LEVEL_1);
		}
		obj = dynamic_cast<Object*>(new SegmentTouchCircle(objects, params));
		LOG("CreateReq: created SegmentTouchCircle", LEVEL_2);
		break;
	}
	case ot_pointPosReq: {
		LOG("CreateReq: started creating pointPosReq", LEVEL_3);
		if (params.GetSize() != 2) {
			LOGERROR("CreateReq: bad size of params", LEVEL_1);
		}
		if (objects.GetSize() != 1) {
			LOGERROR("CreateReq: bad size of objects", LEVEL_1);
		}
		if (objCtrl->GetType(objects[0]) != ot_point) {
			LOGERROR("CreateReq: bad type of one object", LEVEL_1);
		}
		obj = dynamic_cast<Object*>(new PointPosReq(objects, params));
		LOG("CreateReq: created pointPosReq", LEVEL_2);
		break;
	}
	case ot_equalSegmentLen: {
		LOG("CreateReq: started creating equalSegmentLen", LEVEL_3);
		if (params.GetSize() != 0) {
			LOGERROR("CreateReq: bad size of params", LEVEL_1);
		}
		if (objects.GetSize() != 2) {
			LOGERROR("CreateReq: bad size of objects", LEVEL_1);
		}
		if (objCtrl->GetType(objects[0]) != ot_segment ||
			objCtrl->GetType(objects[1]) != ot_segment) {
			LOGERROR("CreateReq: bad type of one object", LEVEL_1);
		}
		obj = dynamic_cast<Object*>(new EqualSegmentLenReq(objects, params));
		LOG("CreateReq: created equalSegmentLen", LEVEL_2);
		break;
	}
	case ot_pointsOnTheOneHand: {
		LOG("CreateReq: started creating pointsOnTheOneHand", LEVEL_3);
		if (params.GetSize() != 0) {
			LOGERROR("CreateReq: bad size of params", LEVEL_1);
		}
		if (objects.GetSize() != 3) {
			LOGERROR("CreateReq: bad size of objects", LEVEL_1);
		}
		if (objCtrl->GetType(objects[0]) != ot_segment ||
			objCtrl->GetType(objects[1]) != ot_point ||
			objCtrl->GetType(objects[2]) != ot_point) {
			LOGERROR("CreateReq: bad type of one object", LEVEL_1);
		}
		obj = dynamic_cast<Object*>(new PointsOnTheOneHand(objects, params));
		LOG("CreateReq: created pointsOnTheOneHand", LEVEL_2);
		break;
	}
	case ot_distBetPointSeg: {
		LOG("CreateReq: started creating distBetPointSeg", LEVEL_3);
		if (params.GetSize() != 1) {
			LOGERROR("CreateReq: bad size of params", LEVEL_1);
		}
		if (objects.GetSize() != 1) {
			LOGERROR("CreateReq: bad size of objects", LEVEL_1);
		}
		if (objCtrl->GetType(objects[0]) != ot_segment) {
			LOGERROR("CreateReq: bad type of one object", LEVEL_1);
		}
		obj = dynamic_cast<Object*>(new DistanceBetweenPointSegment(objects, params));
		LOG("CreateReq: created distBetPointSeg", LEVEL_2);
		break;
	}
	case ot_angleBetSeg: {
		LOG("CreateReq: started creating angleBetweenSegments", LEVEL_3);
		if (params.GetSize() != 0) {
			LOGERROR("CreateReq: bad size of params", LEVEL_1);
		}
		if (objects.GetSize() != 2) {
			LOGERROR("CreateReq: bad size of objects", LEVEL_1);
		}
		if (objCtrl->GetType(objects[0]) != ot_segment ||
			objCtrl->GetType(objects[1]) != ot_segment) {
			LOGERROR("CreateReq: bad type of one object", LEVEL_1);
		}
		obj = dynamic_cast<Object*>(new AngleBetweenSegments(objects, params));
		LOG("CreateReq: created equalSegmentLen", LEVEL_2);
		break;
	}
	default: {
		LOGERROR("CreateReq: bad type of requirement", LEVEL_1);
	}
	}
	return obj->GetID();
}