#ifndef REQUIREMENT_H
#define REQUIREMENT_H
#include "Primitives.h"

// find exact values and place in project
#define OPTIM_EPS 1e-3
#define OPTIM_GRAD_EPS 1e-3
#define DELTA_X 1e-6

class Requirement {
private:
	const ID id;
	const object_type type;
protected:
	Array<double*> arguments;
	Array<double> params;
public:
	Requirement(const ID _id, object_type _type) : id(_id), type(_type) {

		int argNum;
		int paramNum;

		switch (type) {
		case ot_distBetPoints: {
			argNum = 4;
			paramNum = 1;
			break;
		}
		case ot_equalSegmentLen: {
			argNum = 8;
			paramNum = 0;
			break;
		}
		case ot_connection: {
			argNum = 0;
			paramNum = 0;
			break;
		}
		case ot_pointPosReq: {
			argNum = 2;
			paramNum = 2;
			break;
		}
		case ot_pointsOnTheOneHand: {
			argNum = 8;
			paramNum = 0;
			break;
		}
		case ot_distBetPointSeg: {
			argNum = 6;
			paramNum = 1;
			break;
		}
		case ot_angleBetSeg: {
			argNum = 8;
			paramNum = 1;
			break;
		}
		case ot_distBetPointArc: {
			argNum = 7;
			paramNum = 1;
			break;
		}
		case ot_pointInArc: {
			argNum = 7;
			paramNum = 0;
			break;
		}
		default: {
			throw std::exception("Couldn't create requirement. Invalid requirement type");
		}
		}

		arguments = Array<double*>(argNum);
		params = Array<double>(paramNum);
	}
	virtual double error() = 0;
	virtual void Change(const double);
	virtual void ChangeParams(const Array<double>& newParams) {
		if (newParams.GetSize() != params.GetSize()) {
			throw std::exception("Invalid requirement parameters!");
		}
		params = newParams;
	}
	Array<double> Gradient();
	ID GetID() const;
	Array<double*> GetParams();
	object_type GetType() const;
};

class DistBetPointsReq : public Requirement
{
private:
	Point* point1;
	Point* point2;
public:
	DistBetPointsReq(Point* _point1, Point* _point2, double _distance) :
		Requirement(IDGenerator::getInstance()->generateID(), ot_distBetPoints)
	{
		arguments = Array<double*>(4);
		params = Array<double>(1);
		Vector2* pos1 = &_point1->position;
		Vector2* pos2 = &_point2->position;
		
		arguments[0] = &pos1->x;
		arguments[1] = &pos1->y;
		arguments[2] = &pos2->x;
		arguments[3] = &pos2->y;

		params[0] = _distance;
	}
	~DistBetPointsReq() { }

	double error() {
		Vector2 vectorAB(*(arguments[2]) - *(arguments[0]), *(arguments[3]) - *(arguments[1]));
		double modAB_inSquare = Vector2::Dot(vectorAB, vectorAB);
		return modAB_inSquare - params[0] * (2 * sqrt(modAB_inSquare) - params[0]);
	}
};

class EqualSegmentLenReq : public Requirement {
private:
public:
	EqualSegmentLenReq(Segment* _seg1, Segment* _seg2) :
		Requirement(IDGenerator::getInstance()->generateID(), ot_equalSegmentLen)
	{
		arguments = Array<double*>(8);
		params = Array<double>(0);
		arguments[0] = (&_seg1->point1->position.x);
		arguments[1] = (&_seg1->point1->position.y);
		arguments[2] = (&_seg1->point2->position.x);
		arguments[3] = (&_seg1->point2->position.y);
		arguments[4] = (&_seg2->point1->position.x);
		arguments[5] = (&_seg2->point1->position.y);
		arguments[6] = (&_seg2->point2->position.x);
		arguments[7] = (&_seg2->point2->position.y);
	}
	~EqualSegmentLenReq() { }
	double error() {
		Vector2 vec1(*(arguments[3]) - *(arguments[1]), *(arguments[2]) - *(arguments[0]));
		Vector2 vec2(*(arguments[7]) - *(arguments[5]), *(arguments[6]) - *(arguments[4]));

		double divergence = vec2.GetLength() - vec1.GetLength();
		return divergence * divergence;


		params = Array<double>(0);
	}
};

class ConnectionReq : public Requirement {

private:
public:
	ConnectionReq() :
		Requirement(IDGenerator::getInstance()->generateID(), ot_connection)
	{
		arguments = Array<double*>(0);
		params = Array<double>(0);
	}
	~ConnectionReq() { }
	double error() {
		return 0;
	}
};

class PointPosReq : public Requirement {
private:

public:
	PointPosReq(Point* _point, double _x, double _y) :
		Requirement(IDGenerator::getInstance()->generateID(), ot_pointPosReq) {
		arguments = Array<double*>(2);
		params = Array<double>(2);
		arguments[0] = &_point->position.x;
		arguments[1] = &_point->position.y;

		params[0] = _x;
		params[1] = _y;
	}
	PointPosReq(Point* _point, const Vector2& _vec) :
		Requirement(IDGenerator::getInstance()->generateID(), ot_pointPosReq) {
		arguments[0] = &_point->position.x;
		arguments[1] = &_point->position.y;

		params[0] = _vec.x;
		params[1] = _vec.y;
	}

	double error() {
		Vector2 vector(*arguments[0] - params[0], *arguments[1] - params[1]);
		return Vector2::Dot(vector, vector);
	}
};

class PointsOnTheOneHand : public Requirement
{
public:
	PointsOnTheOneHand(Segment* _segment, Point* _point1, Point* _point2) :
		segment(_segment),
		point1(_point1),
		point2(_point2),
		Requirement(IDGenerator::getInstance()->generateID(), ot_pointsOnTheOneHand)
	{
		arguments = Array<double*>(8);
		params = Array<double>(0);

		arguments[0] = &_segment->point1->position.x;
		arguments[1] = &_segment->point1->position.y;
		arguments[2] = &_segment->point2->position.x;
		arguments[3] = &_segment->point2->position.y;
		arguments[4] = &_point1->position.x;
		arguments[5] = &_point1->position.y;
		arguments[6] = &_point2->position.x;
		arguments[7] = &_point2->position.y;
	}
	~PointsOnTheOneHand() {}
	double error() {
		double Fx1 = segment->Inequality(point1->GetPosition());
		double Fx2 = segment->Inequality(point2->GetPosition());
		if ((Fx1 > 0 && Fx2 < 0) || (Fx1 < 0 && Fx2 > 0)) {
			Fx1 = abs(Fx1);
			Fx2 = abs(Fx2);

			if (Fx1 > Fx2) {
				double distance = segment->GetDistance(point2->position);
				return distance * distance;
			}
			else{
				double distance = segment->GetDistance(point1->position);
				return distance * distance;
			}
		}
		return 0;
	}
private:
	Segment* segment;
	Point* point1;
	Point* point2;
};

class DistanceBetweenPointSegment : public Requirement
{
public:
	DistanceBetweenPointSegment(Segment* _segment, Point* _point, double _distance) :
		segment(_segment),
		point(_point),
		Requirement(IDGenerator::getInstance()->generateID(), ot_distBetPointSeg)
	{
		arguments = Array<double*>(6);
		params = Array<double>(1);

		arguments[0] = &_segment->point1->position.x;
		arguments[1] = &_segment->point1->position.y;
		arguments[2] = &_segment->point2->position.x;
		arguments[3] = &_segment->point2->position.y;
		arguments[4] = &_point->position.x;
		arguments[5] = &_point->position.y;

		params[0] = _distance;
	}
	~DistanceBetweenPointSegment() {}
	double error() {
		double distance = segment->GetDistance(point->GetPosition()) - params[0];
		return distance * distance;
	}

	Array<double> gradient() { return Array<double>(); }
private:
	Segment* segment;
	Point* point;
};

class AngleBetweenSegments : public Requirement
{
public:
	AngleBetweenSegments(Segment* _segment1, Segment* _segment2, double _andle) :
		segment1(_segment1),
		segment2(_segment2),
		Requirement(IDGenerator::getInstance()->generateID(), ot_angleBetSeg)
	{
		arguments = Array<double*>(8);
		params = Array<double>(1);

		arguments[0] = &_segment1->point1->position.x;
		arguments[1] = &_segment1->point1->position.y;
		arguments[2] = &_segment1->point2->position.x;
		arguments[3] = &_segment1->point2->position.y;
		arguments[4] = &_segment2->point1->position.x;
		arguments[5] = &_segment2->point1->position.y;
		arguments[6] = &_segment2->point2->position.x;
		arguments[7] = &_segment2->point2->position.y;

		params[0] = abs(cos((_andle / 180) * PI));
		sinus = sin((_andle / 180) * PI);
	}
	~AngleBetweenSegments() {}
	double error() {
		Vector2 vec1(*arguments[2] - *arguments[0], *arguments[3] - *arguments[1]);
		Vector2 vec2(*arguments[6] - *arguments[4], *arguments[7] - *arguments[5]);
		
		double length1 = vec1.GetLength();
		double length2 = vec2.GetLength();

		// smaller side triangle:
		Vector2 vec3 = vec1 - vec2;
		if (Vector2::Dot(vec3, vec3) > length1 * length1 + length2 * length2 + DELTA_X) {
			vec3 = (vec1 * -1) - vec2;
		}
		//
		double length3 = sqrt(length1 * length1 + length2 * length2 - 2 * params[0] * length2* length1);

		double different = length3 - vec3.GetLength();
		return different * different;
	}

	void ChangeParams(const Array<double>& newParams) {
		if (newParams.GetSize() != 1) {
			throw std::exception("Invalid new param argement");
		}
		params[0] = abs(cos((newParams[0] / 180) * PI));
		sinus = sin((newParams[0] / 180) * PI);
	}
private:
	double sinus;
	Segment* segment1;
	Segment* segment2;
};

class DistanceBetweenPointArc : public Requirement
{
public:
	DistanceBetweenPointArc(Arc* _arc, Point* _point, double _distance) :
		arc(_arc),
		point(_point),
		Requirement(IDGenerator::getInstance()->generateID(), ot_distBetPointArc)
	{
		arguments = Array<double*>(7);
		params = Array<double>(1);

		arguments[0] = &_arc->point1->position.x;
		arguments[1] = &_arc->point1->position.y;
		arguments[2] = &_arc->point2->position.x;
		arguments[3] = &_arc->point2->position.y;
		arguments[4] = &_arc->angle;
		arguments[5] = &_point->position.x;
		arguments[6] = &_point->position.y;

		params[0] = _distance;
	}
	~DistanceBetweenPointArc() {}
	double error() {
		Vector2 vector(point->position - arc->GetCenter());
		double modVector_inSquare = Vector2::Dot(vector, vector);
		return modVector_inSquare - params[0] * (2 * sqrt(modVector_inSquare) - params[0]);
	}
private:
	Arc* arc;
	Point* point;
}; 

//class SegmentTouchCircle : public Requirement {
//public:
//	SegmentTouchCircle(Circle* _circle, Segment* _segment) :
//		circle(_circle),
//		segment(_segment),
//		Requirement(IDGenerator::getInstance()->generateID(), ot_distBetPointArc)
//	{
//		arguments = Array<double*>(7);
//		params = Array<double>(0);
//
//		arguments[0] = &_circle->center->position.x;
//		arguments[1] = &_circle->center->position.y;
//		arguments[2] = &_circle->radius;
//		arguments[3] = &_segment->point1->position.x;
//		arguments[4] = &_segment->point1->position.y;
//		arguments[5] = &_segment->point2->position.x;
//		arguments[6] = &_segment->point2->position.y;
//	}
//	~SegmentTouchCircle() {}
//
//	double error() {
//		
//	}
//
//private:
//	Circle * circle;
//	Segment* segment;
//};

// needed to fix

class PointInArc : public Requirement
{
public:
	PointInArc(Arc* _arc, Point* _point) :
		arc(_arc),
		point(_point),
		Requirement(IDGenerator::getInstance()->generateID(), ot_pointInArc)
	{
		arguments[0] = &_arc->point1->position.x;
		arguments[1] = &_arc->point1->position.y;
		arguments[2] = &_arc->point2->position.x;
		arguments[3] = &_arc->point2->position.y;
		arguments[4] = &_arc->angle;
		arguments[5] = &_point->position.x;
		arguments[6] = &_point->position.y;
	}
	~PointInArc() {}
	// return distance to arc and angle
	double error() {
		Vector2 center = arc->GetCenter();
		Vector2 vec1 = arc->GetPoint1_pos() - center;
		Vector2 vecPoint = point->GetPosition() - center;
		double angle = Vector2::Angle(vec1, vecPoint);
		double angleArc = arc->GetAngle();
		if (angle <= angleArc) {
			return 0;
		}
		if (angle <= PI + angleArc / 2) {
			if (angle < angleArc + PI / 2) {
				return point->GetDistance(center) * sin(angle - angleArc);
			}
			else {
				return point->GetDistance(center) + angle;
			}
		}
		else {
			if (angle < PI / 2) {
				return point->GetDistance(center) * sin(angle);
			}
			else {
				return point->GetDistance(center);
			}
		}
	}
private:
	Arc* arc;
	Point* point;
};

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