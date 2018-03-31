#include "Model.h"
#include <stdexcept>


ID Model::createObject(type_id type, Array<double> params) {
	switch (type)
	{
	case point: {
		Point* _point;
		try {
			_point = new Point(params[0], params[1]);
		}
		catch (std::out_of_range) {
			throw std::invalid_argument("Invalid parameters");
		}
		data.Add(_point->GetId(),_point);
		return _point->GetId();
		break;
	}
	case segment: {
		//REWRITE AND FINISH!!!
		Point* _point = new Point(params.popBack(), params.popBack());
		//data.pushBack(_point);
		return _point->GetId();
		break;
	}
	default:
		break;
	}
}

void Model::createRequirement(const Requirement_id _id, Array<Primitive*> primitives, Array<double>params) {
	switch (_id)
	{
	case distBetPoints: {
		DistanceBetweenPoints* Requirement;
		try {
			
			Requirement = new DistanceBetweenPoints(*dynamic_cast<Point*>(primitives[0]), *dynamic_cast<Point*>(primitives[1]), params[0]);
		}
		catch (std::out_of_range) {
			throw std::invalid_argument("Invalid parameters");
		}
		dataReq.pushBack(Requirement);
		return;
	}
	case pointsOnTheOneHand: {
		PointsOnTheOneHand* Requirement;
		try {
			Requirement = new PointsOnTheOneHand(*dynamic_cast<Segment*>(primitives[0]), *dynamic_cast<Point*>(primitives[1]), *dynamic_cast<Point*>(primitives[2]));
		}
		catch (std::out_of_range) {
			throw std::invalid_argument("Invalid parameters");
		}
		dataReq.pushBack(Requirement);
		return;
	}
	case distBetPointSeg: {
		DistanceBetweenPointSegment* Requirement;
		try {

			Requirement = new DistanceBetweenPointSegment(*dynamic_cast<Segment*>(primitives[0]), *dynamic_cast<Point*>(primitives[1]), params[0]);
		}
		catch (std::out_of_range) {
			throw std::invalid_argument("Invalid parameters");
		}
		dataReq.pushBack(Requirement);
		return;
	}
	case angleBetSeg: {
		AngleBetweenSegments* Requirement;
		try {

			Requirement = new AngleBetweenSegments(*dynamic_cast<Segment*>(primitives[0]), *dynamic_cast<Segment*>(primitives[1]), params[0]);
		}
		catch (std::out_of_range) {
			throw std::invalid_argument("Invalid parameters");
		}
		dataReq.pushBack(Requirement);
		return;
	}
	case distBetPointArc: {
		DistanceBetweenPointArc* Requirement;
		try {

			Requirement = new DistanceBetweenPointArc(*dynamic_cast<Arc*>(primitives[0]), *dynamic_cast<Point*>(primitives[1]), params[0]);
		}
		catch (std::out_of_range) {
			throw std::invalid_argument("Invalid parameters");
		}
		dataReq.pushBack(Requirement);
		return;
	}
	case pointInArc: {
		PointInArc* Requirement;
		try {

			Requirement = new PointInArc(*dynamic_cast<Arc*>(primitives[0]), *dynamic_cast<Point*>(primitives[1]));
		}
		catch (std::out_of_range) {
			throw std::invalid_argument("Invalid parameters");
		}
		dataReq.pushBack(Requirement);
		return;
	}
	default:
		break;
	}
}

void Model::Optimizer() {

}

bool Model::getNearest(double x, double y, ID& obj_id) {
	if (data.getsize() != 0) {
		Vector2 pos(x, y);
		data.MoveBegin();
		ID nearestObject = data.GetCurrent()->GetId();
		double minDist = data.GetCurrent()->GetDistance(pos);
		while (data.MoveNext()) {
			double dist = data.GetCurrent()->GetDistance(pos);
			if (dist < minDist) {
				minDist = dist;
				nearestObject = data.GetCurrent()->GetId();
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
bool Model::getObjType(ID obg_id, type_id& type) {
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
		switch (obj->GetType()) {
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