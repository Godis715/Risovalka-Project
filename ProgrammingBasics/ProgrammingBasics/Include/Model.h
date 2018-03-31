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
	Dict<ID, Primitive*> data; //or another container
	Array<IRequirement*> dataReq;
	IDGenerator* idGen;
	void Optimize();
public:
	Model() {}
	bool createObject(type_id, Array<double>&, ID&);
	bool createRequirement(const Requirement_id, Array<ID>&, Array<double>&);
	bool getNearest(double, double, ID&);
	bool getObjType(const ID&, type_id&);
	//Array<double> getObjSubs(ID); //?????
	bool getObjParam(const ID&, Array<double>&);
};

#endif