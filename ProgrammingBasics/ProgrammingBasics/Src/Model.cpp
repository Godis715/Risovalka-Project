#include "Model.h"
#include <stdexcept>


bool Model::createObject(type_id type, Array<double>& params, ID& obj_id) {
	switch (type)
	{
	case point: {
		if (params.getSize() != 2) {
			return false;
		}
		Point* _point;
		_point = new Point(params[0], params[1]);
		data.Add(_point->GetId(),_point);
		obj_id = _point->GetId();
		return true;
	}
	case segment: {
		if (params.getSize() != 4) {
			return false;
		}
		Point* p1 = new Point(params[0], params[1]);
		Point* p2 = new Point(params[2], params[3]);

		Segment* _seg = new Segment(p1, p2);

		data.Add(p1->GetId(), p1);
		data.Add(p2->GetId(), p2);
		data.Add(_seg->GetId(), _seg);

		obj_id = _seg->GetId();
		return true;
	}
	case arc: {
		if (params.getSize() != 5) {
			return false;
		}
		Point* p1 = new Point(params[0], params[1]);
		Point* p2 = new Point(params[2], params[3]);

		Arc* _arc = new Arc(p1, p2, params[4]);

		data.Add(p1->GetId(), p1);
		data.Add(p2->GetId(), p2);
		data.Add(_arc->GetId(), _arc);

		obj_id = _arc->GetId();
		return true;
	}
	default:
		return false;
	}
}

bool Model::createRequirement(const Requirement_id _id, Array<ID>& id_arr, Array<double>& params) {
	Array<Primitive*> primitives;
	for (int i = 0; i < id_arr.getSize(); ++i) {
		if (data.find(id_arr[i])) {
			primitives.pushBack(data.GetCurrent());
		}
		else {
			return false;
		}
	}
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
		return true;
	}
	case pointsOnTheOneHand: {
		PointsOnTheOneHand* Requirement;
		try {
			Requirement = new PointsOnTheOneHand(*dynamic_cast<Segment*>(primitives[0]),
				*dynamic_cast<Point*>(primitives[1]), *dynamic_cast<Point*>(primitives[2]));
		}
		catch (std::out_of_range) {
			throw std::invalid_argument("Invalid parameters");
		}
		dataReq.pushBack(Requirement);
		return true;
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
		return true;
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
		return true;
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
		return true;
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
		return true;
	}
	default:
		return false;
	}
}

void Model::Optimize() {

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

bool Model::getObjType(const ID& obj_id, type_id& type) {
	Primitive* obj = nullptr;
	bool isFound = data.find(obj_id);
	obj = data.GetCurrent();
	if (isFound) {
		type = obj->GetType();
		return true;
	}
	else {
		return false;
	}
}

bool Model::getObjParam(const ID& obj_id, Array<double>& result) {
	Primitive* obj = nullptr;
	bool isFound = data.find(obj_id);
	if (isFound) {
		obj = data.GetCurrent();
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