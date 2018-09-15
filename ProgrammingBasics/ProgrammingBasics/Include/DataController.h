#ifndef __DATACONTROLLER
#define __DATACONTROLLER

#include "Requirement.h"
#include "Dictionary.h"
#include "List.h"

class DataController {
private:
	static DataController* instance;
	DataController();

	typedef BinSearchTree<ID, ID> DataID;
	typedef BinSearchTree<ID, BinSearchTree<ID, ID>* > DataLink;
	
	DataID primData;
	DataID reqData;
	DataLink dataLink;

	PrimController* primCtrl;
	ReqController* reqCtrl;

	BinSearchTree<ID, ID> currentComponent;

public:
	DataController* GetInstance();

	void AddObject(const ID&);
	void Connect(const ID&, const Array<ID>&);
	void DeleteObject(const ID&);
	Array<ID> GetComponent(const ID&) const;
};

#endif