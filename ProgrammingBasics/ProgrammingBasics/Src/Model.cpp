#include "Model.h"
#include <functional>
#define cast dynamic_cast


bool Model::NewComponent(const ID& id, Array<ID>& Prims, Array<ID>& Reqs)
{
	delete currentComponent;
	currentComponent = new BinSearchTree<ID, ID>;
	Queue<ID> queuePrim;
	Queue<ID> queueReq;
	ID currentID;

	auto tempPrimMarker = dataPrim.Find(id);
	if (tempPrimMarker.IsValid()) {
		// get ID Requirement
		auto tempLinkMarker = dataLink.Find(id);
		if(tempLinkMarker.IsValid()) {
			currentID = dataLink.Find(id).GetValue()->GetMarker().GetValue();
		}
		else {
			currentComponent->Add(id, id);
			Prims.PushBack(id);
			return true;
		}
	}
	else {
		auto tempReqMarker = dataReq.Find(id);
		if (tempReqMarker.IsValid()) {
			currentID = id;
		}
		else {
			return false;
		}
	}

	queueReq.push(currentID);
	while (!queueReq.isEmpty())
	{
		while (!queueReq.isEmpty())
		{
			currentID = queueReq.pop();
			currentComponent->Add(currentID, currentID);
			Reqs.PushBack(currentID);
			
			auto marker = dataLink.Find(currentID);
			if (marker.IsValid()) {
				for (auto l = marker.GetValue()->GetMarker(); l.IsValid(); ++l) {
					currentID = l.GetValue();
					if (!currentComponent->Find(currentID).IsValid()) {
						queuePrim.push(currentID);
					}
				}
			}
		}
		while (!queuePrim.isEmpty())
		{
			currentID = queuePrim.pop();
			currentComponent->Add(currentID, currentID);
			Prims.PushBack(currentID);

			auto marker = dataLink.Find(currentID);
			if (marker.IsValid()) {
				for (auto l = marker.GetValue()->GetMarker(); l.IsValid(); ++l) {
					currentID = l.GetValue();
					if (!currentComponent->Find(currentID).IsValid()) {
						queueReq.push(currentID);
					}
				}
			}
		}
	}
	return (Prims.GetSize() != 0) || (Reqs.GetSize() != 0);
}

bool Model::GetRequirements(const Array<ID>& ids, Array<Requirement*>& req) {
	for (int i = 0; i < ids.GetSize(); ++i) {
		auto marker = dataReq.Find(ids[i]);
		if (marker.IsValid()) {
			req.PushBack(marker.GetValue());
		}
	}
	return (req.GetSize() != ids.GetSize());
}

bool Model::GetPrimitives(const Array<ID>& ids, Array<Primitive*>& prim) {
	for (int i = 0; i < ids.GetSize(); ++i) {
		auto marker = dataPrim.Find(ids[i]);
		if (marker.IsValid()) {
			prim.PushBack(marker.GetValue());
		}
	}
	return (prim.GetSize() == ids.GetSize());
}


bool Model::GetRequirementsFromComponent(BinSearchTree<ID, ID>& component, Array<Requirement*>& reqs) {
	for (auto i = component.GetMarker(); i.IsValid(); ++i) {
		auto reqsMarker = dataReq.Find(i.GetValue());
		if (reqsMarker.IsValid()) {
			reqs.PushBack(reqsMarker.GetValue());
		}
	}
	return (reqs.GetSize() != 0);
}

bool Model::GetPrimitivesFromComponent(BinSearchTree<ID, ID>& component, Array<Primitive*>& prims) {
	for (auto i = component.GetMarker(); i.IsValid(); ++i) {
		auto primsMarker = dataPrim.Find(i.GetValue());
		if (primsMarker.IsValid()) {
			prims.PushBack(primsMarker.GetValue());
		}
	}
	return (prims.GetSize() != 0);
}


void Model::ConnectPrimitives(const Array<Primitive*>& prims) {
	Requirement* _connection = new ConnectionReq;
	dataReq.Add(_connection->GetID(), _connection);
	CreateLink(_connection->GetID(), prims);

}

bool Model::CreateObject(const object_type type, const Array<double>& params, ID& obj_id) {
	switch (type)
	{
	case point_t: {
		if (params.GetSize() != 2) {
			return false;
		}
		Point* _point;
		_point = new Point(params[0], params[1]);
		dataPrim.Add(_point->GetID(), _point);
		obj_id = _point->GetID();
		return true;
	}
	case segment_t: {
		if (params.GetSize() != 4) {
			return false;
		}
		Point* p1 = new Point(params[0], params[1]);
		Point* p2 = new Point(params[2], params[3]);

		Segment* _seg = new Segment(p1, p2);

		// points belong to segment
		p1->SetParent(_seg);
		p2->SetParent(_seg);

		dataPrim.Add(p1->GetID(), p1);
		dataPrim.Add(p2->GetID(), p2);
		dataPrim.Add(_seg->GetID(), _seg);

		Array<Primitive*> prims(3);
		prims[0] = p1;
		prims[1] = p2;
		prims[2] = _seg;
		ConnectPrimitives(prims);

		obj_id = _seg->GetID();
		return true;
	}
	case arc_t: {
		if (params.GetSize() != 5) {
			return false;
		}
		Point* p1 = new Point(params[0], params[1]);
		Point* p2 = new Point(params[2], params[3]);

		Arc* _arc = new Arc(p1, p2, params[4]);

		// points belong to arc
		p1->SetParent(_arc);
		p2->SetParent(_arc);

		dataPrim.Add(p1->GetID(), p1);
		dataPrim.Add(p2->GetID(), p2);
		dataPrim.Add(_arc->GetID(), _arc);

		Array<Primitive*> prims(3);
		prims[0] = p1;
		prims[1] = p2;
		prims[2] = _arc;
		ConnectPrimitives(prims);

		obj_id = _arc->GetID();
		return true;
	}
	case circle_t: {
		if (params.GetSize() != 3) {
			return false;
		}
		Point* center = new Point(params[0], params[1]);

		Circle* _circle = new Circle(center, params[2]);

		// points belong to arc
		center->SetParent(_circle);

		dataPrim.Add(center->GetID(), center);
		dataPrim.Add(_circle->GetID(), _circle);

		Array<Primitive*> prims(2);
		prims[0] = center;
		prims[1] = _circle;
		ConnectPrimitives(prims);

		obj_id = _circle->GetID();
		return true;
	}
	default:
		return false;
	}
}

bool Model::DeleteRequirement(const ID& req_id) {
	auto dataReqMarker = dataReq.Find(req_id);
	if (!dataReqMarker.IsValid()) {
		return false;
	}

	auto dataLinkMarker = dataLink.Find(req_id);
	if (!dataLinkMarker.IsValid()) {
		throw std::exception("Invalid link requirement->primitive");
	}

	auto listPrim = dataLinkMarker.GetValue();
	dataLinkMarker.DeleteCurrent();

	for (auto i = listPrim->GetMarker(); i.IsValid(); ++i) {
		dataLinkMarker = dataLink.Find(i.GetValue());
		if (!dataLinkMarker.IsValid()) {
			throw std::exception("Invalid link primitive->requirement");
		}
		auto listReq = dataLinkMarker.GetValue();
		listReq->Find(req_id).DeleteCurrent();
	}

	Requirement* req = dataReqMarker.GetValue();
	dataReqMarker.DeleteCurrent();
	delete req;
	delete listPrim;


	return true;
}

bool Model::DeletePrimitive(const ID& prim_id) {
	auto dataPrimMarker = dataPrim.Find(prim_id);
	if (!dataPrimMarker.IsValid()) {
		return false;
	}

	Primitive* prim = dataPrimMarker.GetValue();
	auto dataLinkMarker = dataLink.Find(prim_id);
	if (!dataLinkMarker.IsValid()) {
		delete prim;
		dataPrimMarker.DeleteCurrent();
		return true;
	}

	auto list = dataLinkMarker.GetValue();

	while (list->GetSize() != 0) {
		DeleteRequirement(list->GetMarker().GetValue());
	}

	delete list;

	dataPrimMarker.DeleteCurrent();
	dataLinkMarker.DeleteCurrent();

	if (prim->GetType() == point_t) {
		Point* point = cast<Point*>(prim);
		if (point->GetParent() != nullptr) {
			bool result = DeletePrimitive(point->GetParent()->GetID());
			delete prim;
			return result;
		}
	}
	delete prim;
	return DeletePrimitive(true);
}


bool Model::CreateRequirementByID(const object_type type, Array<ID>& id_arr, const Array<double>& params, ID& req_id) {
	Array<Primitive*> primitives;
	for (int i = 0; i < id_arr.GetSize(); ++i) {
		auto marker = dataPrim.Find(id_arr[i]);
		if (!marker.IsValid()) {
			return false;
		}
		primitives.PushBack(marker.GetValue());
	}
	return CreateRequirement(type, primitives, params, req_id);
}

bool Model::CreateRequirement(object_type type, Array<Primitive*>& primitives, const Array<double>& params, ID& req_id) {
	Requirement* requirement;
	switch (type)
	{
	case distBetPoints_t: {
		// verification parameters
		if ((primitives.GetSize() != 2)
			|| (params.GetSize() != 1)
			|| (primitives[0]->GetType() != point_t)
			|| (primitives[1]->GetType() != point_t)) {
			return false;
		}
		// creating
		requirement = new DistBetPointsReq(cast<Point*>(primitives[0]),
			cast<Point*>(primitives[1]),
			params[0]);
		break;
	}
	case equalSegmentLen_t: {
		// verification parameters
		if ((primitives.GetSize() != 2)
			|| (params.GetSize() != 0)
			|| (primitives[0]->GetType() != segment_t)
			|| (primitives[1]->GetType() != segment_t)) {
			return false;
		}
		// creating
		requirement = new EqualSegmentLenReq(cast<Segment*>(primitives[0]),
			cast<Segment*>(primitives[1]));
		break;
	}
	case pointsOnTheOneHand: {
		// verification parameters
		if ((primitives.GetSize() != 3)
			|| (params.GetSize() != 0)
			|| (primitives[0]->GetType() != segment_t)
			|| (primitives[1]->GetType() != point_t)
			|| (primitives[2]->GetType() != point_t))
		{
			return false;
		}
		// creating
		requirement = new PointsOnTheOneHand(cast<Segment*>(primitives[0]),
			cast<Point*>(primitives[1]),
			cast<Point*>(primitives[2]));
		break;
	}
	case distBetPointSeg: {
		// verification parameters
		if ((primitives.GetSize() != 2)
			|| (params.GetSize() != 1)
			|| (primitives[0]->GetType() != segment_t)
			|| (primitives[1]->GetType() != point_t))
		{
			return false;
		}
		// creating
		requirement = new DistanceBetweenPointSegment(cast<Segment*>(primitives[0]),
			cast<Point*>(primitives[1]),
			params[0]);
		break;
	}
	case pointPosReq_t: {
		if (primitives.GetSize() != 1
			|| params.GetSize() != 2
			|| primitives[0]->GetType() != point_t) {
		}
		requirement = new PointPosReq(cast<Point*>(primitives[0]), params[0], params[1]);
		break;
	}
	case angleBetSeg: {
		// verification parameters
		if ((primitives.GetSize() != 2)
			|| (params.GetSize() != 1)
			|| (primitives[0]->GetType() != segment_t)
			|| (primitives[1]->GetType() != segment_t))
		{
			return false;
		}
		// creating
		requirement = new AngleBetweenSegments(cast<Segment*>(primitives[0]),
			cast<Segment*>(primitives[1]),
			params[0]);
		break;
	}
	case distBetPointArc: {
		// verification parameters
		if ((primitives.GetSize() != 2)
			&& (params.GetSize() != 1)
			&& (primitives[0]->GetType() != arc_t)
			&& (primitives[1]->GetType() != point_t))
		{
			return false;
		}
		// creating
		requirement = new DistanceBetweenPointArc(cast<Arc*>(primitives[0]),
			cast<Point*>(primitives[1]),
			params[0]);
		break;
	}
	case pointInArc: {
		// verification parameters
		if ((primitives.GetSize() != 2)
			&& (params.GetSize() != 0)
			&& (primitives[0]->GetType() != arc_t)
			&& (primitives[1]->GetType() != point_t))
		{
			return false;
		}
		// creating
		requirement = new PointInArc(cast<Arc*>(primitives[0]),
			cast<Point*>(primitives[1]));
		break;
		}
					 //case correctTriangle: {
					 //	CorrectTriangle* Requirement;
					 //	if ((primitives[0]->GetType() == segment)
					 //		&& (primitives[1]->GetType() == segment)
					 //		&& (primitives[2]->GetType() == segment)
					 //		&& (params.GetSize() > 0)) {
					 //		Requirement = new ÑorrectTriangle(dynamic_cast<Segment*>(primitives[0]),
					 //			dynamic_cast<Segment*>(primitives[1]),
					 //			dynamic_cast<Segment*>(primitives[2]),
					 //			params[0]);
					 //		dataPrimReq.PushBack(Requirement);
					 //		return true;
					 //	}
					 //	else {
					 //		return false;
					 //	}
					 //}
					 //case nsAngle: {
					 //	NsAngle* Requirement;
					 //	ListE<Segment*> list;
					 //	for (int i = 0; i < primitives.GetSize(); ++i) {
					 //		if (segment == primitives[i]->GetType()) {
					 //			list.PushTail(dynamic_cast<Segment*>(primitives[i]));
					 //		}
					 //		else {
					 //			return false;
					 //		}
					 //	}
					 //	Requirement = new NsAngle(list);
					 //	dataPrimReq.PushBack(Requirement);
					 //	return true;
					 //}
					 //case correctNsAngle: {
					 //	CorrectNsAngle* Requirement;
					 //	if (params.GetSize() > 0) {
					 //		ListE<Segment*> list;
					 //		for (int i = 0; i < primitives.GetSize(); ++i) {
					 //			if (segment == primitives[i]->GetType()) {
					 //				list.PushTail(dynamic_cast<Segment*>(primitives[i]));
					 //			}
					 //			else {
					 //				return false;
					 //			}
					 //		}
					 //		Requirement = new CorrectNsAngle(list, params[0]);
					 //		dataPrimReq.PushBack(Requirement);
					 //		return true;
					 //	}
					 //	else {
					 //		return false;
					 //	}
					 //}
					 //}
	default:
		return false;
	}

	req_id = requirement->GetID();

	dataReq.Add(req_id, requirement);

	CreateLink(req_id, primitives);

	return true;
}

void Model::CreateLink(const ID& IDreq, const Array<Primitive*>& primitives) {
	// create link Prim on Req
	for (int i = 0; i < primitives.GetSize(); ++i) {
		auto markerLink = dataLink.Find(primitives[i]->GetID());
		if (markerLink.IsValid()) {
			markerLink.GetValue()->PushTail(IDreq);
		}
		else {
			auto newList = new List<ID>;
			newList->PushTail(IDreq);
			dataLink.Add(primitives[i]->GetID(), newList);
		}
	}
	// create link Req on Prim
	List<ID>* list = new List<ID>;
	for (int i = 0; i < primitives.GetSize(); ++i) {
		list->PushTail(primitives[i]->GetID());
	}
	dataLink.Add(IDreq, list);
}



bool Model::DischargeInfoObjects(Array<infoObject>& dataPrimInfoObjects)
{
	if (dataPrim.GetSize() == 0) {
		return false;
	}
	auto dataPrimMarker = dataPrim.GetMarker();
	do
	{
		infoObject temp;
		GetObjParam(dataPrimMarker.GetValue()->GetID(), temp.params);
		GetObjType(dataPrimMarker.GetValue()->GetID(), temp.type);
		dataPrimInfoObjects.PushBack(temp);
	} while (++dataPrimMarker);
	return true;
}

// optimize

double Model::GetError(const Array<Requirement*>& requirments) const {
	double error = 0.0;
	for (int i = 0; i < requirments.GetSize(); ++i) {
		error += requirments[i]->error();
	}
	return error / requirments.GetSize();
}

double Model::ErrorByAlpha(const Array<Requirement*>& req, const Array<double*>& params, const Array<double>& aGrad, double alpha) {
	for (int i = 0; i < params.GetSize(); ++i) {
		double delta = aGrad[i];
		*(params[i]) += delta * alpha;
	}
	double error = GetError(req);
	for (int i = 0; i < params.GetSize(); ++i) {
		*(params[i]) -= aGrad[i] * alpha;
	}
	return error;
}

void Model::OptimizeByGradient(const Array<Requirement*>& requirments, const Array<double*>& params, const Array<double>& aGradient) {

	const double gold_section = 1.6180339887498;
	int reqSize = requirments.GetSize();

	double error = GetError(requirments);

	double left = 0.0;
	double right = 0.1;

	double leftValue = ErrorByAlpha(requirments, params, aGradient, left);
	double rightValue = ErrorByAlpha(requirments, params, aGradient, right);

	double x1 = right - (right - left) / gold_section;
	double x2 = left + (right - left) / gold_section;

	double x1_Value = ErrorByAlpha(requirments, params, aGradient, x1);
	double x2_Value = ErrorByAlpha(requirments, params, aGradient, x2);

	while (abs(leftValue - rightValue) > OPTIM_GRAD_EPS * error) {

		if (x1_Value > x2_Value) {
			left = x1;
			leftValue = x1_Value;
			x1 = x2;
			x1_Value = x2_Value;
			x2 = left + (right - left) / gold_section;
			x2_Value = ErrorByAlpha(requirments, params, aGradient, x2);
		}
		else {
			right = x2;
			rightValue = x2_Value;
			x2 = x1;
			x1 = right - (right - left) / gold_section;
			x2_Value = x1_Value;
			x1_Value = ErrorByAlpha(requirments, params, aGradient, x1);
		}
	}

	double alpha = (leftValue < rightValue) ? left : right;

	for (int i = 0; i < params.GetSize(); ++i) {
		(*params[i]) += aGradient[i] * alpha;
	}
}

bool Model::OptimizeRequirements(const Array<Requirement*>& requirments) {
	// get parameters number
	int params_number = 0;
	for (int i = 0; i < requirments.GetSize(); ++i) {
		Array<double*> params = requirments[i]->GetParams();
		params_number += params.GetSize();
	}

	class UniqueParam {
	private:
	public:
		double* param;
		int unique_number;
	};

	//ctreating match_array, which will establish a correspondence
	//between not-unique parameters and their unique numbers

	Array<double*> all_parameters(params_number);
	BinSearchTree<double*, UniqueParam> set;
	int* match_array = new int[params_number];

	// from 0 to params_number
	int all_parameters_iterator = 0;

	// from 0 to number of unique double*
	int uniq_numbers_iterator = 0;

	// filling match_array
	for (int i = 0; i < requirments.GetSize(); ++i) {

		Array<double*> currentRequirmentParams = requirments[i]->GetParams();

		for (int j = 0; j < currentRequirmentParams.GetSize(); ++j) {

			double* currentParameter = currentRequirmentParams[j];
			all_parameters[all_parameters_iterator] = currentParameter;

			UniqueParam unique_param;
			auto setMarker = set.Find(currentParameter);
			bool notUniqueParam = setMarker.IsValid();

			if (notUniqueParam) {
				match_array[all_parameters_iterator] = setMarker.GetValue().unique_number;
			}
			else {
				unique_param = UniqueParam{ currentParameter, uniq_numbers_iterator };
				set.Add(currentParameter, unique_param);
				match_array[all_parameters_iterator] = uniq_numbers_iterator;
				uniq_numbers_iterator++;
			}
			all_parameters_iterator++;
		}
	}

	// array of unique_parameters
	Array<double*> unique_parameters(uniq_numbers_iterator, nullptr);

	for (int i = 0; i < params_number; ++i) {
		unique_parameters[match_array[i]] = all_parameters[i];
	}

	// anti gradient
	Array<double> aGradient(uniq_numbers_iterator, 0.0);

	//filling anti gradient
	double err = GetError(requirments);
	int optimization_iter = 0;
	while (err > OPTIM_EPS) {
		int match_array_iterator = 0;
		for (int i = 0; i < requirments.GetSize(); ++i) {
			Array<double> currentGradient = requirments[i]->Gradient();
			for (int j = 0; j < currentGradient.GetSize(); ++j) {
				aGradient[match_array[match_array_iterator]] -= currentGradient[j] / requirments.GetSize();
				++match_array_iterator;
			}
		}

		OptimizeByGradient(requirments, unique_parameters, aGradient);
		aGradient.FillDefault(0.0);
		err = GetError(requirments);
		
		optimization_iter++;
		// temp
		if (optimization_iter >= 1000) {
			return (err < OPTIM_EPS * 10);
		}
	}


	return true;
}

bool Model::OptimizeByID(const ID& id) {
	BinSearchTree<ID, ID> component;
	Array<ID> reqID;
	Array<ID> primID;
	if(!NewComponent(id, primID, reqID)) {
		return true;
	}
	Array<Requirement*> reqs;
	GetRequirements(reqID, reqs);

	/*if (!GetRequirementsFromComponent(component, reqs)) {
		return;
	}*/
	return OptimizeRequirements(reqs);
}

void Model::OptitmizeNewton(const ID& id) {

	Array<ID> primID;
	Array<ID> reqID;
	Array<Primitive*> prim;
	Array<Requirement*> req;
	Array<double*> params;

	NewComponent(id, primID, reqID);
	GetRequirements(reqID, req);
	GetPrimitives(primID, prim);
	GetDoublesForOptimize(prim, params);


}

void Model::GetDoublesForOptimize(Array<Primitive*>& prims, Array<double*>& params) {
	for (int i = 0; i < prims.GetSize(); ++i) {
		if (prims[i]->GetType() == point_t) {
			Point* point = cast<Point*>(prims[i]);
			params.PushBack(&point->position.x);
			params.PushBack(&point->position.y);
		}
		if (prims[i]->GetType() == arc_t) {
			Arc* arc = cast<Arc*>(prims[i]);
			params.PushBack(&arc->angle);
		}
	}
}

void Model::GetDifferential(const Array<Requirement*>& reqs, Array<double*>& params, Array<double>& diff) {
	double begin = GetError(reqs);
	for (int i = 0; i < params.GetSize(); ++i) {
		*params[i] += DELTA_X;
		diff[i] = (begin - GetError(reqs)) / DELTA_X;
		*params[i] -= DELTA_X;
	}
}

//

bool Model::GetObjType(const ID& obj_id, object_type& type) {
	Primitive* obj = nullptr;
	auto dataPrimMarker = dataPrim.Find(obj_id);

	if (dataPrimMarker.IsValid()) {
		obj = dataPrimMarker.GetValue();
		type = obj->GetType();
		return true;
	}
	else {
		return false;
	}
}

bool Model::GetObjParam(const ID& obj_id, Array<double>& result) {
	Primitive* obj = nullptr;
	auto dataPrimMarker = dataPrim.Find(obj_id);
	if (dataPrimMarker.IsValid()) {
		obj = dataPrimMarker.GetValue();
		switch (obj->GetType()) {
		case point_t: {
			Point* point = cast<Point*>(obj);
			result.Clear();
			Vector2 pos = point->GetPosition();
			result.PushBack(pos.x);
			result.PushBack(pos.y);
			return true;
			break;
		}
		case segment_t: {
			Segment* segment = cast<Segment*>(obj);
			result.Clear();
			Vector2 pos1 = segment->GetPoint1_pos();
			Vector2 pos2 = segment->GetPoint2_pos();
			result.PushBack(pos1.x);
			result.PushBack(pos1.y);
			result.PushBack(pos2.x);
			result.PushBack(pos2.y);
			return true;
			break;
		}
		case arc_t: {
			Arc* arc = cast<Arc*>(obj);
			result.Clear();
			Vector2 pos1 = arc->GetPoint1_pos();
			Vector2 pos2 = arc->GetPoint2_pos();
			double angle = arc->GetAngle();
			result.PushBack(arc->GetCenter().x);
			result.PushBack(arc->GetCenter().y);
			result.PushBack(pos1.x);
			result.PushBack(pos1.y);
			result.PushBack(pos2.x);
			result.PushBack(pos2.y);
			return true;
			break;
		}
		case circle_t: {
			Circle* circle = dynamic_cast<Circle*>(obj);
			result.Clear();
			Vector2 center = circle->GetCenter();
			double radius = circle->GetRadius();
			result.PushBack(center.x);
			result.PushBack(center.y);
			result.PushBack(radius);
			return true;
			break;
		}
		default: {
			return false;
		}
		}
	}
	return false;

}

#define SEARCH_AREA 3.0

bool Model::GetObject(double x, double y, Array<ID>& obj_id, Array<double>& distances) {
	bool isFound = false;
	for (auto i = dataPrim.GetMarker(); i.IsValid(); ++i) {
		double dist = i.GetValue()->GetDistance(Vector2(x, y));
		if (dist < SEARCH_AREA) {
			isFound = true;
			distances.PushBack(dist);
			obj_id.PushBack(i.GetValue()->GetID());
		}
	}
	return isFound;
}


void Model::ChangeRequirement(const ID& id, const double param) {
	auto marker = dataReq.Find(id);
	if (marker.IsValid()) {
		marker.GetValue()->Change(param);
		OptimizeByID(id);
	}
}

bool Model::OptimizeGroup(Array<Primitive*>& group) {

	do {
		if (!OptimizeByID(group[0]->GetID())) {
			return false;
		}
		for (int i = 0; i < group.GetSize(); ++i) {
			if (currentComponent->Find(group[i]->GetID()).IsValid()) {
				group.EraseO_1_(i);
				--i;
			}
		}
	} while (group.GetSize() > 0);
	return true;
}

void Model::LockPoint(Point* _point, ID& id) {

	Array<Primitive*> point(1);
	point[0] = _point;
	Array<double> params(2);
	params[0] = _point->position.x;
	params[1] = _point->position.y;

	CreateRequirement(pointPosReq_t, point, params, id);
}

bool Model::Scale(const Array<ID>& idPrim, const double koef) {
	Array<Primitive*> primitives;
	if (!GetPrimitives(idPrim, primitives)) {
		// in presenter invalid ID
		// LOG
		return false;
	}

	BinSearchTree<ID, Point*> points;
	GetPointsFromPrimitives(primitives, points);
	// geting center
	Vector2 center;
	for (auto i = points.GetMarker(); i.IsValid(); ++i) {
		center += i.GetValue()->position;
	}
	center /= points.GetSize();
	Array<ID> reqs;
	// Moving
	for (auto i = points.GetMarker(); i.IsValid(); ++i) {

		Vector2 newPos((i.GetValue()->position - center) * koef);
		i.GetValue()->position = center + newPos;

		ID id;

		LockPoint(i.GetValue(), id);

		reqs.PushBack(id);
	}

	if (!OptimizeGroup(primitives)) {

		for (int i = 0; i < reqs.GetSize(); ++i) {
			DeleteRequirement(reqs[i]);
		}

		return false;
	}

	for (int i = 0; i < reqs.GetSize(); ++i) {
		DeleteRequirement(reqs[i]);
	}
	return true;
}

bool Model::Move(const Array<ID>& idPrim, const Vector2& shift) {
	Array<Primitive*> primitives;
	if (!GetPrimitives(idPrim, primitives)) {
		// LOG
		return false;
	}
	BinSearchTree<ID, Point*> points;
	GetPointsFromPrimitives(primitives, points);

	Array<ID> reqs;

	for (auto i = points.GetMarker(); i.IsValid(); ++i) {
		i.GetValue()->position += shift;

		ID id;

		LockPoint(i.GetValue(), id);

		reqs.PushBack(id);
	}

	if (!OptimizeGroup(primitives)) {

		for (int i = 0; i < reqs.GetSize(); ++i) {
			DeleteRequirement(reqs[i]);
		}

		return false;
	}

	for (int i = 0; i < reqs.GetSize(); ++i) {
		DeleteRequirement(reqs[i]);
	}
	return true;
}



void Model::GetPointsFromPrimitives(Array<Primitive*>& primitives, BinSearchTree<ID, Point*>& pointTree ) {
	for (int i = 0; i < primitives.GetSize(); ++i) {
		switch (primitives[i]->GetType())
		{
		case point_t: {
			if (!pointTree.Find(primitives[i]->GetID()).IsValid()) {
				Point* point = cast<Point*>(primitives[i]);
				pointTree.Add(point->GetID(), point);
			}
			break;
		}
		case segment_t: {
			Segment* segment = cast<Segment*>(primitives[i]);
			if (!pointTree.Find(segment->GetPoint1_ID()).IsValid()) {
				Point* point = segment->point1;
				pointTree.Add(point->GetID(), point);
			}
			if (!pointTree.Find(segment->GetPoint2_ID()).IsValid()) {
				Point* point = segment->point2;
				pointTree.Add(point->GetID(), point);
			}
			break;
		}
		case arc_t: {
			Arc* arc = cast<Arc*>(primitives[i]);
			if (!pointTree.Find(arc->GetPoint1_ID()).IsValid()) {
				Point* point = arc->point1;
				pointTree.Add(point->GetID(), point);
			}
			if (!pointTree.Find(arc->GetPoint2_ID()).IsValid()) {
				Point* point = arc->point2;
				pointTree.Add(point->GetID(), point);
			}
			break;
		}
		default:
			break;
		}
	}
}