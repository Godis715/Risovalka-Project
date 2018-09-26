#ifndef __DATACONTROLLER
#define __DATACONTROLLER

#include "Dictionary.h"
#include "List.h"
#include "Requirement.h"

class DataController;
class Model;

class SVGformat {
private:

	class SVGObject {
	private:
	public:

		// (<children>, <params>)
		SVGObject(object_type, int, int);

		object_type type;
		unsigned long long hash;
		Array<unsigned long long> children;
		Array<double> params;
	};

	typedef BinSearchTree<unsigned long long, SVGObject> ObjectMap;
	typedef BinSearchTree<unsigned long long, ID> IDMap;

	ObjectMap objMap;

	std::string ScanAttribute(std::ifstream&);
	Array<double> ScanParams(std::ifstream&);
	bool ParsePointTag(std::ifstream&);
	bool ParseSegmentTag(std::ifstream&);
	bool ParseCircleTag(std::ifstream&);
	bool ParseArcTag(std::ifstream&);
	bool ParseRequirementTag(std::ifstream&, object_type);

	bool IsContains(IDMap&, unsigned long long);

	void AddObject(const SVGObject&);
	void ApplyDownloadData();

	PrimController* primCtrl;
	ReqController* reqCtrl;
	DataController* dataCtrl;
	ObjectController* objCtrl;

public:
	SVGformat();
	~SVGformat();
	bool Download(const std::string&);
	bool Save(const std::string&, bool);
};

typedef BinSearchTree<ID, ID> Component;

class DataController {
private:
	static DataController* instance;
	DataController();

	typedef BinSearchTree<ID, ID> DataID;
	typedef BinSearchTree<ID, BinSearchTree<ID, ID>* > DataLink;
	typedef BinSearchTree<string, ID> DataName;

	DataID primData;
	DataID reqData;
	DataLink linkData;
	DataName nameData;

	PrimController* primCtrl;
	ReqController* reqCtrl;
	ObjectController* objCtrl;

	BinSearchTree<ID, ID>* currentComponent;

	friend class SVGformat;

public:
	static DataController* GetInstance();

	void AddObject(const ID&);
	void Connect(const ID&, const Array<ID>&);
	void DeleteObject(const ID&);

	ID GetObjectInCircle(double, double, double);

	Component GetComponent(const ID&);

	bool IsUniqueName(const string&) const;
};

#endif