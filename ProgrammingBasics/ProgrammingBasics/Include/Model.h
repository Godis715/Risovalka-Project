#ifndef __MODEL
#define __MODEL

#include "Data.h"

// ID
// IDGenerator
// Library //
// INumerable
// Queue
// Dequeue
// List
// Array
// Dictionary
// Pair-Tree
// Set
// Hash-Table
// Type
// Vector2
// Primitives
// Requirement
// Logger
// Data
// Model


class Model
{
private:
	class Link
	{
	public:
		ID primID;
		ID reqID;
		Link(const ID&, const ID&);
		Link(){}
		~Link(){}
	};

	Dict<ID, Primitive*> dataPrim;

	Dict<ID, Requirement*> dataReq;
	
	Dict<ID, List<ID>*> dataLink;

	IDGenerator* idGen;

	Data data;


	void GetIDRequirementsInComponent(const ID&, Array<ID>&);

	void FindRequirementsByID(Array<ID>&, Array<Requirement*>&);

	//may be not using
	bool find(const ID&, Array<ID>);

	bool find(const ID&, Array<Primitive*>&);

	bool find(const ID&, Array<Requirement*>&);
	//..

	//similar functions!!
	double GetError();
	double GetError(const Array<Requirement*>&) const;
	//

	double ErrorByAlpha(const Array<Requirement*>&, const Array<double*>&, const Array<double>&, double);
	void OptimizeByGradient(const Array<Requirement*>&, const Array<double*>&, const Array<double>&);

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

	// Create destructor
	~Model();

	bool DischargeInfoObjects(Array<infoObject>&);
	bool createObject(type_id, Array<double>&, ID&);
	
	//carefully delete
	//bool createSegment(ID&, ID&, ID&);
	bool CreateRequirementByID(const Requirement_id, Array<ID>&, Array<double>&);
	bool CreateRequirement(const Requirement_id, Array<Primitive*>&, Array<double>&);

	//rewrite!!!!!!!
	bool getNearest(double, double, ID&, double&);


	bool getObjType(const ID&, type_id&);

	//replace with GET CHILD 
	bool GetSegmentPoints(ID, Array<ID>&);
	bool GetArcPoints(ID, Array<ID>&);


	bool getObjParam(const ID&, Array<double>&);
	
	// temp!!
	// int Optimize1();
	// end temp

	void OptimizeRequirements(const Array<Requirement*>&);
	// void PrintSystemRequirement();

	//temp function
	void OptimizeAllRequirements();

	// XXX Function

	bool XXXCreateObject(const type_id, Array<double>&, ID&);

	bool XXXCreateRequirementByID(const Requirement_id, Array<int>&, Array<ID>&, Array<double>&);

	bool XXXCreateRequirement(const Requirement_id, Array<int>&, Array<Primitive*>&, Array<double>&);

	void XXXGetRequirementsByID(int, const ID&, Array<Requirement*>&);

	void XXXGetRequirementsIDByID(int, const ID&, Array<ID>&);

	void XXXGetRequirementsType(int, const ID&, Array<Requirement_id>&);

	void XXXDeleteRequirement(int, const ID&);

	void XXXDeletePrimitive(int, const ID&);

};
#endif