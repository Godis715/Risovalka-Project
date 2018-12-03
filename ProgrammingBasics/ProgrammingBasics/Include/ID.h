#ifndef __ID
#define __ID

#include <iostream>
#include "Array.h"
#include "Logger.h"

#define POINT_PRMS 2
#define SEGMENT_PRMS 0
#define ARC_PRMS 1
#define CIRCLE_PRMS 1

#define POINT_CHLD 0
#define SEGMENT_CHLD 2
#define ARC_CHLD 2
#define CIRCLE_CHLD 1
//#define CURVE_CHLD not value!

enum object_type {
	ot_point,
	ot_segment,
	ot_arc,
	ot_circle,
	ot_curve,

	ot_connection,
	ot_distBetPoints,
	ot_equalSegmentLen,
	ot_equalPointPosReq,
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
	ID* generateID() const;
	ID* generateID(unsigned long long) const;
	static ID GetNullID();

	static bool IsNullID(const ID&);
private:
	IDGenerator() { }
	static IDGenerator* _instance;

	static unsigned long long _lastGivenHash;
};

class Object {
protected:
	friend class ObjectController;
	ID* id;
	object_type type;

	Array<double> params;
	Array<ID> children;

	bool isValid;
public:
	Object(object_type, const Array<double>&, const Array<ID>&);
	Object(object_type, const Array<double>&, const Array<ID>&, unsigned long long);
	virtual ~Object();

	object_type GetType() const;
	ID GetID() const;
	Array<double> GetParams() const;
	Array<ID> GetChildren() const;

	void SetParams(const Array<double>&);

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
	void SetObjParam(const ID&, const Array<double>&);
	Array<double> GetObjParam(const ID&);
	Array<ID> GetObjChildren(const ID&);
	bool IsValid(const ID&);
	void MakeInValid(ID&);
	void MakeValid(ID&);
};

class ID {
private:
	unsigned long long hash;
	Object* object;

	friend class Object;
	friend class ObjectController;
	friend class IDGenerator;

	ID(unsigned long long);
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


template<typename T, typename ...Args> Array<T> CreateArr(const T& val, const Args& ... args) {
	int numargs = sizeof...(args) + 1;
	Array<T> arr(numargs);
	arr[0] = val;
	int i = 1;
	for (auto&& p : std::initializer_list<T>{ args... })
	{
		arr[i] = p;
		++i;
	}
	return arr;
}

#endif