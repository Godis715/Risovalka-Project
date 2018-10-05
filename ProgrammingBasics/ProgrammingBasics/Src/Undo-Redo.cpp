#include "Undo-Redo.h"

#define count_vers 10

#pragma region Version
Version::Version(const TypeOFCange _type) : type(_type) {}
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
VersionCreateReq::VersionCreateReq(const TypeOFCange _type, const ID& _id, const Array<ID>& _data) :
	Version(_type), idReq(_id), IDs(_data) {
	dataBefore = Array<Array<double>>(IDs.GetSize());
	dataAfter = Array<Array<double>>(IDs.GetSize());
}

void VersionCreateReq::Undo() {
	auto dataController = DataController::GetInstance();
	auto objectController = ObjectController::GetInstance();
	dataController->DeleteObject(idReq);

	for (int i = 0; i < IDs.GetSize(); ++i) {
		objectController->SetObjParam(IDs[i], dataBefore[i]);
	}
}

void VersionCreateReq::Redo() {
	auto dataController = DataController::GetInstance();
	auto objectController = ObjectController::GetInstance();
	dataController->AddObject(idReq);
	dataController->Connect(idReq, link);

	for (int i = 0; i < IDs.GetSize(); ++i) {
		objectController->SetObjParam(IDs[i], dataAfter[i]);
	}
}

VersionCreateReq::~VersionCreateReq() {

}
#pragma endregion

#pragma region VersionCreat_Del
VersionCreat_Del::VersionCreat_Del(const TypeOFCange _type, Data& _data) : Version(_type), version(_data){}

void VersionCreat_Del::Undo() {

}

void VersionCreat_Del::Redo() {

}

VersionCreat_Del::~VersionCreat_Del() {
	switch (type)
	{
	case tfc_creation: {
		DeleteCreation();
	}
	case tfc_delete: {
		DeleteDelete();
	}
	default:
		break;
	}
}

void VersionCreat_Del::DeleteCreation() {

}

void VersionCreat_Del::DeleteDelete() {

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
	if (type == tfc_before_change) {
		AddChange(IDs);
		return;
	}
	if (type == tfc_before_creation_req) {
		// $$$
		return;
	}
	auto dataController = DataController::GetInstance();

	Array<std::pair<ID, const BinSearchTree<ID, ID>*>> data(IDs.GetSize());
	for (int i = 0; i < IDs.GetSize(); ++i) {
		std::pair<ID, const BinSearchTree<ID, ID>*> element(IDs[i],
			dataController->GetLinks(IDs[i]));
		data.PushBack(element);
	}

	Version* version = new VersionCreat_Del(type, data);
	if (versions.GetSize() == count_vers) {
		DeleteLastVersion();
	}
	versions.PushTail(version);
	it = versions.End();
}

void Undo_Redo::AddVersion(const TypeOFCange type) {
	if (type == tfc_after_change) {
		CompleteAddChange();
		return;
	}
	if (type == tfc_after_creation_req) {
		CompleteAddChange();
		return;
	}
	// $$$
}

void Undo_Redo::AddChange(const Array<ID>& IDs) {
	auto objectController = ObjectController::GetInstance();
	auto dataController = DataController::GetInstance();
	auto componentIDs = dataController->GetPrimitiveFromComponents(IDs);

	auto version = new VersionChange(tfc_before_change, componentIDs);

	Array<std::pair<ID, Array<double>>> data(componentIDs.GetSize());
	for (int i = 0; i < componentIDs.GetSize(); ++i) {
		version->dataBefore[i] = objectController->GetObjParam(componentIDs[i]);
	}

	if (versions.GetSize() == count_vers) {
		DeleteLastVersion();
	}
	versions.PushTail(version);
}

void Undo_Redo::CompleteAddChange() {
	auto objectController = ObjectController::GetInstance();

	VersionChange* version;
	if (versions.GetTail()->type == tfc_before_change) {
		version = static_cast<VersionChange*>(versions.GetTail());
	}
	else {
		// $$$
	}

	for (int i = 0; i < version->IDs.GetSize(); ++i) {
		version->dataAfter[i] = objectController->GetObjParam(version->IDs[i]);
	}
}

void Undo_Redo::AddCreatingReq(const ID& idReq) {
	auto objectController = ObjectController::GetInstance();
	auto dataController = DataController::GetInstance();
	auto componentIDs = dataController->GetPrimitiveFromComponent(idReq);

	auto version = new VersionCreateReq(tfc_before_creation_req, idReq, componentIDs);

	for (int i = 0; i < componentIDs.GetSize(); ++i) {
		version->dataBefore[i] = objectController->GetObjParam(componentIDs[i]);
	}

	
	if (versions.GetSize() == count_vers) {
		DeleteLastVersion();
	}
	versions.PushTail(version);
	it = versions.End();
}

void Undo_Redo::CompleteAddCreatingReq() {
	auto objectController = ObjectController::GetInstance();

	VersionCreateReq* version;
	if (versions.GetTail()->type == tfc_before_creation_req) {
		version = static_cast<VersionCreateReq*>(versions.GetTail());
	}
	else {
		// $$$
	}

	for (int i = 0; i < version->IDs.GetSize(); ++i) {
		version->dataAfter[i] = objectController->GetObjParam(version->IDs[i]);
	}
}

void Undo_Redo::Undo() {
	if ((it.IsValid()) && (it == versions.Begin())) {
		return;
	}
	it.GetValue()->Undo();
	auto it1 = versions.Begin();
	auto it2 = versions.Begin();
	++it2;
	while (it2 != it)
	{
		++it2;
		++it1;
	}
	it = it1;
}

void Undo_Redo::Redo() {
	if ((it.IsValid()) && (it == versions.End())) {
		return;
	}
	++it;
	it.GetValue()->Redo();
}

Undo_Redo::Undo_Redo() {}

void Undo_Redo::DeleteLastVersion() {
	delete versions.GetHead();
	versions.Begin().DeleteCurrent();
}

Undo_Redo* Undo_Redo::instance = nullptr;
#pragma endregion 