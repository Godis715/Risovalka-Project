#ifndef __ID
#define __ID

#include <iostream>
#include "Array.h"

enum object_type {
	ot_point,
	ot_segment,
	ot_arc,
	ot_circle,

	ot_connection,
	ot_distBetPoints,
	ot_equalSegmentLen,
	ot_pointPosReq,
	ot_pointsOnTheOneHand,
	ot_distBetPointSeg,
	ot_distBetPointArc,

	ot_angleBetSeg,
	ot_pointInArc,
	ot_triangle,
	ot_correctTriangle,
	ot_nsAngle,
	ot_correctNsAngle
};

class ID {
private:
	unsigned long long hash;
public:
	ID(unsigned long long);
	ID();
	void operator=(const ID&);
	bool operator== (const ID&) const;
	bool operator< (const ID&) const;
	bool operator> (const ID&) const;
	unsigned long long GetHash() const;
};

std::ostream& operator<<(std::ostream&, const ID&);

class Requirement {
private:
	const ID id;
	const object_type type;
protected:
	Array<double*> arguments;
	Array<double> params;
public:
	Requirement(const ID _id, object_type _type);
	virtual double error() = 0;
	virtual void Change(const double);
	virtual void ChangeParams(const Array<double>& newParams);
	Array<double> Gradient();
	ID GetID() const;
	Array<double*> GetParams();
	object_type GetType() const;
};



#endif