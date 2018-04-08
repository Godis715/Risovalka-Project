#include "Model.h"
#include <stdexcept>

bool Model::DischargeInfoObjects(Array<infoObject>& DataInfoObjects)
{
	if (data.GetSize() == 0) {
		return false;
	}
	data.MoveBegin();
	do
	{
		infoObject temp;
		getObjParam(data.GetCurrentKey(), temp.params);
		getObjType(data.GetCurrentKey(), temp.type);
		DataInfoObjects.pushBack(temp);
	} while (data.MoveNext());
	return true;
}

bool Model::createObject(type_id type, Array<double>& params, ID& obj_id) {
	switch (type)
	{
	case point: {
		if (params.getSize() != 2) {
			return false;
		}
		Point* _point;
		_point = new Point(params[0], params[1]);
		data.Add(_point->GetID(),_point);
		obj_id = _point->GetID();
		return true;
	}
	case segment: {
		if (params.getSize() != 4) {
			return false;
		}
		Point* p1 = new Point(params[0], params[1]);
		Point* p2 = new Point(params[2], params[3]);

		Segment* _seg = new Segment(p1, p2);

		data.Add(p1->GetID(), p1);
		data.Add(p2->GetID(), p2);
		data.Add(_seg->GetID(), _seg);

		obj_id = _seg->GetID();
		return true;
	}
	case arc: {
		if (params.getSize() != 5) {
			return false;
		}
		Point* p1 = new Point(params[0], params[1]);
		Point* p2 = new Point(params[2], params[3]);

		Arc* _arc = new Arc(p1, p2, params[4]);

		data.Add(p1->GetID(), p1);
		data.Add(p2->GetID(), p2);
		data.Add(_arc->GetID(), _arc);

		obj_id = _arc->GetID();
		return true;
	}
	default:
		return false;
	}
}

bool Model::createSegment(ID& p1ID, ID& p2ID, ID& segID) {
	Primitive* point1PR;
	Primitive* point2PR;
	bool error = false;
	if (data.Find(p1ID)) {
		point1PR = data.GetCurrent();
		if (data.Find(p2ID)) {
			point2PR = data.GetCurrent();
			if ((point1PR->GetType() == point) && (point2PR->GetType() == point)) {
				Point* point1 = dynamic_cast<Point*>(point1PR);
				Point* point2 = dynamic_cast<Point*>(point2PR);
				Segment* segment = new Segment(point1, point2);
				segID = segment->GetID();
				data.Add(segID, segment);
				return true;
			}
		}
	}
	return false;
}

bool Model::createRequirement(const Requirement_id _id, Array<ID>& id_arr, Array<double>& params) {
	Array<Primitive*> primitives;
	for (int i = 0; i < id_arr.getSize(); ++i) {
		if (data.Find(id_arr[i])) {
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

		if ((primitives[0]->GetType() == point)
			&& (primitives[1]->GetType() == point)
			&& (params.getSize() > 0)) {
		Requirement = new DistanceBetweenPoints(*dynamic_cast<Point*>(primitives[0]),
			*dynamic_cast<Point*>(primitives[1]),
			params[0]);
		dataReq.pushBack(Requirement);
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
			dataReq.pushBack(Requirement);
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
			&& (params.getSize() > 0)) {
			Requirement = new DistanceBetweenPointSegment(*dynamic_cast<Segment*>(primitives[0]),
				*dynamic_cast<Point*>(primitives[1]),
				params[0]);
			dataReq.pushBack(Requirement);
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
			&& (params.getSize() > 0)) {
			Requirement = new AngleBetweenSegments(*dynamic_cast<Segment*>(primitives[0]),
				*dynamic_cast<Segment*>(primitives[1]),
				params[0]);
			dataReq.pushBack(Requirement);
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
			&& (params.getSize() > 0)) {
			Requirement = new DistanceBetweenPointArc(*dynamic_cast<Arc*>(primitives[0]),
				*dynamic_cast<Point*>(primitives[1]),
				params[0]);
			dataReq.pushBack(Requirement);
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
			dataReq.pushBack(Requirement);
			return true;
		}
		else {
			return false;
		}
	}
	case triangle: {
		Triangle* Requirement;
		if ((primitives[0]->GetType() == segment)
			&& (primitives[1]->GetType() == segment)
			&& (primitives[2]->GetType() == segment)) {
			Requirement = new Triangle(dynamic_cast<Segment*>(primitives[0]),
				dynamic_cast<Segment*>(primitives[1]),
				dynamic_cast<Segment*>(primitives[2]));
			dataReq.pushBack(Requirement);
			return true;
		}
		else {
			return false;
		}
	}
	case correctTriangle: {
		ÑorrectTriangle* Requirement;
		if ((primitives[0]->GetType() == segment)
			&& (primitives[1]->GetType() == segment)
			&& (primitives[2]->GetType() == segment)
			&& (params.getSize() > 0)) {
			Requirement = new ÑorrectTriangle(dynamic_cast<Segment*>(primitives[0]),
				dynamic_cast<Segment*>(primitives[1]),
				dynamic_cast<Segment*>(primitives[2]),
				params[0]);
			dataReq.pushBack(Requirement);
			return true;
		}
		else {
			return false;
		}
	}
	case nsAngle: {
		NsAngle* Requirement;
		ListE<Segment*> list;
		for (int i = 0; i < primitives.getSize(); ++i) {
			if (segment == primitives[i]->GetType()) {
				list.PushTail(dynamic_cast<Segment*>(primitives[i]));
			}
			else {
				return false;
			}
		}
		Requirement = new NsAngle(list);
		dataReq.pushBack(Requirement);
		return true;
	}
	case correctNsAngle: {
		CorrectNsAngle* Requirement;
		
		if (params.getSize() > 0) {
			ListE<Segment*> list;
			for (int i = 0; i < primitives.getSize(); ++i) {
				if (segment == primitives[i]->GetType()) {
					list.PushTail(dynamic_cast<Segment*>(primitives[i]));
				}
				else {
					return false;
				}
			}
			Requirement = new CorrectNsAngle(list, params[0]);
			dataReq.pushBack(Requirement);
			return true;
		}
		else {
			return false;
		}
	}
	default:
		return false;
	}
}

double Model::GetError() {
	double sum_error = 0;
	for (int i = 0; i < dataReq.getSize(); i++)
	{
		sum_error += dataReq[i]->error();
	}
	return sum_error / dataReq.getSize();
}

int Model::Optimize1() {

	if (data.GetSize() == 0) {
		return 0;
	}

	Array<Point*> points;
	Array<Arc*> arcs;

	data.MoveBegin();
	do {
		Primitive* obj = data.GetCurrent();
		if (obj->GetType() == point) {
			points.pushBack(dynamic_cast<Point*>(obj));
		}
		else if (obj->GetType() == arc) {
			arcs.pushBack(dynamic_cast<Arc*>(obj));
		}
	} while (data.MoveNext());

	const double delta_increasing_k = 2.0;
	double sum_error = 0;
	sum_error = GetError();
	double prevError = sum_error;
	double prevLastError = sum_error;
	int count = 0;
	int iterInside = 3;
	double delta = sum_error;
	EPS = 1e-5;
	std::cout << sum_error << "   " << iterInside << "   " << EPS << "  " << delta << "\n";

	while (sum_error > EPS) {
		++count;
		for (int i = 0; i < points.getSize(); ++i) {

			delta = sum_error;

			Vector2 pos = points[i]->GetPosition();
			for (int k = 0; k < iterInside; ++k)
			{
				double shift_x[]{ delta, -delta, delta, -delta, delta, -delta, 0, 0 };
				double shift_y[]{ delta, delta, -delta, -delta, 0, 0, delta, -delta };

				double minFuncValue = sum_error;
				Vector2 minFuncPos = pos;
				bool hasChanged = false;

				for (int j = 0; j < 8; ++j) {

					points[i]->SetPosition(pos.x + shift_x[j], pos.y + shift_y[j]);

					double funcValue = GetError();

					if (funcValue < minFuncValue) {

						minFuncValue = funcValue;

						minFuncPos = pos;
						minFuncPos.x += shift_x[j];
						minFuncPos.y += shift_y[j];

						hasChanged = true;
					}
				}

				if (!hasChanged) {
					delta /= delta_increasing_k;
				}
				else {
					sum_error = minFuncValue;
					points[i]->SetPosition(minFuncPos);
					break;
				}
				if (delta < 1e-6) {
					break;
				}
			}
		}
		for (int i = 0; i < arcs.getSize(); ++i) {
			double delta = sum_error;
			while (delta > EPS) {
				double tempAngle = arcs[i]->GetAngle();

				bool hasChanged = false;

				double minFuncAngle = tempAngle;
				double minFuncValue = sum_error;

				arcs[i]->SetAngle(tempAngle - delta);
				double funcValue = GetError();

				if (funcValue < minFuncValue) {
					minFuncValue = funcValue;
					minFuncAngle = tempAngle - delta;
					hasChanged = true;
				}

				arcs[i]->SetAngle(tempAngle + delta);
				funcValue = GetError();

				if (funcValue < minFuncAngle) {
					minFuncValue = funcValue;
					minFuncAngle = tempAngle + delta;
					hasChanged = true;
				}

				if (!hasChanged) {
					delta /= delta_increasing_k;
				}
				else {
					arcs[i]->SetAngle(minFuncAngle);
					sum_error = minFuncValue;
					break;
				}
			}
		}

		if (count % 25 == 0) {
			std::cout << sum_error << "   "<< iterInside << "   " << EPS << "  " << delta << "\n";
			if (count % 50 == 0) {
				if (EPS < 0.01) {
					EPS *= 2;
				}
				if (count > 400) {
					//std::cout << sum_error << "   " << iterInside << "   " << EPS << "  " << delta << "\n";
					return count;
				}
				if (prevLastError == sum_error) {
					return count;
				}
				prevLastError = sum_error;
			}
		}
		if (prevError == sum_error) {
			if (iterInside < 24) {
				iterInside *= 2;
			}
		}
		else {
			if (iterInside > 3) {
				iterInside /= 2;
			}
		}
		prevError = sum_error;
	}
	std::cout << sum_error << "   " << iterInside << "   " << EPS << "  " << delta << "\n";
	return count;
}

double Model::GetError(Array<IRequirement*>& requirments) {
	double error = 0.0;
	for (int i = 0; i < requirments.getSize(); ++i) {
		error += requirments[i]->error();
	}
	return error / requirments.getSize();
}

double Model::ErrorByAlpha(Array<IRequirement*>& req, Parameters<double*> params, Parameters<double> aGrad, double alpha) {
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

void Model::OptimizeByGradient(Array<IRequirement*>& requirments, Parameters<double*> params, Parameters<double> aGradient) {

	const double gold_section = 1.6180339887498;
	int reqSize = requirments.getSize();

	double error = GetError(requirments);

	double left = 0.0;
	double right = 0.1 * (double)reqSize;

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

void Model::OptimizeRequirements(Array<IRequirement*>& requirments) {
	// get parameters number
	int params_number = 0;
	for (int i = 0; i < requirments.getSize(); ++i) {
		Parameters<double*> params = requirments[i]->GetParams();
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

	Parameters<double*> all_parameters(params_number);
	Set<double*, UniqueParam> set;
	int* match_array = new int[params_number];

	// from 0 to params_number
	int all_parameters_iterator = 0;

	// from 0 to number of unique double*
	int uniq_numbers_iterator = 0;

	// filling match_array
	for (int i = 0; i < requirments.getSize(); ++i) {

		Parameters<double*> currentRequirmentParams = requirments[i]->GetParams();

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
	Parameters<double*> unique_parameters(uniq_numbers_iterator, nullptr);

	for (int i = 0; i < params_number; ++i) {
		unique_parameters[match_array[i]] = all_parameters[i];
	}

	// anti gradient
	Parameters<double> aGradient(uniq_numbers_iterator, 0.0);

	//filling anti gradient
	double err = GetError(requirments);
	while (GetError(requirments) > OPTIM_EPS) {
		int match_array_iterator = 0;
		for (int i = 0; i < requirments.getSize(); ++i) {
			Parameters<double> currentGradient = requirments[i]->gradient();
			for (int j = 0; j < currentGradient.GetSize(); ++j) {
				aGradient[match_array[match_array_iterator]] -= currentGradient[j];
				++match_array_iterator;
			}
		}

		OptimizeByGradient(requirments, unique_parameters, aGradient);
		aGradient = Parameters<double>(uniq_numbers_iterator, 0.0);
		err = GetError(requirments);
	}
}


bool Model::getObjType(const ID& obj_id, type_id& type) {
	Primitive* obj = nullptr;
	bool isFound = data.Find(obj_id);
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
	bool isFound = data.Find(obj_id);
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
			return true;
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
	if (!data.Find(obj_id)) {
		return false;
	}
	obj = data.GetCurrent();
	if (obj->GetType() != segment) {
		return false;
	}
	Segment* segment = dynamic_cast<Segment*>(obj);
	arr.pushBack(segment->GetPoint1_ID());
	arr.pushBack(segment->GetPoint2_ID());
	return true;
}

bool Model::GetArcPoints(ID obj_id, Array<ID>& arr) {
	Primitive* obj;
	if (!data.Find(obj_id)) {
		return false;
	}
	obj = data.GetCurrent();
	if (obj->GetType() != arc) {
		return false;
	}
	Arc* arc = dynamic_cast<Arc*>(obj);
	arr.pushBack(arc->GetPoint1_ID());
	arr.pushBack(arc->GetPoint2_ID());
	return true;
}

void  Model::PrintSystemRequirement() {
	for (int i = 0; i < dataReq.getSize(); ++i) {
		std::cout << std::endl;
		std::cout << i << ":\n";
		dataReq[i]->Print();
	}
}

bool Model::getNearest(double x, double y, ID& obj_id, double& distance) {
	if (data.GetSize() != 0) {
		Vector2 pos(x, y);
		data.MoveBegin();
		ID nearestObject = data.GetCurrent()->GetID();
		double minDist = data.GetCurrent()->GetDistance(pos);
		while (data.MoveNext()) {
			double dist = data.GetCurrent()->GetDistance(pos);
			if (data.GetCurrent()->GetType() == point) {
				if (dist < 5.0f) {
					dist = 0.0;
				}
			}
			if (dist < minDist && data.GetCurrent()->GetType() == point) {
				minDist = dist;
				nearestObject = data.GetCurrent()->GetID();
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
	Array<IRequirement*> req;
	for (int i = 0; i < dataReq.getSize(); ++i) {
		req.pushBack(dataReq[i]);
	}
	OptimizeRequirements(req);
}