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
};

class VersionChange : Version {
public:
	Array<std::pair<ID, Array<double>>> version;
	~VersionChange();
	VersionChange();
};


class VersionCre_tDet : Version {
public:
	Array<std::pair<ID, BinSearchTree<ID, ID>>> version;
	~VersionCre_tDet();
	VersionCre_tDet();
private:
	void deleteCreation();
	void deleteDelete();
};


class Undo_Redo
{
public:
	static Undo_Redo* GetInstance();

	~Undo_Redo();

private:
	static Undo_Redo* instance;

	Array<Version> versions;
	Undo_Redo();
};

#endif