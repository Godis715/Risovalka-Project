#ifndef __UNDO_REDO
#define __UNDO_REDO

#include "Requirement.h"
#include "Primitives.h"
#include "DataController.h"

enum TypeOFCange {
	tfc_creation,
	tfc_creation_req,
	tfc_delete,
	tfc_change
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
	Array<ID> IDs;
	Array<Array<double>> dataBefore;
	Array<Array<double>> dataAfter;

	~VersionChange();
	VersionChange(const TypeOFCange, const Array<ID>&);

	void Undo();
	void Redo();
};

class VersionCreateReq : public Version {
public:
	const Array<ID> IDs;
	Array<Array<double>> dataBefore;
	Array<Array<double>> dataAfter;
	ID idReq;
	const BinSearchTree<ID, ID>* link;

	void Undo();
	void Redo();

	~VersionCreateReq();
	VersionCreateReq(const TypeOFCange, const Array<ID>&);
};

class VersionCreat_Del : public Version {
public:
	typedef Array<std::pair<ID, const BinSearchTree<ID, ID>*>> Data;

	Data data;
	~VersionCreat_Del();
	VersionCreat_Del(const TypeOFCange, Data&);

	void Undo();
	void Redo();
};

class Undo_Redo
{
public:
	static Undo_Redo* GetInstance();

	void AddVersion(const TypeOFCange, const Array<ID>&);

	void CompleteAddChange();

	void CompleteAddCreatingReq(const ID&);

	void Undo();

	void Redo();
private:
	List<Version*>::Marker it;

	void AddChange(const Array<ID>&);

	void AddCreatingReq(const Array<ID>&);

	static Undo_Redo* instance;

	List<Version*> versions;

	Undo_Redo();

	void DeleteLastVersion();

	void DeleteVersionAfterIt();
};

#endif