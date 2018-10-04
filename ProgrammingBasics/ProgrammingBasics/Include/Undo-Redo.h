#ifndef __UNDO_REDO
#define __UNDO_REDO

#include "Requirement.h"
#include "Primitives.h"
#include "DataController.h"

enum TypeOFCange {
	tfc_creation,
	tfc_delete,
	tfc_change
};


class Version {
public:
	const TypeOFCange type;
	Version(const TypeOFCange);
};

class VersionChange : public Version {
public:
	typedef Array<std::pair<ID, const Array<double>>> Data;
	Data version;
	~VersionChange();
	VersionChange(const TypeOFCange, Data&);
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
private:
	int index;

	void AddChange(const Array<ID>&);

	static Undo_Redo* instance;

	List<Version*> versions;

	Undo_Redo();

	void DeleteLastVersion();
};

#endif