#ifndef REQUIREMENT_H
#define REQUIREMENT_H

#include "Primitives.h"
#define DELTA_X 10e-6

class Requirement;

class ReqController {
private:
	ReqController();
	static ReqController* instance;

	ObjectController* objCtrl;

	PrimController* primCtrl;

	Requirement* GetReq(const ID&) const;
	Requirement* ConvertToReq(Object*) const;
public:
	static ReqController* GetInstance();

	bool IsReq(object_type) const;

	bool IsReq(const ID&) const;

	double GetReqError(const ID&) const;
	double GetReqError(const Array<ID>&) const;

	Array<double> GetReqParamsAsValues(const ID&) const;
	Array<double> GetGradient(const ID&) const;
	
	Array<double*> GetReqArgsAsPointers(const ID&) const;

	void SetReqParams(const ID&, const Array<double>&) const;
	void ApplyChanges(const ID&) const;

	ID CreateReq(object_type, const Array<ID>&, const Array<double>&) const;
};

class Requirement : public Object {
private:
	Array<double*> GetArgs() const;
protected:

	Array<double*> args;

	PrimController* primCtrl;
	
	friend class ReqController;
public:
	Requirement(object_type, const Array<double>&, const Array<ID>&);
	virtual double error() = 0;
	virtual Array<double> Gradient();
};


class DistBetPointsReq : public Requirement
{
private:
public:
	DistBetPointsReq(const Array<ID>&, const Array<double>&);

	double error();
};

class EqualSegmentLenReq : public Requirement {
private:
public:
	EqualSegmentLenReq(const Array<ID>& _objects, const Array<double>& _params) :
		Requirement(ot_equalSegmentLen, _params, _objects)
	{
		Array<ID> allPoints = primCtrl->GetChildren(_objects[0]) +
			primCtrl->GetChildren(_objects[1]);

		for (int i = 0; i < allPoints.GetSize(); ++i) {
			args = args + primCtrl->GetPrimitiveDoubleParamsAsPointers(allPoints[i]);
		}
	}

	double error() {
		Vector2 vec1(*(args[3]) - *(args[1]), *(args[2]) - *(args[0]));
		Vector2 vec2(*(args[7]) - *(args[5]), *(args[6]) - *(args[4]));

		double divergence = vec2.GetLength() - vec1.GetLength();
		return divergence * divergence;
	}
};
//
////class ConnectionReq : public Requirement {
////
////private:
////public:
////	ConnectionReq() :
////		Requirement(IDGenerator::getInstance()->generateID(), ot_connection)
////	{
////		args = Array<double*>(0);
////		params = Array<double>(0);
////	}
////	~ConnectionReq() { }
////	double error() {
////		return 0;
////	}
////};
//
class PointPosReq : public Requirement {
private:

public:
	PointPosReq(const Array<ID>& _objects, const Array<double>& _params) :
		Requirement(ot_pointPosReq, params, _objects) {

		for (int i = 0; i < _objects.GetSize(); ++i) {
			args = args + primCtrl->GetPrimitiveDoubleParamsAsPointers(_objects[i]);
		}
	}

	double error() {
		Vector2 vector(*args[0] - params[0], *args[1] - params[1]);
		return Vector2::Dot(vector, vector);
	}
};

class PointsOnTheOneHand : public Requirement
{
public:
	// _objects = <segment, point, point>
	PointsOnTheOneHand(const Array<ID>& _objects, const Array<double>& _params) :
		Requirement(ot_pointsOnTheOneHand, params, _objects)
	{
		Array<ID> objs = primCtrl->GetChildren(_objects[0]) +
			_objects[1] + _objects[2];

		for (int i = 0; i < objs.GetSize(); ++i) {
			args = args + primCtrl->GetPrimitiveDoubleParamsAsPointers(objs[i]);
		}
	}
	double error() {
		Vector2 pointPos1 = Vector2(*args[4], *args[5]);
		Vector2 pointPos2 = Vector2(*args[6], *args[7]);

		double Fx1 = /*segment->Inequality(pointPos1)*/0; // FIX
		double Fx2 =/* segment->Inequality(pointPos2)*/0; // FIX
		if ((Fx1 > 0 && Fx2 < 0) || (Fx1 < 0 && Fx2 > 0)) {
			Fx1 = abs(Fx1);
			Fx2 = abs(Fx2);

			if (Fx1 > Fx2) {
				double distance = /*segment->GetDist(pointPos2)*/0;
				return distance * distance;
			}
			else{
				double distance = /*segment->GetDist(pointPos1)*/0;
				return distance * distance;
			}
		}
		return 0;
	}
};

class DistanceBetweenPointSegment : public Requirement
{
public:
	// _objects = <segment, point>
	DistanceBetweenPointSegment(const Array<ID>& _objects, const Array<double>& _params) :
		Requirement(ot_distBetPointSeg, _params, _objects)
	{
		Array<ID> objs = primCtrl->GetChildren(_objects[0]) + _objects[1];
		for (int i = 0; i < objs.GetSize(); ++i) {
			args = args + primCtrl->GetPrimitiveDoubleParamsAsPointers(objs[i]);
		}
	}
	~DistanceBetweenPointSegment() {}
	double error() {
		Vector2 point(*args[4], *args[5]);
		double distance = /*segment->GetDist(point)*/ - params[0]; //FIX
		return distance * distance;
	}

	Array<double> gradient() { return Array<double>(); }
};
//
////class AngleBetweenSegments : public Requirement
////{
////public:
////	AngleBetweenSegments(Segment* _segment1, Segment* _segment2, double _andle) :
////		segment1(_segment1),
////		segment2(_segment2),
////		Requirement(IDGenerator::getInstance()->generateID(), ot_angleBetSeg)
////	{
////		args = Array<double*>(8);
////		params = Array<double>(1);
////
////		args[0] = &_segment1->point1->pos.x;
////		args[1] = &_segment1->point1->pos.y;
////		args[2] = &_segment1->point2->pos.x;
////		args[3] = &_segment1->point2->pos.y;
////		args[4] = &_segment2->point1->pos.x;
////		args[5] = &_segment2->point1->pos.y;
////		args[6] = &_segment2->point2->pos.x;
////		args[7] = &_segment2->point2->pos.y;
////
////		params[0] = abs(cos((_andle / 180) * PI));
////		sinus = sin((_andle / 180) * PI);
////	}
////	~AngleBetweenSegments() {}
////	double error() {
////		Vector2 vec1(*args[2] - *args[0], *args[3] - *args[1]);
////		Vector2 vec2(*args[6] - *args[4], *args[7] - *args[5]);
////		
////		double length1 = vec1.GetLength();
////		double length2 = vec2.GetLength();
////
////		// smaller side triangle:
////		Vector2 vec3 = vec1 - vec2;
////		if (Vector2::Dot(vec3, vec3) > length1 * length1 + length2 * length2 + DELTA_X) {
////			vec3 = (vec1 * -1) - vec2;
////		}
////		//
////		double length3 = sqrt(length1 * length1 + length2 * length2 - 2 * params[0] * length2* length1);
////
////		double different = length3 - vec3.GetLength();
////		return different * different;
////	}
////
////	void ChangeParams(const Array<double>& newParams) {
////		if (newParams.GetSize() != 1) {
////			throw std::exception("Invalid new param argement");
////		}
////		params[0] = abs(cos((newParams[0] / 180) * PI));
////		sinus = sin((newParams[0] / 180) * PI);
////	}
////private:
////	double sinus;
////	Segment* segment1;
////	Segment* segment2;
////};
////
////class DistanceBetweenPointArc : public Requirement
////{
////public:
////	DistanceBetweenPointArc(Arc* _arc, Point* _point, double _distance) :
////		arc(_arc),
////		point(_point),
////		Requirement(IDGenerator::getInstance()->generateID(), ot_distBetPointArc)
////	{
////		args = Array<double*>(7);
////		params = Array<double>(1);
////
////		args[0] = &_arc->point1->pos.x;
////		args[1] = &_arc->point1->pos.y;
////		args[2] = &_arc->point2->pos.x;
////		args[3] = &_arc->point2->pos.y;
////		args[4] = &_arc->angle;
////		args[5] = &_point->pos.x;
////		args[6] = &_point->pos.y;
////
////		params[0] = _distance;
////	}
////	~DistanceBetweenPointArc() {}
////	double error() {
////		Vector2 vector(point->pos - arc->GetCenter());
////		double modVector_inSquare = Vector2::Dot(vector, vector);
////		return modVector_inSquare - params[0] * (2 * sqrt(modVector_inSquare) - params[0]);
////	}
////private:
////	Arc* arc;
////	Point* point;
////}; 
//
class SegmentTouchCircle : public Requirement {
public:
	SegmentTouchCircle(const Array<ID>& _objects, const Array<double>& _params) :
		Requirement(ot_segmentTouchCircle, _params, _objects)
	{
		Array<ID> objs =
			primCtrl->GetChildren(_objects[0]) +
			primCtrl->GetChildren(_objects[1]) +
			_objects[1];

		for (int i = 0; i < objs.GetSize(); ++i) {
			args = args + primCtrl->GetPrimitiveDoubleParamsAsPointers(objs[i]);
		}
	}

	double error() {
		return 0.0;
	}

private:
	Circle * circle;
	Segment* segment;
};

// needed to fix
//
//class PointInArc : public Requirement
//{
//public:
//	PointInArc(Arc* _arc, Point* _point) :
//		arc(_arc),
//		point(_point),
//		Requirement(IDGenerator::getInstance()->generateID(), ot_pointInArc)
//	{
//		args[0] = &_arc->point1->pos.x;
//		args[1] = &_arc->point1->pos.y;
//		args[2] = &_arc->point2->pos.x;
//		args[3] = &_arc->point2->pos.y;
//		args[4] = &_arc->angle;
//		args[5] = &_point->pos.x;
//		args[6] = &_point->pos.y;
//	}
//	~PointInArc() {}
//	// return distance to arc and angle
//	double error() {
//		Vector2 center = arc->GetCenter();
//		Vector2 vec1 = arc->GetPointPos1() - center;
//		Vector2 vecPoint = point->GetPos() - center;
//		double angle = Vector2::Angle(vec1, vecPoint);
//		double angleArc = arc->GetAngle();
//		if (angle <= angleArc) {
//			return 0;
//		}
//		if (angle <= PI + angleArc / 2) {
//			if (angle < angleArc + PI / 2) {
//				return point->GetDist(center) * sin(angle - angleArc);
//			}
//			else {
//				return point->GetDist(center) + angle;
//			}
//		}
//		else {
//			if (angle < PI / 2) {
//				return point->GetDist(center) * sin(angle);
//			}
//			else {
//				return point->GetDist(center);
//			}
//		}
//	}
//private:
//	Arc* arc;
//	Point* point;
//};

// carefully delete
//class Triangle : public Requirement
//{
//public:
//	Triangle(Segment* _segment1, Segment* _segment2, Segment* _segment3) :
//		Requirement(IDGenerator::getInstance()->generateID())
//	{
//		Vector2 points[6];
//		points[0] = _segment1->GetPoint1_pos();
//		points[1] = _segment1->GetPoint2_pos();
//		points[2] = _segment1->GetPoint1_pos();
//		points[3] = _segment1->GetPoint2_pos();
//		points[4] = _segment1->GetPoint1_pos();
//		points[5] = _segment1->GetPoint2_pos();
//		Vector2 temp;
//		double minDist = 0;
//		double dist = 0;
//		segment1 = _segment1;
//		minDist = (points[0] - points[2]).GetLength();
//		segment2 = _segment2;
//		bijection[0] = false;
//		bijection[2] = false;
//		int i = 3;
//		int index = i;
//		for (i; i < 6; ++i) {
//			bijection[i] = false;
//			dist = (points[0] - points[i]).GetLength();
//			if (dist < minDist) {
//				minDist = dist;
//				if (i == 3) {
//					bijection[0] = true;
//					
//					index = 2;
//				}
//				else {
//					segment2 = _segment3;
//					if (i == 4) {
//						bijection[0] = false;
//						index = 5;
//					}
//					else {
//						bijection[0] = true;
//						index = 4;
//					}
//				}
//			}
//		}
//		if (index < 4) {
//			segment3 = _segment3;
//			minDist = (points[index] - points[4]).GetLength();
//			dist = (points[index] - points[5]).GetLength();
//			if (minDist < dist) {
//				bijection[index] = false;
//				bijection[1] = true;
//				bijection[5] = true;
//				if (index == 2) {
//					bijection[4] = false;
//				}
//				else {
//					bijection[4] = true;
//				}
//			}
//			else {
//				bijection[index] = true;
//				bijection[1] = false;
//				bijection[4] = true;
//				if (index == 2) {
//					bijection[5] = false;
//				}
//				else {
//					bijection[5] = true;
//				}
//			}
//		}
//		else {
//			segment3 = _segment2;
//			minDist = (points[index] - points[2]).GetLength();
//			dist = (points[index] - points[3]).GetLength();
//			if (minDist < dist) {
//				bijection[index] = false;
//				bijection[1] = true;
//				bijection[3] = true;
//				if (index == 4) {
//					bijection[2] = false;
//				}
//				else {
//					bijection[2] = true;
//				}
//			}
//			else {
//				bijection[index] = true;
//				bijection[1] = false;
//				bijection[2] = true;
//				if (index == 4) {
//					bijection[3] = false;
//				}
//				else {
//					bijection[3] = true;
//				}
//			}
//		}
//		
//	}
//	~Triangle() {}
//	double error() {
//		double sumError = 0;
//		if (bijection[0]) {
//			sumError += DistanceBetweenPoints::errorSt(segment1->GetPoint1_pos(), segment2->GetPoint2_pos(), 0);
//			if (bijection[1]) {
//				sumError += DistanceBetweenPoints::errorSt(segment1->GetPoint2_pos(), segment3->GetPoint2_pos(), 0);
//				sumError += DistanceBetweenPoints::errorSt(segment2->GetPoint1_pos(), segment3->GetPoint1_pos(), 0);
//			}
//			else {
//				sumError += DistanceBetweenPoints::errorSt(segment1->GetPoint2_pos(), segment3->GetPoint1_pos(), 0);
//				sumError += DistanceBetweenPoints::errorSt(segment2->GetPoint1_pos(), segment3->GetPoint2_pos(), 0);
//			}
//		}
//		else {
//			sumError += DistanceBetweenPoints::errorSt(segment1->GetPoint1_pos(), segment2->GetPoint1_pos(), 0);
//			if (bijection[1]) {
//				sumError += DistanceBetweenPoints::errorSt(segment1->GetPoint2_pos(), segment3->GetPoint2_pos(), 0);
//				sumError += DistanceBetweenPoints::errorSt(segment2->GetPoint2_pos(), segment3->GetPoint1_pos(), 0);
//			}
//			else {
//				sumError += DistanceBetweenPoints::errorSt(segment1->GetPoint2_pos(), segment3->GetPoint1_pos(), 0);
//				sumError += DistanceBetweenPoints::errorSt(segment2->GetPoint2_pos(), segment3->GetPoint2_pos(), 0);
//			}
//		}
//		return sumError / 3;
//	}
//
//	Array<double> gradient() { return Array<double>(); }
//private:
//	Segment* segment1;
//	Segment* segment2;
//	Segment* segment3;
//	bool bijection[6];
//};

// carefully delete
//class �orrectTriangle : public Requirement
//{
//public:
//	�orrectTriangle(Segment* _segment1, Segment* _segment2, Segment* _segment3, double _size) :
//		Requirement(IDGenerator::getInstance()->generateID())
//	{
//		size = _segment1->GetLength() + _segment2->GetLength() + _segment2->GetLength();
//
//
//
//		Vector2 points[6];
//		points[0] = _segment1->GetPoint1_pos();
//		points[1] = _segment1->GetPoint2_pos();
//		points[2] = _segment1->GetPoint1_pos();
//		points[3] = _segment1->GetPoint2_pos();
//		points[4] = _segment1->GetPoint1_pos();
//		points[5] = _segment1->GetPoint2_pos();
//		Vector2 temp;
//		double minDist = 0;
//		double dist = 0;
//		segment1 = _segment1;
//		minDist = (points[0] - points[2]).GetLength();
//		segment2 = _segment2;
//		bijection[0] = false;
//		bijection[2] = false;
//		int i = 3;
//		int index = i;
//		for (i; i < 6; ++i) {
//			bijection[i] = false;
//			dist = (points[0] - points[i]).GetLength();
//			if (dist < minDist) {
//				minDist = dist;
//				if (i == 3) {
//					bijection[0] = true;
//
//					index = 2;
//				}
//				else {
//					segment2 = _segment3;
//					if (i == 4) {
//						bijection[0] = false;
//						index = 5;
//					}
//					else {
//						bijection[0] = true;
//						index = 4;
//					}
//				}
//			}
//		}
//		if (index < 4) {
//			segment3 = _segment3;
//			minDist = (points[index] - points[4]).GetLength();
//			dist = (points[index] - points[5]).GetLength();
//			if (minDist < dist) {
//				bijection[index] = false;
//				bijection[1] = true;
//				bijection[5] = true;
//				if (index == 2) {
//					bijection[4] = false;
//				}
//				else {
//					bijection[4] = true;
//				}
//			}
//			else {
//				bijection[index] = true;
//				bijection[1] = false;
//				bijection[4] = true;
//				if (index == 2) {
//					bijection[5] = false;
//				}
//				else {
//					bijection[5] = true;
//				}
//			}
//		}
//		else {
//			segment3 = _segment2;
//			minDist = (points[index] - points[2]).GetLength();
//			dist = (points[index] - points[3]).GetLength();
//			if (minDist < dist) {
//				bijection[index] = false;
//				bijection[1] = true;
//				bijection[3] = true;
//				if (index == 4) {
//					bijection[2] = false;
//				}
//				else {
//					bijection[2] = true;
//				}
//			}
//			else {
//				bijection[index] = true;
//				bijection[1] = false;
//				bijection[2] = true;
//				if (index == 4) {
//					bijection[3] = false;
//				}
//				else {
//					bijection[3] = true;
//				}
//			}
//		}
//
//	}
//	~�orrectTriangle() {}
//	double error() {
//		double sumError = 0;
//		if (bijection[0]) {
//			sumError += DistanceBetweenPoints::errorSt(segment1->GetPoint1_pos(), segment2->GetPoint2_pos(), 0);
//			if (bijection[1]) {
//				sumError += DistanceBetweenPoints::errorSt(segment1->GetPoint2_pos(), segment3->GetPoint2_pos(), 0);
//				sumError += DistanceBetweenPoints::errorSt(segment2->GetPoint1_pos(), segment3->GetPoint1_pos(), 0);
//			}
//			else {
//				sumError += DistanceBetweenPoints::errorSt(segment1->GetPoint2_pos(), segment3->GetPoint1_pos(), 0);
//				sumError += DistanceBetweenPoints::errorSt(segment2->GetPoint1_pos(), segment3->GetPoint2_pos(), 0);
//			}
//		}
//		else {
//			sumError += DistanceBetweenPoints::errorSt(segment1->GetPoint1_pos(), segment2->GetPoint1_pos(), 0);
//			if (bijection[1]) {
//				sumError += DistanceBetweenPoints::errorSt(segment1->GetPoint2_pos(), segment3->GetPoint2_pos(), 0);
//				sumError += DistanceBetweenPoints::errorSt(segment2->GetPoint2_pos(), segment3->GetPoint1_pos(), 0);
//			}
//			else {
//				sumError += DistanceBetweenPoints::errorSt(segment1->GetPoint2_pos(), segment3->GetPoint1_pos(), 0);
//				sumError += DistanceBetweenPoints::errorSt(segment2->GetPoint2_pos(), segment3->GetPoint2_pos(), 0);
//			}
//		}
//		sumError += DistanceBetweenPoints::errorSt(segment1->GetPoint1_pos(), segment1->GetPoint2_pos(), size);
//		sumError += DistanceBetweenPoints::errorSt(segment2->GetPoint1_pos(), segment3->GetPoint2_pos(), size);
//		sumError += DistanceBetweenPoints::errorSt(segment3->GetPoint1_pos(), segment2->GetPoint2_pos(), size);
//		return sumError / 6;
//	}
//	void ChangeSize(double _size) {
//		size = _size;
//	}
//
//	Array<double> gradient() { return Array<double>(); }
//private:
//	Segment* segment1;
//	Segment* segment2;
//	Segment* segment3;
//	double size;
//	bool bijection[6];
//};
//
//class NsAngle : public Requirement
//{
//public:
//	NsAngle(ListE<Segment*>& list) :
//		Requirement(IDGenerator::getInstance()->generateID())
//	{
//		count = count = list.GetSize();
//		segments = new Segment*[count];
//		Segment* temp;
//		Segment* minSegment;
//		Vector2 prev;
//		double minDist = 0;
//		double dist = 0;
//		int index = 0;
//		bijection = new bool[count];
//		list.MoveHead();
//		segments[index] = list.GetCurrent();
//		list.DeleteCurrent();
//		prev = segments[index]->GetPoint1_pos();
//		do
//		{
//			list.MoveHead();
//			temp = list.GetCurrent();
//			minSegment = temp;
//			minDist = (prev - temp->GetPoint1_pos()).GetLength();
//			dist = (prev - temp->GetPoint2_pos()).GetLength();
//			if (dist < minDist) {
//				minDist = dist;
//			}
//			list.CreateLabel();
//			while (list.MoveNext())
//			{
//				temp = list.GetCurrent();
//				dist = (prev - temp->GetPoint1_pos()).GetLength();
//				if (dist < minDist) {
//					minDist = dist;
//					minSegment = temp;
//					list.CreateLabel();
//				}
//				dist = (prev - temp->GetPoint2_pos()).GetLength();
//				if (dist < minDist) {
//					minDist = dist;
//					minSegment = temp;
//					list.CreateLabel();
//				}
//			}
//			dist = (prev - minSegment->GetPoint2_pos()).GetLength();
//			if (dist > minDist){
//				bijection[index] = false;
//				prev = minSegment->GetPoint2_pos();
//			}
//			else {
//				bijection[index] = true;
//				prev = minSegment->GetPoint1_pos();
//			}
//			list.DeleteLabel();
//			++index;
//			segments[index] = minSegment;
//		} while (list.GetSize() != 0);
//		bijection[index] = true;
//	}
//	~NsAngle() {}
//	double error() {
//		double sumError = 0;
//		Vector2 vec1;
//		Vector2 vec2;
//		for (int i = 1; i < count - 1; ++i) {
//			if (bijection[i] && bijection[i - 1]) {
//				vec1 = segments[i]->GetPoint1_pos();
//				vec2 = segments[i + 1]->GetPoint2_pos();
//				sumError += DistanceBetweenPoints::errorSt(vec1, vec2, 0);
//			}
//			if (bijection[i] && !bijection[i - 1]) {
//				vec1 = segments[i]->GetPoint2_pos();
//				vec2 = segments[i + 1]->GetPoint2_pos();
//				sumError += DistanceBetweenPoints::errorSt(vec1, vec2, 0);
//			}
//			if (!bijection[i] && bijection[i - 1]) {
//				vec1 = segments[i]->GetPoint1_pos();
//				vec2 = segments[i + 1]->GetPoint1_pos();
//				sumError += DistanceBetweenPoints::errorSt(vec1, vec2, 0);
//			}
//			if (!bijection[i] && !bijection[i - 1]) {
//				vec1 = segments[i]->GetPoint2_pos();
//				vec2 = segments[i + 1]->GetPoint1_pos();
//				sumError += DistanceBetweenPoints::errorSt(vec1, vec2, 0);
//			}
//		}
//		if (bijection[count - 2]) {
//			vec1 = segments[count - 1]->GetPoint1_pos();
//			vec2 = segments[0]->GetPoint2_pos();
//			sumError += DistanceBetweenPoints::errorSt(vec1, vec2, 0);
//		}
//		else {
//			vec1 = segments[count - 1]->GetPoint2_pos();
//			vec2 = segments[0]->GetPoint2_pos();
//			sumError += DistanceBetweenPoints::errorSt(vec1, vec2, 0);
//		}
//		if (bijection[0]) {
//			vec1 = segments[0]->GetPoint1_pos();
//			vec2 = segments[1]->GetPoint2_pos();
//			sumError += DistanceBetweenPoints::errorSt(vec1, vec2, 0);
//		}
//		else {
//			vec1 = segments[0]->GetPoint1_pos();
//			vec2 = segments[1]->GetPoint1_pos();
//			sumError += DistanceBetweenPoints::errorSt(vec1, vec2, 0);
//		}
//		return sumError / count;
//	}
//
//	Array<double> gradient() { return Array<double>(); }
//private:
//	Segment** segments;
//	bool* bijection;
//	int count;
//};
//
//class CorrectNsAngle : public Requirement
//{
//public:
//	CorrectNsAngle(ListE<Segment*>& list, double _size) :
//		Requirement(IDGenerator::getInstance()->generateID())
//	{
//		Segment* temp;
//		Segment* minSegment;
//		Vector2 prev;
//		count = list.GetSize();
//		list.MoveHead();
//		center.x = 0;
//		center.y = 0;
//		size = 0;
//		do
//		{
//			temp = list.GetCurrent();
//			center = center + temp->GetPoint1_pos();
//			center = center + temp->GetPoint2_pos();
//			size += temp->GetLength();
//		} while (list.MoveNext());
//		center = center / (double)(count * 2);
//		radius = size / (2 * sin(PI / count));
//
//		segments = new Segment*[count];
//		double minDist = 0;
//		double dist = 0;
//		int index = 0;
//		bijection = new bool[count];
//		list.MoveHead();
//		segments[index] = list.GetCurrent();
//		list.DeleteCurrent();
//		prev = segments[index]->GetPoint1_pos();
//		do
//		{
//			list.MoveHead();
//			temp = list.GetCurrent();
//			minSegment = temp;
//			minDist = (prev - temp->GetPoint1_pos()).GetLength();
//			dist = (prev - temp->GetPoint2_pos()).GetLength();
//			if (dist < minDist) {
//				minDist = dist;
//			}
//			list.CreateLabel();
//			while (list.MoveNext())
//			{
//				temp = list.GetCurrent();
//				dist = (prev - temp->GetPoint1_pos()).GetLength();
//				if (dist < minDist) {
//					minDist = dist;
//					minSegment = temp;
//					list.CreateLabel();
//				}
//				dist = (prev - temp->GetPoint2_pos()).GetLength();
//				if (dist < minDist) {
//					minDist = dist;
//					minSegment = temp;
//					list.CreateLabel();
//				}
//			}
//			dist = (prev - minSegment->GetPoint2_pos()).GetLength();
//			if (dist > minDist) {
//				bijection[index] = false;
//				prev = minSegment->GetPoint2_pos();
//			}
//			else {
//				bijection[index] = true;
//				prev = minSegment->GetPoint1_pos();
//			}
//			list.DeleteLabel();
//			++index;
//			segments[index] = minSegment;
//		} while (list.GetSize() != 0);
//		bijection[index] = true;
//	}
//	~CorrectNsAngle() {}
//	double error() {
//		/*center.x = 0;
//		center.y = 0;
//		for (int i = 0; i < count; ++i) {
//			center = center + segments[i]->GetPoint1_pos();
//			center = center + segments[i]->GetPoint2_pos();
//		}
//		center = center / (double)(count * 2);*/
//
//		double sumError = 0;
//		Vector2 vec1;
//		Vector2 vec2;
//		for (int i = 1; i < count - 1; ++i) {
//			if (bijection[i] && bijection[i - 1]) {
//				vec1 = segments[i]->GetPoint1_pos();
//				vec2 = segments[i + 1]->GetPoint2_pos();
//				sumError += DistanceBetweenPoints::errorSt(vec1, vec2, 0);
//			}
//			if (bijection[i] && !bijection[i - 1]) {
//				vec1 = segments[i]->GetPoint2_pos();
//				vec2 = segments[i + 1]->GetPoint2_pos();
//				sumError += DistanceBetweenPoints::errorSt(vec1, vec2, 0);
//			}
//			if (!bijection[i] && bijection[i - 1]) {
//				vec1 = segments[i]->GetPoint1_pos();
//				vec2 = segments[i + 1]->GetPoint1_pos();
//				sumError += DistanceBetweenPoints::errorSt(vec1, vec2, 0);
//			}
//			if (!bijection[i] && !bijection[i - 1]) {
//				vec1 = segments[i]->GetPoint2_pos();
//				vec2 = segments[i + 1]->GetPoint1_pos();
//				sumError += DistanceBetweenPoints::errorSt(vec1, vec2, 0);
//			}
//		}
//		if (bijection[count - 2]) {
//			vec1 = segments[count - 1]->GetPoint1_pos();
//			vec2 = segments[0]->GetPoint2_pos();
//			sumError += DistanceBetweenPoints::errorSt(vec1, vec2, 0);
//		}
//		else {
//			vec1 = segments[count - 1]->GetPoint2_pos();
//			vec2 = segments[0]->GetPoint2_pos();
//			sumError += DistanceBetweenPoints::errorSt(vec1, vec2, 0);
//		}
//		if (bijection[0]) {
//			vec1 = segments[0]->GetPoint1_pos();
//			vec2 = segments[1]->GetPoint2_pos();
//			sumError += DistanceBetweenPoints::errorSt(vec1, vec2, 0);
//		}
//		else {
//			vec1 = segments[0]->GetPoint1_pos();
//			vec2 = segments[1]->GetPoint1_pos();
//			sumError += DistanceBetweenPoints::errorSt(vec1, vec2, 0);
//		}
//		for (int i = 0; i < count; ++i) {
//			vec1 = segments[i]->GetPoint1_pos();
//			vec2 = segments[i]->GetPoint2_pos();
//			sumError += DistanceBetweenPoints::errorSt(vec1, vec2, size);
//			sumError += DistanceBetweenPoints::errorSt(vec2, center, radius);
//		}
//		return sumError / (count * 3);
//	}
//
//	Array<double> gradient() { return Array<double>(); }
//private:
//	Segment * * segments;
//	bool* bijection;
//	int count;
//	double size;
//	double radius;
//	Vector2 center;
//};

#endif // REQUIREMENT_H