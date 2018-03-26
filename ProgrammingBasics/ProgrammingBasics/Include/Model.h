#include "Array.h"
#include "Primitives.h"

#ifndef __MODEL
#define __MODEL

class Primitive;

class Model
{
private:
	Array<Primitive*> data; //or another container
	IDGenerator* idGen;
public:
	Model() {}
	ID createObject(Type, Array<double>);
	bool getNearest(double, double, ID&);
	bool getObjType(ID, Type&);
	//Array<double> getObjSubs(ID); //?????
	bool getObjParam(ID, Array<double>&);
};

#endif