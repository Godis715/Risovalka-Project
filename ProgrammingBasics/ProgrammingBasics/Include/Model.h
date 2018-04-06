#include "HyperGraph.h"

#ifndef __MODEL
#define __MODEL

class Primitive;

class Model
{
private:

	double EPS = 1e-6;
	Dict<ID, Primitive*> data; //or another container
	Array<IRequirement*> dataReq;
	IDGenerator* idGen;
	double GetError();
	double GetError(Array<IRequirement*>&);
	double ErrorByAlpha(Array<IRequirement*>&, Parameters<double*>, Parameters<double>, double);

	void OptimizeByGradient(Array<IRequirement*>&, Parameters<double*>, Parameters<double>);

public:
	class infoObject
	{
	public:
		infoObject(){}
		void operator=(infoObject input)
		{
			this->params = input.params;
			this->type = input.type;
		}
		Array<double> params;
		type_id type;
	};
	Model() { }
	void DischargeInfoObjects(Array<infoObject>&);
	bool createObject(type_id, Array<double>&, ID&);
	bool createSegment(ID&, ID&, ID&);
	bool createRequirement(const Requirement_id, Array<ID>&, Array<double>&);
	bool getNearest(double, double, ID&, double&);
	bool getObjType(const ID&, type_id&);
	bool GetSegmentPoints(ID, Array<ID>&);
	bool GetArcPoints(ID, Array<ID>&);
	bool getObjParam(const ID&, Array<double>&);
	int Optimize1();
	void OptimizeRequirements(Array<IRequirement*>&);
	void PrintSystemRequirement();

	//temp function
	void OptimizeAllRequirements();
};

#endif