#ifndef __TYPE
#define __TYPE

#include <string>

enum type_id { point = 1, segment, arc };

class Type {
private:
	std::string name;
	type_id id;
public:
	Type(type_id);
	std::string GetName() const;
	type_id GetTypeId() const;
};

enum Requirement_id {
	distBetPoints = 1,
	pointsOnTheOneHand,
	distBetPointSeg,
	angleBetSeg,
	distBetPointArc,
	pointInArc
};

class TypeRequirement {
private:
	std::string name;
	Requirement_id id;
public:
	TypeRequirement(Requirement_id);
	std::string GetName() const;
	Requirement_id GetRequirementId() const;
};

#endif
