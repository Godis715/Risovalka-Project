#ifndef REQUIREMENT_H
#define REQUIREMENT_H
#define PI 3.141592653589793 

class IRequirement{
public :
	virtual double error() = 0;
};

class RequirementDistanceBetweenPoints : public IRequirement
{
public:
	RequirementDistanceBetweenPoints(Point& _point1, Point& _point2, double _distance) :
	point1(_point1), point2(_point2)
	{
		distance = _distance;
	}
	~RequirementDistanceBetweenPoints() {}
	double error() {
		return abs(point1.GetDistance(point2.GetPosition()) - distance);
	}
	void ChangeDistance(double _distance) {
		distance = _distance;
	}
private:
	double distance;
	Point& point1;
	Point& point2;
};

class RequirementPointsOnTheOneHand : public IRequirement
{
public:
	RequirementPointsOnTheOneHand( Segment& _segment, Point& _point1, Point& _point2) :
		segment(_segment),
		point1(_point1),
		point2(_point2)
	{}
	~RequirementPointsOnTheOneHand() {}
	double error() {

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
	RequirementDistanceBetweenPointSegment(Segment& _segment, Point& _point, double _distance) :
		segment(_segment),
		point(_point)
	{
		distance = _distance;
	}
	~RequirementDistanceBetweenPointSegment() {}
	double error() {
		return abs(segment.GetDistance(point.GetPosition()) - distance);
	}
	void ChangeDistance(double _distance) {
		distance = _distance;
	}
private:
	Segment& segment;
	Point& point;
	double distance;
};

class RequirementAngleBtweenSegments : public IRequirement
{
public:
	RequirementAngleBtweenSegments(Segment& _segment1, Segment& _segment2, double _andle) :
		segment1(_segment1),
		segment2(_segment2)
	{
		angle = _andle;
	}
	~RequirementAngleBtweenSegments() {}
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
	double error() {
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
private:
	Arc& arc;
	Point& point;
};
#endif // REQUIREMENT_H
