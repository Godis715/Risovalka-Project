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
	const Requirement_id type;
protected:
	Array<double*> params;
public:
	Requirement(ID _id, int _size) : id(_id), params(Array<double*>(_size)) { 
		
	}
	virtual double error() = 0;
	Array<double> gradient();
	ID GetID() const;
	Array<double*> GetParams();
	Requirement_id GetType() const;
};

class DistBetPointsReq : public Requirement
{
private:
	double distance;
public:
	DistBetPointsReq(Point* _point1, Point* _point2, double _distance) :
		Requirement(IDGenerator::getInstance()->generateID(), 4)
	{
		Vector2* pos1 = &_point1->position;
		Vector2* pos2 = &_point2->position;
		
		params = Array<double*>(4);

		params[0] = &pos1->x;
		params[1] = &pos1->y;
		params[2] = &pos2->x;
		params[3] = &pos2->y;

		distance = _distance;
	}
	~DistBetPointsReq() { }
	//static double errorSt(Vector2 vec1, Vector2 vec2, double dist) {
	//	return abs((vec1 - vec2).GetLength() - dist);
	//}
	double error() {
		Vector2 vectorAB(*(params[2]) - *(params[0]), *(params[3]) - *(params[1]));
		double modAB_inSquare = Vector2::Dot(vectorAB, vectorAB);
		return modAB_inSquare - distance * (2 * sqrt(modAB_inSquare) - distance);
	}
	void SetDistance(double _distance) {
		distance = _distance;
	}
};

class EqualSegmentLenReq : public Requirement {
private:
	Segment * seg1;
	Segment* seg2;
public:
	EqualSegmentLenReq(Segment& _seg1, Segment& _seg2) :
		Requirement(IDGenerator::getInstance()->generateID(), 8)
	{
		seg1 = &_seg1;
		seg2 = &_seg2;

		params[0] = (&seg1->point1->position.x);
		params[1] = (&seg1->point1->position.y);
		params[2] = (&seg1->point2->position.x);
		params[3] = (&seg1->point2->position.y);
		params[4] = (&seg2->point1->position.x);
		params[5] = (&seg2->point1->position.y);
		params[6] = (&seg2->point2->position.x);
		params[7] = (&seg2->point2->position.y);
	}
	~EqualSegmentLenReq() { }
	double error() {
		Vector2 vec1(*(params[3]) - *(params[1]), *(params[2]) - *(params[0]));
		Vector2 vec2(*(params[7]) - *(params[5]), *(params[6]) - *(params[4]));

		double divergence = vec2.GetLength() - vec1.GetLength();
		return divergence * divergence;
	}
};



class PointsOnTheOneHand : public Requirement
{
public:
	PointsOnTheOneHand(Segment& _segment, Point& _point1, Point& _point2) :
		segment(_segment),
		point1(_point1),
		point2(_point2),
		Requirement(IDGenerator::getInstance()->generateID(), 0) {}
	~PointsOnTheOneHand() {}
	double error() {

		double Fx1 = segment.Inequality(point1.GetPosition());
		double Fx2 = segment.Inequality(point2.GetPosition());
		if ((Fx1 > 0 && Fx2 < 0) || (Fx1 < 0 && Fx2 > 0)) {
			Fx1 = abs(Fx1);
			Fx2 = abs(Fx2);

			if (Fx1 > Fx2) {
				return Fx2;
			}
			else{
				return Fx1;
			}
		}
		return 0;
	}


	Array<double> gradient() { return Array<double>(); }

	void Print() {
		Vector2 vec1 = segment.GetPoint1_pos();
		Vector2 vec2 = segment.GetPoint2_pos();
	}
private:
	Segment& segment;
	Point& point1;
	Point& point2;
};

class DistanceBetweenPointSegment : public Requirement
{
public:
	DistanceBetweenPointSegment(Segment& _segment, Point& _point, double _distance) :
		segment(_segment),
		point(_point),
		Requirement(IDGenerator::getInstance()->generateID(), 0)
	{
		distance = _distance;
	}
	~DistanceBetweenPointSegment() {}
	double error() {
		return abs(segment.GetDistance(point.GetPosition()) - distance);
	}
	void ChangeDistance(double _distance) {
		distance = _distance;
	}

	Array<double> gradient() { return Array<double>(); }
private:
	Segment& segment;
	Point& point;
	double distance;
};

class AngleBetweenSegments : public Requirement
{
public:
	AngleBetweenSegments(Segment& _segment1, Segment& _segment2, double _andle) :
		segment1(_segment1),
		segment2(_segment2),
		Requirement(IDGenerator::getInstance()->generateID(), 0)
	{
		angle = _andle;
	}
	~AngleBetweenSegments() {}
	double error() {
		Vector2 vec1 = segment1.GetPoint2_pos() - segment1.GetPoint1_pos();
		Vector2 vec2 = segment2.GetPoint2_pos() - segment2.GetPoint1_pos();
		double angleReal = asin(Vector2::Cross(vec1, vec2) / (vec1.GetLength() * vec2.GetLength()));
		angleReal = abs(angleReal);
		return abs(angleReal - angle);
	}
	void ChangeAngle(double _andle) {
		angle = _andle;
	}

	Array<double> gradient() { return Array<double>(); }
private:
	Segment& segment1;
	Segment& segment2;
	double angle;
};

class DistanceBetweenPointArc : public Requirement
{
public:
	DistanceBetweenPointArc(Arc& _arc, Point& _point, double dist) :
		arc(_arc),
		point(_point),
		Requirement(IDGenerator::getInstance()->generateID(), 0)
	{
		distance = dist;
	}
	~DistanceBetweenPointArc() {}
	double error() {
		Vector2 center = arc.GetCenter();
		return abs(point.GetDistance(center) - distance);
	}
	void ChangeDistance(double dist) {
		distance = dist;
	}
	void Print() {}

	Array<double> gradient() { return Array<double>(); }

private:
	Arc& arc;
	Point& point;
	double distance;
}; 

class PointInArc : public Requirement
{
public:
	PointInArc(Arc& _arc,  Point& _point) :
		arc(_arc),
		point(_point),
		Requirement(IDGenerator::getInstance()->generateID(), 0) {}
	~PointInArc() {}
	// return distance to arc and angle
	double error() {
		Vector2 center = arc.GetCenter();
		Vector2 vec1 = arc.GetPoint1_pos() - center;
		Vector2 vec2 = point.GetPosition() - center;
		double angle = Vector2::Angle(vec1, vec2);
		double angleArc = arc.GetAngle();
		if (angle <= angleArc) {
			return 0;
		}
		if (angle <= PI + angleArc / 2) {
			if (angle < angleArc + PI / 2) {
				return point.GetDistance(center) * sin(angle - angleArc) + angle;
			}
			else {
				return point.GetDistance(center) + angle;
			}
		}
		else {
			if (angle < PI / 2) {
				return point.GetDistance(center) * sin(angle) + angle;
			}
			else {
				return point.GetDistance(center) + angle;
			}
		}
	}

	Array<double> gradient() { return Array<double>(); }

	void Print() {}
private:
	Arc& arc;
	Point& point;
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
//class ÑorrectTriangle : public Requirement
//{
//public:
//	ÑorrectTriangle(Segment* _segment1, Segment* _segment2, Segment* _segment3, double _size) :
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
//	~ÑorrectTriangle() {}
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
