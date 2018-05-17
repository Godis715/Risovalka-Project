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
// Type
// Vector2
// Primitives
// Requirement
// Logger
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


	bool GetRequirements(const Array<ID>&, Array<Requirement*>&);

	bool GetPrimitives(const Array<ID>&, Array<Primitive*>&);
	
	bool GetRequirementsFromComponent(BinSearchTree<ID, ID>&, Array<Requirement*>&);

	bool GetPrimitivesFromComponent(BinSearchTree<ID, ID>&, Array<Primitive*>&);

	void ConnectPrimitives(const Array<Primitive*>&);

	bool CreateRequirement(object_type, Array<Primitive*>&, const Array<double>&, ID&);

	bool OptimizeGroup(Array<Primitive*>&);

	double GetError(const Array<Requirement*>&) const;

	double ErrorByAlpha(const Array<Requirement*>&, const Array<double*>&, const Array<double>&, double);
	void OptimizeByGradient(const Array<Requirement*>&, const Array<double*>&, const Array<double>&);

	void LockPoint(Point* point, ID&);

	/*version 2*/
	void OptitmizeNewton(const ID&);

	void GetDoublesForOptimize(Array<Primitive*>&, Array<double*>&);

	void GetDifferential(const Array<Requirement*>&, Array<double*>&, Array<double>&);

	void GetPointsFromPrimitives(Array<Primitive*>&, BinSearchTree<ID, Point*>&);
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

	bool NewComponent(const ID&, Array<ID>&, Array<ID>&);

	bool DischargeInfoObjects(Array<infoObject>&);

	bool CreateObject(object_type, const Array<double>&, ID&);
	
	bool CreateRequirementByID(object_type, const Array<ID>&, const Array<double>&, ID&);

	void CreateLink(const ID&, const Array<Primitive*>&);

	bool DeletePrimitive(const ID&);

	bool DeleteRequirement(const ID&);

	bool GetObject(double, double, Array<ID>&, Array<object_type>&, Array<double>&);

	bool GetObjType(const ID&, object_type&);

	bool ImposeRequirement(object_type, const Array<ID>&);

	bool GetObjParam(const ID&, Array<double>&);
	
	bool OptimizeRequirements(const Array<Requirement*>&);

	bool OptimizeByID(const ID&);
	// new functon

	void ChangeRequirement(const ID&, const double);

	bool Scale(const Array<ID>&, const double);

	bool Move(const Array<ID>&, const Vector2&);
};
#endif