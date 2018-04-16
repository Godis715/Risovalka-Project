#include "HyperGraph.h"

#ifndef __MODEL
#define __MODEL

class Primitive;

class Model
{
private:

	double EPS = 1e-12;
	Dict<ID, Primitive*> data; //or another container
	Array<IRequirement*> dataReq;
	IDGenerator* idGen;
	double GetError() const;
	double GetError(const Array<IRequirement*>&) const;
	double ErrorByAlpha(const Array<IRequirement*>&, const Array<double*>&, const Array<double>&, double);

	void OptimizeByGradient(const Array<IRequirement*>&, const Array<double*>&, const Array<double>&);

public:
	class infoObject
	{
	public:
		infoObject(){ }
		void operator=(const infoObject& input)
		{
			this->params = input.params;
			this->type = input.type;
		}
		Array<double> params;
		type_id type;
	};

	Model() { }
	bool DischargeInfoObjects(Array<infoObject>&);
	bool createObject(type_id, Array<double>&, ID&);
	bool createSegment(ID&, ID&, ID&);
	bool createRequirement(const Requirement_id, Array<ID>&, Array<double>&);
	bool getNearest(double, double, ID&);
	bool getObjType(const ID&, type_id&);
	bool GetSegmentPoints(ID, Array<ID>&);
	bool GetArcPoints(ID, Array<ID>&);
	bool getObjParam(const ID&, Array<double>&);
	int Optimize1();
	void OptimizeRequirements(const Array<IRequirement*>&);
	// void PrintSystemRequirement();

	//temp function
	void OptimizeAllRequirements();
};

#endif