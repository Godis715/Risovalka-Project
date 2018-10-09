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
VersionCreat_Del::VersionCreat_Del(const TypeOFCange _type, const Array<ID>& _IDs, const Array<Set<ID>*>& _links) :
	Version(_type), IDs(_IDs), links(_links){}

void VersionCreat_Del::Undo() {
	auto dataController = DataController::GetInstance();
	if (type == tfc_creation) {
		for (int i = 0; i < IDs.GetSize(); ++i) {
			dataController->DeleteObject(IDs[i]);
			//delete links[i];
		}
	}
	else {
		for (int i = 0; i < IDs.GetSize(); ++i) {
			dataController->AddObject(IDs[i]);
			dataController->Connect(IDs[i], links[i]);
		}
	}
}

void VersionCreat_Del::Redo() {
	auto dataController = DataController::GetInstance();
	if (type == tfc_creation) {
		for (int i = 0; i < IDs.GetSize(); ++i) {
			dataController->AddObject(IDs[i]);
			dataController->Connect(IDs[i], links[i]);
		}
	}
	else {
		for (int i = 0; i < IDs.GetSize(); ++i) {
			dataController->DeleteObject(IDs[i]);
			//delete links[i];
		}
	}
}

VersionCreat_Del::~VersionCreat_Del() {
	auto objectController = ObjectController::GetInstance();

	if (type == tfc_delete) {
		for (int i = 0; i < IDs.GetSize(); ++i) {
			objectController->DeleteObj(IDs[i]);
			delete links[i];
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
	if ((it.IsValid()) && (versions.End() != it)) {
		DeleteVersionAfterIt();
	}
	if (type == tfc_change) {
		AddChange(IDs);
		return;
	}
	if (type == tfc_creation_req) {
		AddCreatingReq(IDs);
		return;
	}
	auto dataController = DataController::GetInstance();

	Array<Set<ID>*> links(IDs.GetSize());
	for (int i = 0; i < IDs.GetSize(); ++i) {
		links[i] = dataController->GetLinks(IDs[i]);
	}

	Version* version = new VersionCreat_Del(type, IDs, links);

	versions.Add(version);
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
	versions.Add(version);
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

	versions.Add(version);
	it = versions.End();
}

void Undo_Redo::CompleteAddCreatingReq(const ID& idReq) {
	auto objectController = ObjectController::GetInstance();
	auto dataController = DataController::GetInstance();

	VersionCreateReq* version;
	if (versions.GetTail()->type == tfc_creation_req) {
		version = static_cast<VersionCreateReq*>(versions.GetTail());
	}
	else {
		// $$$
		return;
	}

	Array<Array<double>> dataAfter(version->IDs.GetSize());
	for (int i = 0; i < version->IDs.GetSize(); ++i) {
		version->dataAfter[i] = objectController->GetObjParam(version->IDs[i]);
	}
	version->dataAfter = dataAfter;

	version->link = dataController->GetLinks(idReq);
	version->idReq = idReq;
}

void Undo_Redo::Undo() {
	if ((!it.IsValid()) && (it == versions.Begin())) {
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
	if ((!it.IsValid()) && (it == versions.End())) {
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

void Undo_Redo::DeleteVersionAfterIt() {
	while ((it.IsValid()) && (versions.End() != it)) {
		delete versions.GetTail();
	}
}

Undo_Redo* Undo_Redo::instance = nullptr;
#pragma endregion 