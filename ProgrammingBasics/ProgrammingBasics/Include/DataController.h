#ifndef __DATACONTROLLER
#define __DATACONTROLLER

#include "ID.h"
#include "Dictionary.h"
#include "List.h"

class DataController {
private:
	static DataController* instance;
	DataController();

	typedef BinSearchTree<ID, ID> DataID;
	typedef BinSearchTree<ID, List<ID> > DataLink;
	
	DataID primData;
	DataID reqData;
	DataLink dataLink;

public:
	DataController* GetInstance();

	void AddPrimitive(const ID&);
	void AddRequirement(const ID&);
	void Connect(const ID&, const Array<ID>&);
	void DeleteObject(const ID&);
	Array<ID> GetComponent(const ID&) const;
};

#endif