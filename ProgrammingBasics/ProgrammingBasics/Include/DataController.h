#ifndef __DATACONTROLLER
#define __DATACONTROLLER

#include "Dictionary.h"
#include "List.h"
#include "Requirement.h"

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