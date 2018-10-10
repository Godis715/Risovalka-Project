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

	Array<ID> objects;
	
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
	EqualSegmentLenReq(const Array<ID>& _objects, const Array<double>& _params);

	double error();
};

class PointPosReq : public Requirement {
private:

public:
	PointPosReq(const Array<ID>&, const Array<double>&);

	double error();
};

class PointsOnTheOneHand : public Requirement
{
public:
	PointsOnTheOneHand(const Array<ID>&, const Array<double>&);

	double error();
};

class DistanceBetweenPointSegment : public Requirement
{
public:
	// _objects = <segment, point>
	DistanceBetweenPointSegment(const Array<ID>&, const Array<double>&);

	double error();

	Array<double> gradient();
};

class AngleBetweenSegments : public Requirement
{
public:
	AngleBetweenSegments(const Array<ID>&, const Array<double>&);

	double error();

	void ChangeParams();
private:
	double cosinus;
	double sinus;
	double angle;
};

class DistanceBetweenPointArc : public Requirement
{
public:
	DistanceBetweenPointArc(const Array<ID>&, const Array<double>&);

	double error();
}; 

class SegmentTouchCircle : public Requirement {
public:
	SegmentTouchCircle(const Array<ID>&, const Array<double>&);

	double error();
};

// needed to fix

class PointInArc : public Requirement
{
public:
	PointInArc(const Array<ID>&, const Array<double>&);

	// return distance to arc and angle
	double error();
};

#endif // REQUIREMENT_H