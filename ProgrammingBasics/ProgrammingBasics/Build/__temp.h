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

// because ID contains pointers to objects

class IDGenerator
{
public:
	static IDGenerator* getInstance();
	ID generateID();
private:
	IDGenerator() { }
	static IDGenerator* _instance;

	static unsigned long long _lastGivenHash;
};

// base class of primitive and requirement
// initializies ID of the object
class Object {
protected:
	static IDGenerator* idGen;
	ID* objectID;
	object_type type;
public:
	Object();
	~Object();
	ID GetID() const {
		return *objectID;
	}
};

class Model {
private:
	void ChangeParam(ID&);
};

class ID {
private:
	friend void ChangeParam(ID&);
	unsigned long long hash;
	Object* object;

	friend
public:
	ID(unsigned long long);
	ID();
	~ID();
	void operator=(const ID&);
	bool operator== (const ID&) const;
	bool operator< (const ID&) const;
	bool operator> (const ID&) const;
	unsigned long long GetHash() const;
};

std::ostream& operator<<(std::ostream&, const ID&);

class Primitive : public Object {
private:
	const object_type type;

public:
	Primitive(ID, object_type);
	virtual double GetDistance(const Vector2&) const = 0;
	ID GetID() const;
	object_type GetType();
};

class Requirement : public Object {
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