#ifndef REQUIREMENT_H
#define REQUIREMENT_H
#include "Model.h"

class IRequirement{
public :
	virtual double error() = 0;
};

class RequirementDistanceBetweenPoints : public IRequirement
{
public:
	RequirementDistanceBetweenPoints(const Point& point1, const Point& point2, double dist) :
	first(point1.GetId()), second(point1.GetId())
	{
		distance = dist;
	}
	~RequirementDistanceBetweenPoints() {}
	virtual double error() {
		Model model;
		if (!model.dict.find(first)) {
			// требование должно быть удалено, процесс удаления еще не сделан
		}
		Point* point1 = dynamic_cast<Point*>(model.dict.GetCurrent());
		if (!model.dict.find(second)) {
			// требование должно быть удалено, процесс удаления еще не сделан
		}
		Point* point2 = dynamic_cast<Point*>(model.dict.GetCurrent());
		return abs(point1->GetDistance(point2->GetPosition()) - distance);
	}
	void ChangeDistance(double dist) {
		distance = dist;
	}
private:
	double distance;
	const ID& first;
	const ID& second;
};

class RequirementPointsOnTheOneHand : public IRequirement
{
public:
	RequirementPointsOnTheOneHand(const Segment& segment, const Point& point1, const Point& point2, int dist) :
		segment(segment.GetId()),
		first(point1.GetId()),
		second(point1.GetId())
	{}
	~RequirementPointsOnTheOneHand() {}
	virtual double error() {
		Model model;
		if (!model.dict.find(first)) {
			// требование должно быть удалено, процесс удаления еще не сделан
		}
		Point* point1 = dynamic_cast<Point*>(model.dict.GetCurrent());
		if (!model.dict.find(second)) {
			// требование должно быть удалено, процесс удаления еще не сделан
		}
		Point* point2 = dynamic_cast<Point*>(model.dict.GetCurrent());
		if (!model.dict.find(segment)) {
			// требование должно быть удалено, процесс удаления еще не сделан
		}
		Segment* seg = dynamic_cast<Segment*>(model.dict.GetCurrent());
		double Fx1 = seg->Inequality(point1->GetPosition());
		double Fx2 = seg->Inequality(point2->GetPosition());
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
	const ID& segment;
	const ID& first;
	const ID& second;
};

class RequirementDistanceBetweenPointSegment : public IRequirement
{
public:
	RequirementDistanceBetweenPointSegment(const Segment& segment, const Point& point, double dist) :
		segment(segment.GetId()),
		first(point.GetId())
	{
		distance = dist;
	}
	~RequirementDistanceBetweenPointSegment() {}
	virtual double error() {
		Model model;
		if (!model.dict.find(first)) {
			// требование должно быть удалено, процесс удаления еще не сделан
		}
		Point* point = dynamic_cast<Point*>(model.dict.GetCurrent());
		if (!model.dict.find(segment)) {
			// требование должно быть удалено, процесс удаления еще не сделан
		}
		Segment* seg = dynamic_cast<Segment*>(model.dict.GetCurrent());
		return abs(seg->GetDistance(point->GetPosition()) - distance);
	}
	void ChangeDistance(double dist) {
		distance = dist;
	}
private:
	const ID& segment;
	const ID& first;
	double distance;
};

class RequirementAngleBtweenSegments : public IRequirement
{
public:
	RequirementAngleBtweenSegments(const Segment& seg1, const Segment& seg2, double ang) :
		segment1(seg1.GetId()),
		segment2(seg2.GetId())
	{
		angle = ang;
	}
	~RequirementAngleBtweenSegments() {}
	virtual double error() {
		Model model;
		if (!model.dict.find(segment1)) {
			// требование должно быть удалено, процесс удаления еще не сделан
		}
		Segment* seg1 = dynamic_cast<Segment*>(model.dict.GetCurrent());
		if (!model.dict.find(segment2)) {
			// требование должно быть удалено, процесс удаления еще не сделан
		}
		Segment* seg2 = dynamic_cast<Segment*>(model.dict.GetCurrent());
		Vector2 vec1 = seg1->GetPoint2_pos() - seg1->GetPoint1_pos();
		Vector2 vec2 = seg2->GetPoint2_pos() - seg2->GetPoint1_pos();
		double answer = Vector2::Dot(vec1, vec2);
		double PI_d2 = 3.14159265 / 2;
		if (answer > PI_d2) {
			answer = PI_d2 * 2 - answer;
		}
		// умножение нужно потому что для большого угла разность будет слишком малой
		return abs(answer - angle) * PI_d2 / 2;
	}
	void ChangeAngle(double ang) {
		angle = ang;
	}
private:
	const ID& segment1;
	const ID& segment2;
	double angle;
};
<<<<<<< HEAD

class RequirementDistanceBetweenPointArc : public IRequirement
{
public:
	RequirementDistanceBetweenPointArc(const Arc& ar, const Point& point, double dist) :
		arc(ar.GetId()),
		first(point.GetId())
	{
		distance = dist;
	}
	~RequirementDistanceBetweenPointArc() {}
	virtual double error() {
		Model model;
		if (!model.dict.find(first)) {
			// требование должно быть удалено, процесс удаления еще не сделан
		}
		Point* point = dynamic_cast<Point*>(model.dict.GetCurrent());
		if (!model.dict.find(arc)) {
			// требование должно быть удалено, процесс удаления еще не сделан
		}
		Arc* arcL = dynamic_cast<Arc*>(model.dict.GetCurrent());
		Vector2 center = arcL->GetCenter();
		return abs(point->GetDistance(center) - distance);
	}
	void ChangeDistance(double dist) {
		distance = dist;
	}
private:
	const ID& arc;
	const ID& first;
	double distance;
};

class RequirementPointInArc : public IRequirement
{
public:
	RequirementPointInArc(const Arc& ar, const Point& point) :
		arc(ar.GetId()),
		first(point.GetId())
	{}
	~RequirementPointInArc() {}
	virtual double error() {
		Model model;
		if (!model.dict.find(first)) {
			// требование должно быть удалено, процесс удаления еще не сделан
		}
		Point* point = dynamic_cast<Point*>(model.dict.GetCurrent());
		if (!model.dict.find(arc)) {
			// требование должно быть удалено, процесс удаления еще не сделан
		}
		Arc* arcL = dynamic_cast<Arc*>(model.dict.GetCurrent());
		Vector2 center = arcL->GetCenter();
		return abs(point->GetDistance(center));
	}
private:
	const ID& arc;
	const ID& first;
};
=======
>>>>>>> Evg-Branch
#endif // REQUIREMENT_H
