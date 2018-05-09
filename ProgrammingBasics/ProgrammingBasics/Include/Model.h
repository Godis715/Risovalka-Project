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

typedef BinSearchTree<ID, List<ID>*> DataLink;
typedef BinSearchTree<ID, Primitive*> DataPrim;
typedef BinSearchTree<ID, Requirement*> DataReq;

class Model
{
private:

	IDGenerator* idGen;

	// Evgeny' graph
	Data data; 


#ifdef MODEL_VERSION_LINK 
	//void GetIDRequirementsInComponent(const ID&, Array<ID>&);

	DataPrim dataPrim;

	DataReq dataReq;

	DataLink dataLink;

	BinSearchTree<ID, ID>* component;

	bool GetRequirementsFromComponent(BinSearchTree<ID, ID>&, Array<Requirement*>&);

	//void FindRequirementsByID(Array<ID>&, Array<Requirement*>&);

	void ConnectPrimitives(Primitive*, Primitive*);

	bool CreateRequirement(req_type, Array<Primitive*>&, Array<double>&);
#endif

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
		prim_type type;
	};

	Model() { }

	// Create destructor
	~Model() { }

	bool DischargeInfoObjects(Array<infoObject>&);

#ifdef MODEL_VERSION_LINK
	bool CreateObject(prim_type, Array<double>&, ID&);
	
	bool CreateRequirementByID(req_type, Array<ID>&, Array<double>&);
	void CreateLink(const ID&, Array<Primitive*>&);

	bool DeletePrimitive(const ID&);
	bool DeleteRequirement(const ID&);

#endif

	bool GetObject(double, double, Array<ID>&, Array<double>&);

	bool GetObjType(const ID&, prim_type&);

	// to private
	bool GetComponent(const ID&, BinSearchTree<ID, ID>&);

	bool GetObjParam(const ID&, Array<double>&);
	
	void OptimizeRequirements(const Array<Requirement*>&);

	// void PrintSystemRequirement();

	void OptimizeByID(const ID&);

	// XXX Function

#ifdef MODEL_VERSION_DATA
	bool XXXCreateObject(const prim_type, Array<double>&, ID&);

	void XXXConnectPrimitives(Primitive*, Primitive*, Primitive*);

	bool XXXCreateRequirementByID(const req_type, Array<int>&, Array<ID>&, Array<double>&);

	bool XXXCreateRequirement(const req_type, Array<int>&, Array<ID>&, Array<Primitive*>&, Array<double>&);

	void XXXGetRequirementsByID(int, const ID&, Array<Requirement*>&);

	void XXXGetRequirementsIDByID(int, const ID&, Array<ID>&);

	void XXXGetRequirementsType(int, const ID&, Array<req_type>&);

	void XXXDeleteRequirement(int, const ID&);

	void XXXDeletePrimitive(int, const ID&);
#endif
};
#endif