#include "Model.h"
#include <iostream>
#include <stdexcept>

Model::Link::Link(const ID& primID, const ID& reqID)
{
	this->primID = primID;
	this->reqID = reqID;
}

void Model::GetIDRequirements(const ID& id, Array<ID>& FoundIDRequirement)
{
	Dict<ID, ID> labels;
	Queue<ID> forConsideration;
	forConsideration.push(id);
	do
	{
		ID tempID = forConsideration.pop();
		if (!labels.Find(tempID))
		{
			for (int i = 0; i < dataLink.GetSize(); i++)
			{
				if (dataLink[i].reqID == id)
				{
					forConsideration.push(dataLink[i].primID);
				}

				if (dataLink[i].primID == id)
				{
					FoundIDRequirement.PushBack(dataLink[i].reqID);
					forConsideration.push(dataLink[i].reqID);
				}
			}
			labels.Add(tempID, tempID);
		}
	} while (!forConsideration.isEmpty());
}

bool Model::find(const ID& id, Array<ID> foundID)
{
	bool isFound = false;
	for (int i = 0; i < dataLink.GetSize(); i++)
	{
		if (dataLink[i].reqID == id)
		{
			foundID.PushBack(dataLink[i].primID);
			isFound = true;
		}

		if (dataLink[i].primID == id)
		{
			foundID.PushBack(dataLink[i].reqID);
			isFound = true;
		}
	}
	return isFound;
}

bool Model::find(const ID& idReq, Array<Primitive*>& foundPrim)
{
	bool isFound = false;
	for (int i = 0; i < dataLink.GetSize(); i++)
	{
		if (dataLink[i].reqID == idReq)
		{
			if (dataPrim.Find(dataLink[i].primID)) {
				foundPrim.PushBack(dataPrim.GetCurrent());
				isFound = true;
			}
		}
	}
	return isFound;
}

bool Model::find(const ID& idPrim, Array<Requirement*>& foundReq)
{
	bool isFound = false;
	for (int i = 0; i < dataLink.GetSize(); i++)
	{
		if (dataLink[i].primID == idPrim)
		{
			if (dataReq.Find(dataLink[i].reqID)) {
				foundReq.PushBack(dataReq.GetCurrent());
				isFound = true;
			}
		}
	}
	return isFound;
}

bool Model::DischargeInfoObjects(Array<infoObject>& dataPrimInfoObjects)
{
	if (dataPrim.GetSize() == 0) {
		return false;
	}
	dataPrim.MoveBegin();
	do
	{
		infoObject temp;
		getObjParam(dataPrim.GetCurrentKey(), temp.params);
		getObjType(dataPrim.GetCurrentKey(), temp.type);
		dataPrimInfoObjects.PushBack(temp);
	} while (dataPrim.MoveNext());
	return true;
}

bool Model::createObject(type_id type, Array<double>& params, ID& obj_id) {
	switch (type)
	{
	case point: {
		if (params.GetSize() != 2) {
			return false;
		}
		Point* _point;
		_point = new Point(params[0], params[1]);
		dataPrim.Add(_point->GetID(),_point);
		obj_id = _point->GetID();
		return true;
	}
	case segment: {
		if (params.GetSize() != 4) {
			return false;
		}
		Point* p1 = new Point(params[0], params[1]);
		Point* p2 = new Point(params[2], params[3]);

		Segment* _seg = new Segment(p1, p2);

		dataPrim.Add(p1->GetID(), p1);
		dataPrim.Add(p2->GetID(), p2);
		dataPrim.Add(_seg->GetID(), _seg);

		obj_id = _seg->GetID();
		return true;
	}
	case arc: {
		if (params.GetSize() != 5) {
			return false;
		}
		Point* p1 = new Point(params[0], params[1]);
		Point* p2 = new Point(params[2], params[3]);

		Arc* _arc = new Arc(p1, p2, params[4]);

		dataPrim.Add(p1->GetID(), p1);
		dataPrim.Add(p2->GetID(), p2);
		dataPrim.Add(_arc->GetID(), _arc);

		obj_id = _arc->GetID();
		return true;
	}
	default:
		return false;
	}
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

bool Model::createRequirement(const Requirement_id _id, Array<ID>& id_arr, Array<double>& params) {
	Array<Primitive*> primitives;
	for (int i = 0; i < id_arr.GetSize(); ++i) {
		if (dataPrim.Find(id_arr[i])) {
			primitives.PushBack(dataPrim.GetCurrent());
		}
		else {
			return false;
		}
	}
	switch (_id)
	{
	case distBetPoints: {
		DistanceBetweenPoints* Requirement;

		if ((primitives[0]->GetType() == point)
			&& (primitives[1]->GetType() == point)
			&& (params.GetSize() > 0)) {
		Requirement = new DistanceBetweenPoints(dynamic_cast<Point*>(primitives[0]),
			dynamic_cast<Point*>(primitives[1]),
			params[0]);
		dataReq.Add(Requirement->GetID(), Requirement);
		dataLink.PushBack(Link(primitives[0]->GetID(), Requirement->GetID()));
		dataLink.PushBack(Link(primitives[1]->GetID(), Requirement->GetID()));
		return true;
		}
		else {
			return false;
		}
	}
	case pointsOnTheOneHand: {
		PointsOnTheOneHand* Requirement;
		if ((primitives[0]->GetType() == segment)
			&& (primitives[1]->GetType() == point)
			&& (primitives[2]->GetType() == point)) {
			Requirement = new PointsOnTheOneHand(*dynamic_cast<Segment*>(primitives[0]),
				*dynamic_cast<Point*>(primitives[1]),
				*dynamic_cast<Point*>(primitives[2]));
			dataReq.Add(Requirement->GetID(), Requirement);
			dataLink.PushBack(Link(primitives[0]->GetID(), Requirement->GetID()));
			dataLink.PushBack(Link(primitives[1]->GetID(), Requirement->GetID()));
			dataLink.PushBack(Link(primitives[2]->GetID(), Requirement->GetID()));
			return true;
		}
		else {
			return false;
		}
	}
	case distBetPointSeg: {
		DistanceBetweenPointSegment* Requirement;
		if ((primitives[0]->GetType() == segment)
			&& (primitives[1]->GetType() == point)
			&& (params.GetSize() > 0)) {
			Requirement = new DistanceBetweenPointSegment(*dynamic_cast<Segment*>(primitives[0]),
				*dynamic_cast<Point*>(primitives[1]),
				params[0]);
			dataReq.Add(Requirement->GetID(), Requirement);
			dataLink.PushBack(Link(primitives[0]->GetID(), Requirement->GetID()));
			dataLink.PushBack(Link(primitives[1]->GetID(), Requirement->GetID()));
			return true;
		}
		else {
			return false;
		}
	}
	case angleBetSeg: {
		AngleBetweenSegments* Requirement;
		if ((primitives[0]->GetType() == segment)
			&& (primitives[1]->GetType() == segment)
			&& (params.GetSize() > 0)) {
			Requirement = new AngleBetweenSegments(*dynamic_cast<Segment*>(primitives[0]),
				*dynamic_cast<Segment*>(primitives[1]),
				params[0]);
			dataReq.Add(Requirement->GetID(), Requirement);
			dataLink.PushBack(Link(primitives[0]->GetID(), Requirement->GetID()));
			dataLink.PushBack(Link(primitives[1]->GetID(), Requirement->GetID()));
			return true;
		}
		else {
			return false;
		}
	}
	case distBetPointArc: {
		DistanceBetweenPointArc* Requirement;
		if ((primitives[0]->GetType() == arc)
			&& (primitives[1]->GetType() == point)
			&& (params.GetSize() > 0)) {
			Requirement = new DistanceBetweenPointArc(*dynamic_cast<Arc*>(primitives[0]),
				*dynamic_cast<Point*>(primitives[1]),
				params[0]);
			dataReq.Add(Requirement->GetID(), Requirement);
			dataLink.PushBack(Link(primitives[0]->GetID(), Requirement->GetID()));
			dataLink.PushBack(Link(primitives[1]->GetID(), Requirement->GetID()));
			return true;
		}
		else {
			return false;
		}
	}
	case pointInArc: {
		PointInArc* Requirement;
		if ((primitives[0]->GetType() == arc)
			&& (primitives[1]->GetType() == point)) {
			Requirement = new PointInArc(*dynamic_cast<Arc*>(primitives[0]),
				*dynamic_cast<Point*>(primitives[1]));
			dataReq.Add(Requirement->GetID(), Requirement);
			dataLink.PushBack(Link(primitives[0]->GetID(), Requirement->GetID()));
			dataLink.PushBack(Link(primitives[1]->GetID(), Requirement->GetID()));
			return true;
		}
		else {
			return false;
		}
	}
	/*case triangle: {
		Triangle* Requirement;
		if ((primitives[0]->GetType() == segment)
			&& (primitives[1]->GetType() == segment)
			&& (primitives[2]->GetType() == segment)) {
			Requirement = new Triangle(dynamic_cast<Segment*>(primitives[0]),
				dynamic_cast<Segment*>(primitives[1]),
				dynamic_cast<Segment*>(primitives[2]));
			dataPrimReq.PushBack(Requirement);
			return true;
		}
		else {
			return false;
		}
	}*/
	//case correctTriangle: {
	//	ÑorrectTriangle* Requirement;
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
	/* case nsAngle: {
		NsAngle* Requirement;
		ListE<Segment*> list;
		for (int i = 0; i < primitives.GetSize(); ++i) {
			if (segment == primitives[i]->GetType()) {
				list.PushTail(dynamic_cast<Segment*>(primitives[i]));
			}
			else {
				return false;
			}
		}
		Requirement = new NsAngle(list);
		dataPrimReq.PushBack(Requirement);
		return true;
	}
	case correctNsAngle: {
		CorrectNsAngle* Requirement;
		
		if (params.GetSize() > 0) {
			ListE<Segment*> list;
			for (int i = 0; i < primitives.GetSize(); ++i) {
				if (segment == primitives[i]->GetType()) {
					list.PushTail(dynamic_cast<Segment*>(primitives[i]));
				}
				else {
					return false;
				}
			}
			Requirement = new CorrectNsAngle(list, params[0]);
			dataPrimReq.PushBack(Requirement);
			return true;
		}
		else {
			return false;
		}
	} */
	default:
		return false;
	}
}

double Model::GetError(){
	double sum_error = 0;
	dataReq.MoveHead();
	do
	{
		sum_error += dataReq.GetCurrent()->error();
	} while (dataReq.MoveNext());
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

bool Model::getObjType(const ID& obj_id, type_id& type) {
	Primitive* obj = nullptr;
	bool isFound = dataPrim.Find(obj_id);
	obj = dataPrim.GetCurrent();
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
	bool isFound = dataPrim.Find(obj_id);
	if (isFound) {
		obj = dataPrim.GetCurrent();
		switch (obj->GetType()) {
		case point: {
			Point* point = dynamic_cast<Point*>(obj);
			result.Clear();
			Vector2 pos = point->GetPosition();
			result.PushBack(pos.x);
			result.PushBack(pos.y);
			return true;
			break;
		}
		case segment: {
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
		case arc: {
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

bool Model::GetSegmentPoints(ID obj_id, Array<ID>& arr) {
	Primitive* obj;
	if (!dataPrim.Find(obj_id)) {
		return false;
	}
	obj = dataPrim.GetCurrent();
	if (obj->GetType() != segment) {
		return false;
	}
	Segment* segment = dynamic_cast<Segment*>(obj);
	arr.PushBack(segment->GetPoint1_ID());
	arr.PushBack(segment->GetPoint2_ID());
	return true;
}

bool Model::GetArcPoints(ID obj_id, Array<ID>& arr) {
	Primitive* obj;
	if (!dataPrim.Find(obj_id)) {
		return false;
	}
	obj = dataPrim.GetCurrent();
	if (obj->GetType() != arc) {
		return false;
	}
	Arc* arc = dynamic_cast<Arc*>(obj);
	arr.PushBack(arc->GetPoint1_ID());
	arr.PushBack(arc->GetPoint2_ID());
	return true;
}

//void  Model::PrintSystemRequirement() {
//	for (int i = 0; i < dataPrimReq.GetSize(); ++i) {
//		std::cout << std::endl;
//		std::cout << i << ":\n";
//		//dataPrimReq[i]->Print();
//	}
//}

bool Model::getNearest(double x, double y, ID& obj_id, double& distance) {
	if (dataPrim.GetSize() != 0) {
		Vector2 pos(x, y);
		dataPrim.MoveBegin();
		ID nearestObject = dataPrim.GetCurrent()->GetID();
		double minDist = dataPrim.GetCurrent()->GetDistance(pos);
		while (dataPrim.MoveNext()) {
			double dist = dataPrim.GetCurrent()->GetDistance(pos);
			if (dataPrim.GetCurrent()->GetType() == point) {
				if (dist < 5.0f) {
					dist = 0.0;
				}
			}
			if (dist < minDist && dataPrim.GetCurrent()->GetType() == point) {
				minDist = dist;
				nearestObject = dataPrim.GetCurrent()->GetID();
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
	dataReq.MoveHead();
	do
	{
		req.PushBack(dataReq.GetCurrent());
	} while (dataReq.MoveNext());
	OptimizeRequirements(req);
}