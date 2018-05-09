#ifndef __MODEL
#define __MODEL

#include "Logger.h"

// ID
// IDGenerator
// Library //
// INumerable
// Queue
// Dequeue
// List
// Array
// Dictionary
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

	DataPrim dataPrim;

	DataReq dataReq;

	DataLink dataLink;

	BinSearchTree<ID, ID>* currentComponent;

	bool GetRequirementsFromComponent(BinSearchTree<ID, ID>&, Array<Requirement*>&);

	bool GetPrimitiveFromComponent(BinSearchTree<ID, ID>&, Array<Primitive*>&);

	void ConnectPrimitives(Primitive*, Primitive*);

	bool CreateRequirement(object_type, Array<Primitive*>&, Array<double>&);


	double GetError(const Array<Requirement*>&) const;

	double ErrorByAlpha(const Array<Requirement*>&, const Array<double*>&, const Array<double>&, double);
	void OptimizeByGradient(const Array<Requirement*>&, const Array<double*>&, const Array<double>&);

	void OptitmizeNewton(const ID&);

	void GetDoublesForOptimize(Array<Primitive*>&, Array<double*>&);
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
		object_type type;
	};

	Model() { }

	// Create destructor
	~Model() { }

	bool DischargeInfoObjects(Array<infoObject>&);

	bool CreateObject(object_type, Array<double>&, ID&);
	
	bool CreateRequirementByID(object_type, Array<ID>&, Array<double>&);
	void CreateLink(const ID&, Array<Primitive*>&);

	bool DeletePrimitive(const ID&);
	bool DeleteRequirement(const ID&);


	bool GetObject(double, double, Array<ID>&, Array<double>&);

	bool GetObjType(const ID&, object_type&);

	bool ImposeRequirement(object_type, const Array<ID>&);

	// to private
	bool GetComponent(const ID&, BinSearchTree<ID, ID>&);

	bool GetObjParam(const ID&, Array<double>&);
	
	void OptimizeRequirements(const Array<Requirement*>&);

	void OptimizeByID(const ID&);

};
#endif