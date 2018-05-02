#ifndef __TYPE
#define __TYPE

#include "Hash-Table.h"

enum prim_type {
	point_t = 1,
	segment_t,
	arc_t
};

//class Type {
//private:
//	std::string name;
//	type_id id;
//public:
//	Type(type_id);
//	std::string GetName() const;
//	type_id GetTypeId() const;
//};

enum req_type {
	distBetPoints = 1,
	equalSegmentLen,
	pointsOnTheOneHand,
	distBetPointSeg,
	angleBetSeg,
	distBetPointArc,
	pointInArc,
	triangle,
	correctTriangle,
	nsAngle,
	correctNsAngle
};

//class TypeRequirement {
//private:
//	std::string name;
//	Requirement_id id;
//public:
//	TypeRequirement(Requirement_id);
//	std::string GetName() const;
//	Requirement_id GetRequirementId() const;
//};

#endif
