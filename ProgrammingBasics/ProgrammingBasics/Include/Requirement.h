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
		Vector2 pointVec1 = point1->GetPosition();
		Vector2 pointVec2 = point2->GetPosition();
		pointVec1 = pointVec1 - pointVec2;
		return abs(pointVec1.GetLength() - distance);
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
#endif // REQUIREMENT_H
