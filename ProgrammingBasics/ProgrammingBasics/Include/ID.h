#ifndef __ID
#define __ID

#include <iostream>
#include "Array.h"
#include "Logger.h"

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
	ot_segmentTouchCircle,

	ot_angleBetSeg,
	ot_pointInArc,
	ot_triangle,
	ot_correctTriangle,
	ot_nsAngle,
	ot_correctNsAngle
};

class ID;
class Object;
class DataController;

class IDGenerator
{
public:
	static IDGenerator* getInstance();
	ID* generateID(Object*);
	ID* generateID(Object*, unsigned long long);
private:
	IDGenerator() { }
	static IDGenerator* _instance;

	static unsigned long long _lastGivenHash;
};

class Object {
protected:
	ID* id;
	object_type type;

	Array<double> params;
public:
	Object(object_type, const Array<double>&);
	Object(object_type, const Array<double>&, unsigned long long);
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
	void DeleteObj(ID&) const;
};

class ID {
private:
	unsigned long long hash;
	Object* object;

	friend class ObjectController;
	friend class IDGenerator;

	ID(unsigned long long, Object*);

public:
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