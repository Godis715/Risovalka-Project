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

	virtual void Undo() = 0;
	virtual void Redo() = 0;

	virtual ~Version() = 0;
};

class VersionChange : public Version {
public:
	typedef Array<std::pair<ID, Array<double>>> Data;
	Data data;

	~VersionChange();
	VersionChange(const TypeOFCange, Data&);

	void Undo();
	void Redo();
};

class VersionCreateReq : public Version {
public:
	typedef Array<std::pair<ID, Array<double>>> Data;
	Data data;
	const ID idReq;

	void Undo();
	void Redo();

	~VersionCreateReq();
	VersionCreateReq(const TypeOFCange, const ID&, Data&);
};


class VersionCreat_Del : public Version {
public:
	typedef Array<std::pair<ID, const BinSearchTree<ID, ID>*>> Data;

	Data version;
	~VersionCreat_Del();
	VersionCreat_Del(const TypeOFCange, Data&);

	void Undo();
	void Redo();

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

	void AddCreatingReq(const ID&);

	void Undo();

	void Redo();
private:
	List<Version*>::Marker it;

	void AddChange(const Array<ID>&);

	void CompleteAddChange();

	void CompleteAddCreatingReq();

	static Undo_Redo* instance;

	List<Version*> versions;

	Undo_Redo();

	void DeleteLastVersion();
};

#endif