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

class ID;

class IDGenerator
{
public:
	static IDGenerator* getInstance();
	ID* generateID();
private:
	IDGenerator() { }
	static IDGenerator* _instance;

	static unsigned long long _lastGivenHash;
};

class Object {
protected:
	ID* id;
	object_type type;
public:
	Object(object_type);
	~Object();
	object_type GetType() const;
	ID GetID() const;
};

class ObjectController {
private:
	ObjectController();
	static ObjectController* instance;
public:
	static ObjectController* GetInstance();

	Object* GetObject(const ID&) const;
	object_type GetType(const ID&) const;
};

class ID {
private:
	unsigned long long hash;
	Object* object;

	friend class ObjectController;
public:
	ID(unsigned long long);
	ID(const ID&);
	ID();
	~ID();
	void operator=(const ID&);
	bool operator== (const ID&) const;
	bool operator< (const ID&) const;
	bool operator> (const ID&) const;
	unsigned long long GetHash() const;
};

std::ostream& operator<<(std::ostream&, const ID&);


#endif