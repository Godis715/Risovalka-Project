#ifndef __UNDO_REDO
#define __UNDO_REDO

#include "Requirement.h"
#include "Primitives.h"
#include "DataController.h"

enum TypeOFCange {
	tfc_creation,
	tfc_before_creation_req,
	tfc_after_creation_req,
	tfc_delete,
	tfc_before_change,
	tfc_after_change
};


class Version {
public:
	const TypeOFCange type;
	Version(const TypeOFCange);
};

class VersionChange : public Version {
public:
	typedef Array<std::pair<ID, Array<double>>> Data;
	Data data;

	~VersionChange();
	VersionChange(const TypeOFCange, Data&);
};

class VersionCreateReq : public Version {
public:
	typedef Array<std::pair<ID, const Array<double>>> Data;
	Data version;
	const ID idReq;

	~VersionCreateReq();
	VersionCreateReq(const TypeOFCange, const ID&, Data&);
};


class VersionCreat_Del : public Version {
public:
	typedef Array<std::pair<ID, const BinSearchTree<ID, ID>*>> Data;

	Data version;
	~VersionCreat_Del();
	VersionCreat_Del(const TypeOFCange, Data&);
private:
	void DeleteCreation();
	void DeleteDelete();
};

class Undo_Redo
{
public:
	static Undo_Redo* GetInstance();

	void AddVersion(const TypeOFCange, const Array<ID>&);

	void AddVersion(const TypeOFCange);
private:
	int index;

	void AddChange(const Array<ID>&);

	void CompleteAddChange();

	void AddCreatingReq(const Array<ID>&);

	void CompleteAddCreatingReq();

	static Undo_Redo* instance;

	List<Version*> versions;

	Undo_Redo();

	void DeleteLastVersion();
};

#endif