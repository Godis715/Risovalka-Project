#ifndef __DATACONTROLLER
#define __DATACONTROLLER

#include "Dictionary.h"
#include "List.h"
#include "Requirement.h"

class DataController;
class Model;

class SVGformat {
private:
	std::string ScanAttribute(std::ifstream&);
	Array<double> ScanParams(std::ifstream&);
	bool ParsePointTag(std::ifstream&);
	bool ParseSegmentTag(std::ifstream&);
	bool ParseCircleTag(std::ifstream&);
	bool ParseArcTag(std::ifstream&);
	bool ParseRequirementTag(std::ifstream&, object_type);

	BinSearchTree<unsigned long long, ID> idMap;
public:
	SVGformat();
	~SVGformat();
	bool Download(const std::string&);
	bool Save(const std::string&);
};

typedef BinSearchTree<ID, ID> Component;

class DataController {
private:
	static DataController* instance;
	DataController();

	typedef BinSearchTree<ID, ID> DataID;
	typedef BinSearchTree<ID, BinSearchTree<ID, ID>* > DataLink;
	typedef BinSearchTree<string, bool> DataName;

	DataID primData;
	DataID reqData;
	DataLink linkData;
	DataName nameData;

	PrimController* primCtrl;
	ReqController* reqCtrl;
	ObjectController* objCtrl;

	BinSearchTree<ID, ID>* currentComponent;

public:
	DataController* GetInstance();

	void AddObject(const ID&);
	void Connect(const ID&, const Array<ID>&);
	void DeleteObject(const ID&);
	Component GetComponent(const ID&);

	bool IsUniqueName(const string&) const;
};

#endif