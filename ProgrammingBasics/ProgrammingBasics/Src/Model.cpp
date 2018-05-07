
#include "Model.h"
#define cast dynamic_cast

#ifdef MODEL_VERSION_LINK
void Model::GetIDRequirementsInComponent(const ID& idPrim, Array<ID>& IDReq)
{
	BinSearchTree<ID, ID> labels;
	Queue<ID> queuePrim;
	Queue<ID> queueReq;
	auto marker = dataLink.GetMarker();
	List<ID>* list;
	List<ID>::Marker listMarker;
	ID id;
	DataLink::Marker treeMarker;

	queuePrim.push(idPrim);
	while (!queuePrim.isEmpty())
	{
		while (!queuePrim.isEmpty())
		{
			id = queuePrim.pop();
			labels.Add(id, id);

			treeMarker = dataLink.Find(id);
			if (!treeMarker.IsValid()) {
				continue;
			}
			list = treeMarker.GetValue();
			listMarker = list->GetMarker();
			if (!listMarker.IsValid()) {
				continue;
			}
			id = listMarker.GetValue();
			auto tempLabelsMarker = labels.Find(id);
			if (!tempLabelsMarker.IsValid()) {
				continue;
			}
			queueReq.push(id);
		}
		while (!queueReq.isEmpty())
		{
			id = queueReq.pop();
			labels.Add(id, id);
			IDReq.PushBack(id);

			treeMarker = dataLink.Find(id);
			if (!treeMarker.IsValid()) {
				continue;
			}
			list = treeMarker.GetValue();
			listMarker = list->GetMarker();
			if (!listMarker.IsValid()) {
				continue;
			}
			id = listMarker.GetValue();
			if (labels.Find(id).IsValid()) {
				continue;
			}
			queuePrim.push(id);
		}
	}
}

void Model::FindRequirementsByID(Array<ID>& IDReq, Array<Requirement*>& Requirements) {
	for (int i = 0; i < IDReq.GetSize(); ++i) {
		auto marker = dataReq.Find(IDReq[i]);
		if (!marker.IsValid()) {
			continue;
		}
		Requirements.PushBack(marker.GetValue());
	}
}

bool Model::find(const ID& id, Array<ID> foundID)
{
	bool isFound = false;
	auto marker = dataLink.Find(id);
	if (!marker.IsValid()) {
		return isFound;
	}
	List<ID>* list = marker.GetValue();
	auto listMarker = list->GetMarker();
	if (!listMarker.IsValid()) {
		return isFound;
	}
	do
	{
		foundID.PushBack(listMarker.GetValue());
	} while (++listMarker);
	isFound = true;
	return isFound;
}

bool Model::find(const ID& idReq, Array<Primitive*>& foundPrim)
{
	bool isFound = false;
	auto marker = dataLink.Find(idReq);
	if (!marker.IsValid()) {
		return isFound;
	}
	List<ID>* list = marker.GetValue();
	auto listMarker = list->GetMarker();
	if (!listMarker.IsValid()) {
		return isFound;
	}
	do
	{
		BinSearchTree<ID, Primitive*>::Marker markerPrim = dataPrim.Find(listMarker.GetValue());
		foundPrim.PushBack(markerPrim.GetValue());
		if (!markerPrim.IsValid()) {
			continue;
		}
	} while (++listMarker);
	isFound = true;
	return isFound;
}

bool Model::find(const ID& idPrim, Array<Requirement*>& foundReq)
{
	bool isFound = false;
	auto marker = dataLink.Find(idPrim);
	if (!marker.IsValid()) {
		return isFound;
	}
	List<ID>* list = marker.GetValue();
	auto listMarker = list->GetMarker();
	if (!listMarker.IsValid()) {
		return isFound;
	}
	do
	{
		BinSearchTree<ID, Requirement*>::Marker markerPrim = dataReq.Find(listMarker.GetValue());
		if (!markerPrim.IsValid()) {
			continue;
		}
		foundReq.PushBack(markerPrim.GetValue());
	} while (++listMarker);
	isFound = true;
	return isFound;
}

void Model::ConnectPrimitives(Primitive* point, Primitive* prim) {
	Requirement* _connection = new ConnectionReq;
	Array<Primitive*> prims(2);
	prims.PushBack(point);
	prims.PushBack(prim);
	CreateLink(_connection->GetID(), prims);
}

bool Model::CreateObject(const prim_type type, Array<double>& params, ID& obj_id) {
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

		ConnectPrimitives(p1, _seg);
		ConnectPrimitives(p2, _seg);

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

		ConnectPrimitives(p1, _arc);
		ConnectPrimitives(p2, _arc);

		obj_id = _arc->GetID();
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

	auto listPrim = dataLink.GetMarker().GetValue();
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

//bool Model::createSegment(ID& p1ID, ID& p2ID, ID& segID) {
//	Primitive* point1PR;
//	Primitive* point2PR;
//	bool error = false;
//	if (dataPrim.Find(p1ID)) {
//		point1PR = dataPrim.GetCurrent();
//		if (dataPrim.Find(p2ID)) {
//			point2PR = dataPrim.GetCurrent();
//			if ((point1PR->GetType() == point) && (point2PR->GetType() == point)) {
//				Point* point1 = dynamic_cast<Point*>(point1PR);
//				Point* point2 = dynamic_cast<Point*>(point2PR);
//				Segment* segment = new Segment(point1, point2);
//				segID = segment->GetID();
//				dataPrim.Add(segID, segment);
//				return true;
//			}
//		}
//	}
//	return false;
//}

bool Model::CreateRequirementByID(const req_type type, Array<ID>& id_arr, Array<double>& params) {
	Array<Primitive*> primitives;
	for (int i = 0; i < id_arr.GetSize(); ++i) {
		auto marker = dataPrim.Find(id_arr[i]);
		if (!marker.IsValid()) {
			return false;
		}
		primitives.PushBack(marker.GetValue());
	}
	return CreateRequirement(type, primitives, params);
}

bool Model::CreateRequirement(req_type type, Array<Primitive*>& primitives, Array<double>& params) {
	switch (type)
	{
	case distBetPoints: {
		// verification parameters
		if ((primitives.GetSize() != 2)
			&& (params.GetSize() != 1)
			&& (primitives[0]->GetType() != point_t)
			&& (primitives[1]->GetType() != point_t)) {
			return false;
		}
		// creating
		DistBetPointsReq* requirement;
		requirement = new DistBetPointsReq(cast<Point*>(primitives[0]),
			cast<Point*>(primitives[1]),
			params[0]);
		dataReq.Add(requirement->GetID(), requirement);

		CreateLink(requirement->GetID(), primitives);
		return true;
	}
	case equalSegmentLen: {
		// verification parameters
		if ((primitives.GetSize() != 2)
			&& (params.GetSize() != 0)
			&& (primitives[0]->GetType() != segment_t)
			&& (primitives[1]->GetType() != segment_t)) {
			return false;
		}
		// creating
		EqualSegmentLenReq* requirement = new EqualSegmentLenReq(*cast<Segment*>(primitives[0]),
			*cast<Segment*>(primitives[1]));
		dataReq.Add(requirement->GetID(), requirement);


		CreateLink(requirement->GetID(), primitives);
		return true;
	}
	case pointsOnTheOneHand: {
		// verification parameters
		if ((primitives.GetSize() != 3)
			&& (params.GetSize() == 0)
			&& (primitives[0]->GetType() == segment_t)
			&& (primitives[1]->GetType() == point_t)
			&& (primitives[2]->GetType() == point_t))
		{
			return false;
		}
		// creating
		PointsOnTheOneHand* requirement = new PointsOnTheOneHand(*cast<Segment*>(primitives[0]),
			*cast<Point*>(primitives[1]),
			*cast<Point*>(primitives[2]));
		dataReq.Add(requirement->GetID(), requirement);

		CreateLink(requirement->GetID(), primitives);
		return true;
	}
	case distBetPointSeg: {
		// verification parameters
		if ((primitives.GetSize() != 2)
			&& (params.GetSize() != 1)
			&& (primitives[0]->GetType() != segment_t)
			&& (primitives[1]->GetType() != point_t))
		{
			return false;
		}
		// creating
		DistanceBetweenPointSegment* requirement = new DistanceBetweenPointSegment(*cast<Segment*>(primitives[0]),
			*cast<Point*>(primitives[1]),
			params[0]);
		dataReq.Add(requirement->GetID(), requirement);

		CreateLink(requirement->GetID(), primitives);
		return true;
	}
	case angleBetSeg: {
		// verification parameters
		if ((primitives.GetSize() != 2)
			&& (params.GetSize() == 1)
			&& (primitives[0]->GetType() == segment_t)
			&& (primitives[1]->GetType() == segment_t))
		{
			return false;
		}
		// creating
		AngleBetweenSegments* requirement = new AngleBetweenSegments(*cast<Segment*>(primitives[0]),
			*cast<Segment*>(primitives[1]),
			params[0]);
		dataReq.Add(requirement->GetID(), requirement);

		CreateLink(requirement->GetID(), primitives);
		return true;

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
		DistanceBetweenPointArc* requirement = new DistanceBetweenPointArc(*cast<Arc*>(primitives[0]),
			*cast<Point*>(primitives[1]),
			params[0]);
		dataReq.Add(requirement->GetID(), requirement);

		CreateLink(requirement->GetID(), primitives);
		return true;
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
		PointInArc* requirement = new PointInArc(*cast<Arc*>(primitives[0]),
			*cast<Point*>(primitives[1]));
		dataReq.Add(requirement->GetID(), requirement);

		CreateLink(requirement->GetID(), primitives);
		return true;
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
}

void Model::CreateLink(const ID& IDreq, Array<Primitive*>& primitives) {
	// create link Prim on Req
	for (int i = 0; i < primitives.GetSize(); ++i) {
		auto markerLink = dataLink.Find(primitives[i]->GetID());
		markerLink.GetValue()->PushTail(IDreq);
	}
	// create link Req on Prim
	List<ID>* list = new List<ID>;
	for (int i = 0; i < primitives.GetSize(); ++i) {
		list->PushTail(primitives[i]->GetID());
	}
	dataLink.Add(IDreq, list);
}

#endif

bool Model::DischargeInfoObjects(Array<infoObject>& dataPrimInfoObjects)
{
	if (dataPrim.GetSize() == 0) {
		return false;
	}
	auto dataPrimMarker = dataPrim.GetMarker();
	do
	{
		infoObject temp;
		getObjParam(dataPrimMarker.GetValue()->GetID(), temp.params);
		getObjType(dataPrimMarker.GetValue()->GetID(), temp.type);
		dataPrimInfoObjects.PushBack(temp);
	} while (++dataPrimMarker);
	return true;
}

// optimize function

double Model::GetError(){
	double sum_error = 0;
	auto dataReqMarker = dataReq.GetMarker();
	do
	{
		sum_error += dataReqMarker.GetValue()->error();
	} while (++dataReqMarker);
	return sum_error / dataReq.GetSize();
}

//int Model::Optimize1() {
//
//	if (dataPrim.GetSize() == 0) {
//		return 0;
//	}
//
//	Array<Point*> points;
//	Array<Arc*> arcs;
//
//	dataPrim.MoveBegin();
//	do {
//		Primitive* obj = dataPrim.GetCurrent();
//		if (obj->GetType() == point) {
//			points.PushBack(dynamic_cast<Point*>(obj));
//		}
//		else if (obj->GetType() == arc) {
//			arcs.PushBack(dynamic_cast<Arc*>(obj));
//		}
//	} while (dataPrim.MoveNext());
//
//	const double delta_increasing_k = 2.0;
//	double sum_error = 0;
//	sum_error = GetError();
//	double prevError = sum_error;
//	double prevLastError = sum_error;
//	int count = 0;
//	int iterInside = 3;
//	double delta = sum_error;
//	std::cout << sum_error << "   " << iterInside << "   " << EPS << "  " << delta << "\n";
//
//	while (sum_error > EPS) {
//		++count;
//		for (int i = 0; i < points.GetSize(); ++i) {
//
//			delta = sum_error;
//
//			Vector2 pos = points[i]->GetPosition();
//			for (int k = 0; k < iterInside; ++k)
//			{
//				double shift_x[]{ delta, -delta, delta, -delta, delta, -delta, 0, 0 };
//				double shift_y[]{ delta, delta, -delta, -delta, 0, 0, delta, -delta };
//
//				double minFuncValue = sum_error;
//				Vector2 minFuncPos = pos;
//				bool hasChanged = false;
//
//				for (int j = 0; j < 8; ++j) {
//
//					points[i]->SetPosition(pos.x + shift_x[j], pos.y + shift_y[j]);
//
//					double funcValue = GetError();
//
//					if (funcValue < minFuncValue) {
//
//						minFuncValue = funcValue;
//
//						minFuncPos = pos;
//						minFuncPos.x += shift_x[j];
//						minFuncPos.y += shift_y[j];
//
//						hasChanged = true;
//					}
//				}
//
//				if (!hasChanged) {
//					delta /= delta_increasing_k;
//				}
//				else {
//					sum_error = minFuncValue;
//					points[i]->SetPosition(minFuncPos);
//					break;
//				}
//				if (delta < 1e-6) {
//					break;
//				}
//			}
//		}
//		for (int i = 0; i < arcs.GetSize(); ++i) {
//			double delta = sum_error;
//			while (delta > EPS) {
//				double tempAngle = arcs[i]->GetAngle();
//
//				bool hasChanged = false;
//
//				double minFuncAngle = tempAngle;
//				double minFuncValue = sum_error;
//
//				arcs[i]->SetAngle(tempAngle - delta);
//				double funcValue = GetError();
//
//				if (funcValue < minFuncValue) {
//					minFuncValue = funcValue;
//					minFuncAngle = tempAngle - delta;
//					hasChanged = true;
//				}
//
//				arcs[i]->SetAngle(tempAngle + delta);
//				funcValue = GetError();
//
//				if (funcValue < minFuncAngle) {
//					minFuncValue = funcValue;
//					minFuncAngle = tempAngle + delta;
//					hasChanged = true;
//				}
//
//				if (!hasChanged) {
//					delta /= delta_increasing_k;
//				}
//				else {
//					arcs[i]->SetAngle(minFuncAngle);
//					sum_error = minFuncValue;
//					break;
//				}
//			}
//		}
//
//		if (count % 25 == 0) {
//			std::cout << sum_error << "   "<< iterInside << "   " << EPS << "  " << delta << "\n";
//			if (count % 50 == 0) {
//				if (EPS < 0.01) {
//					EPS *= 2;
//				}
//				if (count > 400) {
//					//std::cout << sum_error << "   " << iterInside << "   " << EPS << "  " << delta << "\n";
//					return count;
//				}
//				if (prevLastError == sum_error) {
//					return count;
//				}
//				prevLastError = sum_error;
//			}
//		}
//		if (prevError == sum_error) {
//			if (iterInside < 24) {
//				iterInside *= 2;
//			}
//		}
//		else {
//			if (iterInside > 3) {
//				iterInside /= 2;
//			}
//		}
//		prevError = sum_error;
//	}
//	std::cout << sum_error << "   " << iterInside << "   " << EPS << "  " << delta << "\n";
//	return count;
//}

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

void Model::OptimizeRequirements(const Array<Requirement*>& requirments) {
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
	Set<double*, UniqueParam> set;
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
			bool notUniqueParam = set.GetByKey(currentParameter, unique_param);

			if (notUniqueParam) {
				match_array[all_parameters_iterator] = unique_param.unique_number;
			}
			else {
				unique_param = UniqueParam{ currentParameter, uniq_numbers_iterator };
				set.Push(currentParameter, unique_param);
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
	while (GetError(requirments) > OPTIM_EPS) {
		int match_array_iterator = 0;
		for (int i = 0; i < requirments.GetSize(); ++i) {
			Array<double> currentGradient = requirments[i]->gradient();
			for (int j = 0; j < currentGradient.GetSize(); ++j) {
				aGradient[match_array[match_array_iterator]] -= currentGradient[j] / requirments.GetSize();
				++match_array_iterator;
			}
		}

		OptimizeByGradient(requirments, unique_parameters, aGradient);
		aGradient.FillDefault(0.0);
		err = GetError(requirments);
	}
}

bool Model::getObjType(const ID& obj_id, prim_type& type) {
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

bool Model::getObjParam(const ID& obj_id, Array<double>& result) {
	Primitive* obj = nullptr;
	auto dataPrimMarker = dataPrim.Find(obj_id);
	if (dataPrimMarker.IsValid()) {
		obj = dataPrimMarker.GetValue();
		switch (obj->GetType()) {
		case point_t: {
			Point* point = dynamic_cast<Point*>(obj);
			result.Clear();
			Vector2 pos = point->GetPosition();
			result.PushBack(pos.x);
			result.PushBack(pos.y);
			return true;
			break;
		}
		case segment_t: {
			Segment* segment = dynamic_cast<Segment*>(obj);
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
			Arc* arc = dynamic_cast<Arc*>(obj);
			result.Clear();
			Vector2 pos1 = arc->GetPoint1_pos();
			Vector2 pos2 = arc->GetPoint2_pos();
			double angle = arc->GetAngle();
			result.PushBack(pos1.x);
			result.PushBack(pos1.y);
			result.PushBack(pos2.x);
			result.PushBack(pos2.y);
			result.PushBack(angle);
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

bool Model::getNearest(double x, double y, ID& obj_id, double& distance) {
	if (dataPrim.GetSize() != 0) {
		Vector2 pos(x, y);
		auto dataPrimMarker = dataPrim.GetMarker();
		ID nearestObject = dataPrimMarker.GetValue()->GetID();
		double minDist = dataPrimMarker.GetValue()->GetDistance(pos);
		while (++dataPrimMarker) {
			double dist = dataPrimMarker.GetValue()->GetDistance(pos);
			if (dataPrimMarker.GetValue()->GetType() == point_t) {
				if (dist < 5.0f) {
					dist = 0.0;
				}
			}
			if (dist < minDist && dataPrimMarker.GetValue()->GetType() == point_t) {
				minDist = dist;
				nearestObject = dataPrimMarker.GetValue()->GetID();
			}
		}
		distance = minDist;
		obj_id = nearestObject;
		return true;
	}
	else
	{
		return false;
	}
}

void Model::OptimizeAllRequirements() {
	Array<Requirement*> req;
	auto dataReqMarker = dataReq.GetMarker();
	do
	{
		req.PushBack(dataReqMarker.GetValue());
	} while (++dataReqMarker);
	OptimizeRequirements(req);
}

#ifdef MODEL_VERSION_DATA

void Model::XXXConnectPrimitives(Primitive* prim1, Primitive* prim2, Primitive* prim3) {
	ConnectionReq* connect = new ConnectionReq;
	Array<int> index(3);
	index[0] = -1;
	index[1] = -1;
	index[2] = -1;
	Array<ID> IDPrims(3);
	IDPrims[0] = prim1->GetID();
	IDPrims[1] = prim2->GetID();
	IDPrims[2] = prim3->GetID();
	Array<Primitive*> Prims(3);
	Prims[0] = prim1;
	Prims[1] = prim2;
	Prims[2] = prim3;
	data.Add(index, IDPrims, Prims, connect->GetID(), connect);
}

bool Model::XXXCreateObject(const prim_type type, Array<double>& params, ID& obj_id) {
	switch (type)
	{
	case point_t: {
		if (params.GetSize() != 2) {
			return false;
		}
		Point* point = new Point(params[0], params[1]);
		obj_id = point->GetID();
		data.dict->Add(obj_id, point);
		return true;
	}
	case segment_t: {
		if (params.GetSize() != 4) {
			return false;
		}
		Point* point1 = new Point(params[0], params[1]);
		Point* point2 = new Point(params[2], params[3]);

		Segment* segment = new Segment(point1, point2);
		obj_id = segment->GetID();

		point1->SetParent(segment);
		point2->SetParent(segment);

		XXXConnectPrimitives(point1, point2, segment);
		return true;
	}
	case arc_t: {
		if (params.GetSize() != 5) {
			return false;
		}
		Point* point1 = new Point(params[0], params[1]);
		Point* point2 = new Point(params[2], params[3]);

		Arc* arc = new Arc(point1, point2, params[4]);
		obj_id = arc->GetID();

		point1->SetParent(arc);
		point2->SetParent(arc);

		XXXConnectPrimitives(point1, point2, arc);
		return true;
	}
	default:
		return false;
	}
}

bool Model::XXXCreateRequirementByID(const req_type type, Array<int>& index, Array<ID>& IDPrims, Array<double>& params) {
	// verification size arrays	
	if (IDPrims.GetSize() != index.GetSize()) {
		throw std::exception("size is not equal!!!");
	}

	Array<Primitive*> arrayPrim(IDPrims.GetSize());
	for (int i = 0; i < IDPrims.GetSize(); ++i) {
		if (index[i] < 0) {
			auto marker = data.dict->Find(IDPrims[i]);
			arrayPrim.PushBack(marker.GetValue());
		}
		else {
			auto gMarker = data.Find(index[i], IDPrims[i]);
			arrayPrim.PushBack(gMarker.GetValue());
		}
	}
	return XXXCreateRequirement(type, index, IDPrims, arrayPrim, params);
}

bool Model::XXXCreateRequirement(const req_type type, Array<int>& index, Array<ID>& IDPrims, Array<Primitive*>& primitives, Array<double>& params) {
	switch (type)
	{
	case distBetPoints: {
		// verification parameters
		if ((primitives.GetSize() != 2)
			&& (params.GetSize() != 1)
			&& (primitives[0]->GetType() != point_t)
			&& (primitives[1]->GetType() != point_t)) {
			return false;
		}
		// creating
		DistBetPointsReq* requirement;
		requirement = new DistBetPointsReq(cast<Point*>(primitives[0]),
			cast<Point*>(primitives[1]),
			params[0]);
		dataReq.Add(requirement->GetID(), requirement);


		data.Add(index, IDPrims, primitives, requirement->GetID(), requirement);
		return true;
	}
	case equalSegmentLen: {
		// verification parameters
		if (primitives.GetSize() != 2
			&& params.GetSize() == 0
			&& (primitives[0]->GetType() != segment_t)
			&& (primitives[1]->GetType() != segment_t)) {
			return false;
		}
		// creating
		EqualSegmentLenReq* requirement = new EqualSegmentLenReq(*cast<Segment*>(primitives[0]),
			*cast<Segment*>(primitives[1]));
		dataReq.Add(requirement->GetID(), requirement);


		data.Add(index, IDPrims, primitives, requirement->GetID(), requirement);
		return true;
	}
	case pointsOnTheOneHand: {
		// verification parameters
		if ((primitives.GetSize() != 3)
			&& (params.GetSize() == 0)
			&& (primitives[0]->GetType() == segment_t)
			&& (primitives[1]->GetType() == point_t)
			&& (primitives[2]->GetType() == point_t))
		{
			return false;
		}
		// creating
		PointsOnTheOneHand* requirement = new PointsOnTheOneHand(*cast<Segment*>(primitives[0]),
			*cast<Point*>(primitives[1]),
			*cast<Point*>(primitives[2]));
		dataReq.Add(requirement->GetID(), requirement);

		data.Add(index, IDPrims, primitives, requirement->GetID(), requirement);
		return true;
	}
	case distBetPointSeg: {
		// verification parameters
		if ((primitives.GetSize() != 2)
			&& (params.GetSize() != 1)
			&& (primitives[0]->GetType() != segment_t)
			&& (primitives[1]->GetType() != point_t))
		{
			return false;
		}
		// creating
		DistanceBetweenPointSegment* requirement = new DistanceBetweenPointSegment(*cast<Segment*>(primitives[0]),
			*cast<Point*>(primitives[1]),
			params[0]);
		dataReq.Add(requirement->GetID(), requirement);

		data.Add(index, IDPrims, primitives, requirement->GetID(), requirement);
		return true;
	}
	case angleBetSeg: {
		// verification parameters
		if ((primitives.GetSize() != 2)
			&& (params.GetSize() == 1)
			&& (primitives[0]->GetType() == segment_t)
			&& (primitives[1]->GetType() == segment_t))
		{
			return false;
		}
		// creating
		AngleBetweenSegments* requirement = new AngleBetweenSegments(*cast<Segment*>(primitives[0]),
			*cast<Segment*>(primitives[1]),
			params[0]);
		dataReq.Add(requirement->GetID(), requirement);

		data.Add(index, IDPrims, primitives, requirement->GetID(), requirement);
		return true;

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
		DistanceBetweenPointArc* requirement = new DistanceBetweenPointArc(*cast<Arc*>(primitives[0]),
			*cast<Point*>(primitives[1]),
			params[0]);
		dataReq.Add(requirement->GetID(), requirement);

		data.Add(index, IDPrims, primitives, requirement->GetID(), requirement);
		return true;
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
		PointInArc* requirement = new PointInArc(*cast<Arc*>(primitives[0]),
			*cast<Point*>(primitives[1]));
		dataReq.Add(requirement->GetID(), requirement);

		data.Add(index, IDPrims, primitives, requirement->GetID(), requirement);
		return true;
	}
	default:
		return false;
	}
}

void Model::XXXGetRequirementsByID(int index, const ID& id, Array<Requirement*>& arrayReq) {
	data.GetRequirementsByPrim(index, id, arrayReq);
}

void Model::XXXGetRequirementsIDByID(int index, const ID& id, Array<ID>& arrayReqID) {
	data.GetIDRequirementsByPrim(index, id, arrayReqID);
}

void Model::XXXGetRequirementsType(int index, const ID& id, Array<req_type>& arrayReqType) {
	Array<Requirement*> arrayReq;
	data.GetRequirementsByPrim(index, id, arrayReq);
	for (int i = 0; i < arrayReq.GetSize(); ++i) {
		arrayReqType.PushBack(arrayReq[i]->GetType());
	}
}

void Model::XXXDeleteRequirement(int index, const ID& id) {
	data.DeleteRequirement(index, id);
}

void Model::XXXDeletePrimitive(int index, const ID& id) {
	if (index < 0) {
		auto marker = data.dict->Find(id);
		marker.DeleteCurrent();
		return;
	}
	data.DeletePrimitive(index, id);
}

#endif