#include "Array.h"
#include "Primitives.h"
#include "Dictionary.h"
#include "Requirement.h"


#ifndef __MODEL
#define __MODEL

class Primitive;

class Model
{
private:
	const double EPS = 1e-6;
	Dict<ID, Primitive*> data; //or another container
	Array<IRequirement*> dataReq;
	IDGenerator* idGen;
	double GetError();
public:
	Model() {}
	bool createObject(type_id, Array<double>&, ID&);
	bool createRequirement(const Requirement_id, Array<ID>&, Array<double>&);
	bool getNearest(double, double, ID&);
	bool getObjType(const ID&, type_id&) const;
	bool GetSegmentPoints(ID, Array<ID>&) const; //sssssssssssssssssssss
	bool GetArcPoints(ID, Array<ID>&) const;
	//Array<double> getObjSubs(ID); //?????
	bool getObjParam(const ID&, Array<double>&) const;
	void Optimize();
};

#endif