#include "Model.h"
#include <stdexcept>


ID Model::createObject(Type T, Array<double> params) {
	switch (T.GetTypeId())
	{
	case point: {
		Point* _point;
		try {
			_point = new Point(params[0], params[1]);
		}
		catch (std::out_of_range) {
			throw std::invalid_argument("Invalid parameters");
		}
		data.pushBack(_point);
		return _point->GetId();
		break;
	}
	case segment: {
		Point* _point = new Point(params.popBack(), params.popBack());
		data.pushBack(_point);
		return _point->GetId();
		break;
	}
	default:
		break;
	}
}

bool Model::getNearest(double x, double y, ID& obj_id) {
	if (data.getSize() != 0) {
		Vector2 pos(x, y);
		ID nearestObject = data[0]->GetId();
		double minDist = data[0]->GetDistance(pos);
		for (int i = 1; i < data.getSize(); ++i) {
			double dist = data[i]->GetDistance(pos);
			if (minDist > dist) {
				minDist = dist;
				nearestObject = data[i]->GetId();
			}
		}
		obj_id = nearestObject;
		return true;
	}
	else
	{
		return false;
	}
}

// NEED TO DEVELOP
bool Model::getObjType(ID obg_id, Type& type) {
	Primitive* obj = nullptr;
	bool isFound = false;// = data.find(obj_id, obj);
	if (isFound) {
		type = obj->GetType();
		return true;
	}
	else {
		return false;
	}
}

bool Model::getObjParam(ID obj_id, Array<double>& result) {
	Primitive* obj = nullptr;
	bool isFound = false;// = data.find(obj_id, obj);
	if (isFound) {
		switch (obj->GetType().GetTypeId()) {
		case point: {
			Point* point = dynamic_cast<Point*>(obj);
			result.clear();
			Vector2 pos = point->GetPosition();
			result.pushBack(pos.x);
			result.pushBack(pos.y);
			return true;
			break;
		}
		case segment: {
			Segment* segment = dynamic_cast<Segment*>(obj);
			result.clear();
			Vector2 pos1 = segment->GetPoint1_pos();
			Vector2 pos2 = segment->GetPoint2_pos();
			result.pushBack(pos1.x);
			result.pushBack(pos1.y);
			result.pushBack(pos2.x);
			result.pushBack(pos2.y);
			break;
		}
		case arc: {
			Arc* arc = dynamic_cast<Arc*>(obj);
			result.clear();
			Vector2 pos1 = arc->GetPoint1_pos();
			Vector2 pos2 = arc->GetPoint2_pos();
			double angle = arc->GetAngle();
			result.pushBack(pos1.x);
			result.pushBack(pos1.y);
			result.pushBack(pos2.x);
			result.pushBack(pos2.y);
			result.pushBack(angle);
			break;
		}
		default: {
			return false;
		}
		}
	}
	else {
		return false;
	}
}