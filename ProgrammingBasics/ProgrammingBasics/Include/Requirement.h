#ifndef REQUIREMENT_H
#define REQUIREMENT_H
#define PI 3.141592653589793 
#include "Model.h"

class IRequirement{
public :
	virtual double error() = 0;
};

class RequirementDistanceBetweenPoints : public IRequirement
{
public:
	RequirementDistanceBetweenPoints(Point& _point1, Point& _point2, double dist) :
	point1(_point1), point2(_point2)
	{
		distance = dist;
	}
	~RequirementDistanceBetweenPoints() {}
	virtual double error() {
		//Model model;
		//if (!model.dict.find(first)) {
		//	// требование должно быть удалено, процесс удаления еще не сделан
		//}
		//Point* point1 = dynamic_cast<Point*>(model.dict.GetCurrent());
		//if (!model.dict.find(second)) {
		//	// требование должно быть удалено, процесс удаления еще не сделан
		//}
		return abs(point1.GetDistance(point2.GetPosition()) - distance);
	}
	void ChangeDistance(double dist) {
		distance = dist;
	}
private:
	double distance;
	Point& point1;
	Point& point2;
};

class RequirementPointsOnTheOneHand : public IRequirement
{
public:
	RequirementPointsOnTheOneHand( Segment& _segment, Point& _point1, Point& _point2, int dist) :
		segment(_segment),
		point1(_point1),
		point2(_point2)
	{}
	~RequirementPointsOnTheOneHand() {}
	virtual double error() {

		double Fx1 = segment.Inequality(point1.GetPosition());
		double Fx2 = segment.Inequality(point2.GetPosition());
		if ((Fx1 > 0 && Fx2 < 0) || (Fx1 < 0 && Fx2 > 0)) {
			Fx1 = abs(Fx1);
			Fx2 = abs(Fx2);
			// выбрасываем меньшее
			if (Fx1 > Fx2) {
				return Fx2;
			}
			else{
				return Fx1;
			}
		}
		return 0;
	}
private:
	Segment& segment;
	Point& point1;
	Point& point2;
};

class RequirementDistanceBetweenPointSegment : public IRequirement
{
public:
	RequirementDistanceBetweenPointSegment(Segment& _segment, Point& _point, double dist) :
		segment(_segment),
		point(_point)
	{
		distance = dist;
	}
	~RequirementDistanceBetweenPointSegment() {}
	virtual double error() {
		return abs(segment.GetDistance(point.GetPosition()) - distance);
	}
	void ChangeDistance(double dist) {
		distance = dist;
	}
private:
	Segment& segment;
	Point& point;
	double distance;
};

class RequirementAngleBtweenSegments : public IRequirement
{
public:
	RequirementAngleBtweenSegments(Segment& _seg1, Segment& _seg2, double ang) :
		segment1(_seg1),
		segment2(_seg2)
	{
		angle = ang;
	}
	~RequirementAngleBtweenSegments() {}
	virtual double error() {
		Vector2 vec1 = segment1.GetPoint2_pos() - segment1.GetPoint1_pos();
		Vector2 vec2 = segment2.GetPoint2_pos() - segment2.GetPoint1_pos();
		double answer = Vector2::Dot(vec1, vec2);
		double PI_d2 = PI / 2;
		if (answer > PI_d2) {
			answer = PI_d2 * 2 - answer;
		}
		// умножение нужно потому что для большого угла разность будет слишком малой
		return abs(answer - angle) * PI_d2;
	}
	void ChangeAngle(double ang) {
		angle = ang;
	}
private:
	 Segment& segment1;
	 Segment& segment2;
	double angle;
};

class RequirementDistanceBetweenPointArc : public IRequirement
{
public:
	RequirementDistanceBetweenPointArc( Arc& _arc, Point& _point, double dist) :
		arc(_arc),
		point(_point)
	{
		distance = dist;
	}
	~RequirementDistanceBetweenPointArc() {}
	virtual double error() {
		
		Vector2 center = arc.GetCenter();
		return abs(point.GetDistance(center) - distance);
	}
	void ChangeDistance(double dist) {
		distance = dist;
	}
private:
	Arc& arc;
	Point& point;
	double distance;
};

class RequirementPointInArc : public IRequirement
{
public:
	RequirementPointInArc(Arc& _arc,  Point& _point) :
		arc(_arc),
		point(_point)
	{}
	~RequirementPointInArc() {}
	virtual double error() {
		Vector2 center = arc.GetCenter();
		return abs(point.GetDistance(center));
	}
private:
	Arc& arc;
	Point& point;
};
#endif // REQUIREMENT_H
