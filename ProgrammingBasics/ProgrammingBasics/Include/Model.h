#ifndef __MODEL
#define __MODEL

#include "Copmilator.h"

// ID
// IDGenerator
// Library //
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
// Compilator
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

	bool pointInArea(double, double, double, double, double, double);

	bool CreateObjByID(object_type, Array<ID>&, Array<double>&);

	class SVGformat
	{
	private:
		Model* model;
		std::string ScanAttribute(std::ifstream&);
		Array<double> ScanParams(std::ifstream&);
		bool ParsePointTag(std::ifstream&);
		bool ParseSegmentTag(std::ifstream&);
		bool ParseCircleTag(std::ifstream&);
		bool ParseArcTag(std::ifstream&);
		bool ParseRequirementTag(std::ifstream&, object_type);
	public:
		SVGformat();
		SVGformat(Model*);
		~SVGformat();
		bool Download(const std::string);
		bool Save(const std::string);

	};
	SVGformat* workingWithReester;

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

	void Clear();

	bool GetObject(double, double, Array<ID>&, Array<object_type>&, Array<double>&);

	//test
	bool GetObjectsOnArea(double, double, double, double, Array<ID>&, Array<object_type>&);

	bool GetObjType(const ID&, object_type&);

	// bool ImposeRequirement(object_type, const Array<ID>&);

	bool GetObjParam(const ID&, Array<double>&);
	
	bool OptimizeRequirements(const Array<Requirement*>&);

	bool OptimizeByID(const ID&);
	// new functon

	void ChangeRequirement(const ID&, const double);

	void ChangePrimitive(const ID&, Array<double>&);

	bool Scale(const Array<ID>&, const double);

	bool Move(const Array<ID>&, const Vector2&);

	bool SaveProject(const std::string);

	bool DownloadFile(const std::string);
};
#endif