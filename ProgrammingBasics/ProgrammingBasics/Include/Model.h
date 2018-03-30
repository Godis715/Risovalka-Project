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
public:
	Model() {}
	ID createObject(Type, Array<double>);
	void createRequirement(const Requirement_id, Array<Primitive*>, Array<double>);
	bool getNearest(double, double, ID&);
	bool getObjType(ID, Type&);
	//Array<double> getObjSubs(ID); //?????
	bool getObjParam(ID, Array<double>&);
};

#endif