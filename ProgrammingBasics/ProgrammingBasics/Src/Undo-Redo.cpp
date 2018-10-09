#include "Undo-Redo.h"

#define count_vers 10

#pragma region Version
Version::Version(const TypeOFCange _type) : type(_type) {}
Version::~Version() {}
#pragma endregion 

#pragma region VersionChange
VersionChange::VersionChange(const TypeOFCange _type, const Array<ID>& _data) :
	Version(_type), IDs(_data) {
	dataBefore = Array<Array<double>>(IDs.GetSize());
	dataAfter = Array<Array<double>>(IDs.GetSize());
}

void VersionChange::Undo() {
	auto objectController = ObjectController::GetInstance();

	for (int i = 0; i < IDs.GetSize(); ++i) {
		objectController->SetObjParam(IDs[i], dataBefore[i]);
	}
}

void VersionChange::Redo() {
	auto objectController = ObjectController::GetInstance();

	for (int i = 0; i < IDs.GetSize(); ++i) {
		objectController->SetObjParam(IDs[i], dataAfter[i]);
	}
}

VersionChange::~VersionChange() {

}
#pragma endregion 

#pragma region VersionCreateReq
VersionCreateReq::VersionCreateReq(const TypeOFCange _type, const Array<ID>& _data) :
	Version(_type), IDs(_data) {
	dataBefore = Array<Array<double>>(IDs.GetSize());
	dataAfter = Array<Array<double>>(IDs.GetSize());
}

void VersionCreateReq::Undo() {
	auto objectController = ObjectController::GetInstance();
	objectController->MakeInValid(idReq);

	for (int i = 0; i < IDs.GetSize(); ++i) {
		objectController->SetObjParam(IDs[i], dataBefore[i]);
	}
}

void VersionCreateReq::Redo() {
	auto objectController = ObjectController::GetInstance();
	objectController->MakeValid(idReq);

	for (int i = 0; i < IDs.GetSize(); ++i) {
		objectController->SetObjParam(IDs[i], dataAfter[i]);
	}
}

VersionCreateReq::~VersionCreateReq() {

}
#pragma endregion

#pragma region VersionCreat_Del
VersionCreat_Del::VersionCreat_Del(const TypeOFCange _type, const Array<ID>& _IDs) :
	Version(_type), IDs(_IDs){}

void VersionCreat_Del::Undo() {
	auto objectControler = ObjectController::GetInstance();
	if (type == tfc_creation) {
		for (int i = 0; i < IDs.GetSize(); ++i) {
			objectControler->MakeInValid(IDs[i]);
		}
	}
	else {
		for (int i = 0; i < IDs.GetSize(); ++i) {
			objectControler->MakeValid(IDs[i]);
		}
	}
}

void VersionCreat_Del::Redo() {
	auto objectControler = ObjectController::GetInstance();
	if (type == tfc_creation) {
		for (int i = 0; i < IDs.GetSize(); ++i) {
			objectControler->MakeValid(IDs[i]);
		}
	}
	else {
		for (int i = 0; i < IDs.GetSize(); ++i) {
			objectControler->MakeInValid(IDs[i]);
		}
	}
}

VersionCreat_Del::~VersionCreat_Del() {
	auto dataController = DataController::GetInstance();

	if (type == tfc_delete) {
		for (int i = 0; i < IDs.GetSize(); ++i) {
			dataController->DeleteObject(IDs[i]);
		}
	}
}
#pragma endregion 

#pragma region Undo_Redo
Undo_Redo* Undo_Redo::GetInstance() {
	if (instance == nullptr) {
		instance = new Undo_Redo;
	}
	return instance;
}

void Undo_Redo::AddVersion(const TypeOFCange type, const Array<ID>& IDs) {

	if (IDs.GetSize() == 0) {
		// $$$
	}
	if (versions.GetSize() == count_vers) {
		DeleteLastVersion();
	}

	DeleteVersionAfterIt();

	if (type == tfc_change) {
		AddChange(IDs);
		return;
	}
	if (type == tfc_delete) {
		AddDeleting(IDs);
		return;
	}
	if (type == tfc_creation_req) {
		AddCreatingReq(IDs);
		return;
	}
	auto primController = PrimController::GetInstance();
	List<ID> AllChildren;
	for (int i = 0; i < IDs.GetSize(); ++i) {
		auto children = primController->GetChildren(IDs[i]);
		for (int j = 0; j < children.GetSize(); ++j) {
			AllChildren.Push(children[j]);
		}
	}
	Array<ID> data(IDs.GetSize() + AllChildren.GetSize());
	for (int i = 0; i < IDs.GetSize(); ++i) {
		data[i] = IDs[i];
	}

	
	auto iter = AllChildren.Begin();
	
	if (iter.IsValid()) {
		int i = IDs.GetSize();
		do {
			data[i] = *iter;
			++i;
		} while (++iter);
	}
	Version* version = new VersionCreat_Del(type, data);

	versions.Push(version);
	it = versions.End();
}

void Undo_Redo::AddDeleting(const Array<ID>& IDs) {
	auto dataController = DataController::GetInstance();
	auto primController = PrimController::GetInstance();
	auto reqController = ReqController::GetInstance();

	Set<ID> set;
	Queue<ID> queue;
	for (int i = 0; i < IDs.GetSize(); ++i) {
		queue.Push(IDs[i]);
	}

	while (!queue.IsEmpty())
	{
		ID currentID = queue.Pop();
		set.Add(currentID);
		if (reqController->IsReq(currentID)) {
			continue;
		}
		auto links = dataController->GetLinks(currentID);
		if (links == nullptr) {
			continue;
		}
		auto linkIter = links->GetMarker();
		while (linkIter.IsValid())
		{
			queue.Push(*linkIter);
			++linkIter;
		}
	}

	Array<ID> deletedIDs(set.GetSize());
	auto iter = set.GetMarker();
	for (int i = 0; i < set.GetSize(); ++i) {
		deletedIDs[i] = *iter;
		++iter;
	}

	Version* version = new VersionCreat_Del(tfc_delete, deletedIDs);

	versions.Push(version);
	it = versions.End();
}

void Undo_Redo::AddChange(const Array<ID>& IDs) {
	auto objectController = ObjectController::GetInstance();
	auto dataController = DataController::GetInstance();
	auto reqController = ReqController::GetInstance();
	auto componentIDs = dataController->GetPrimitiveFromComponents(IDs);
	if (reqController->IsReq(IDs[0])) {
		componentIDs.PushBack(IDs[0]);
	}

	auto version = new VersionChange(tfc_change, componentIDs);

	Array<std::pair<ID, Array<double>>> data(componentIDs.GetSize());
	for (int i = 0; i < componentIDs.GetSize(); ++i) {
		version->dataBefore[i] = objectController->GetObjParam(componentIDs[i]);
	}

	versions.Push(version);
	it = versions.End();
}

void Undo_Redo::CompleteAddChange() {
	auto objectController = ObjectController::GetInstance();

	VersionChange* version;
	if (versions.GetTail()->type == tfc_change) {
		version = static_cast<VersionChange*>(versions.GetTail());
	}
	else {
		// $$$
		return;
	}
	
	Array<Array<double>> dataAfter(version->IDs.GetSize());
	for (int i = 0; i < version->IDs.GetSize(); ++i) {
		dataAfter[i] = objectController->GetObjParam(version->IDs[i]);

	}
	version->dataAfter = dataAfter;
}

void Undo_Redo::AddCreatingReq(const Array<ID>& IDs) {
	auto objectController = ObjectController::GetInstance();
	auto dataController = DataController::GetInstance();
	auto componentIDs = dataController->GetPrimitiveFromComponents(IDs);

	auto version = new VersionCreateReq(tfc_creation_req, componentIDs);

	for (int i = 0; i < componentIDs.GetSize(); ++i) {
		version->dataBefore[i] = objectController->GetObjParam(componentIDs[i]);
	}

	versions.Push(version);
	it = versions.End();
}

void Undo_Redo::CompleteAddCreatingReq(const ID& idReq) {
	auto objectController = ObjectController::GetInstance();

	VersionCreateReq* version;
	if (versions.GetTail()->type == tfc_creation_req) {
		version = static_cast<VersionCreateReq*>(versions.GetTail());
	}
	else {
		// $$$
		return;
	}

	for (int i = 0; i < version->IDs.GetSize(); ++i) {
		version->dataAfter[i] = objectController->GetObjParam(version->IDs[i]);
	}

	version->idReq = idReq;
}

void Undo_Redo::Undo() {
	if ((!it.IsValid()) || (it == versions.BeforeBegin())) {
		return;
	}
	(*it)->Undo();
	auto it1 = versions.BeforeBegin();
	auto it2 = versions.Begin();
	while (it2 != it)
	{
		++it2;
		++it1;
	}
	it = it1;
}

void Undo_Redo::Redo() {
	if ((!it.IsValid()) || (it == versions.End())) {
		return;
	}
	++it;
	(*it)->Redo();
}

Undo_Redo::Undo_Redo() {}

void Undo_Redo::DeleteLastVersion() {
	delete versions.GetHead();
	versions.Begin().Delete();
}

void Undo_Redo::DeleteVersionAfterIt() {
	while ((it.IsValid()) && (versions.End() != it) && (versions.GetSize() != 0)) {
		delete versions.GetTail();
		versions.End().Delete();
	}
}

Undo_Redo* Undo_Redo::instance = nullptr;
#pragma endregion 