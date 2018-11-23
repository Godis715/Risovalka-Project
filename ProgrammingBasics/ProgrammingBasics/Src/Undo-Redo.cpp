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
	auto primCtrl = PrimController::GetInstance();
	auto objctlr = ObjectController::GetInstance();
	auto reqCtrl = ReqController::GetInstance();

	for (int i = 0; i < IDs.GetSize(); ++i) {
		if (primCtrl->IsPrimitive(IDs[i])) {
			if (objctlr->GetType(IDs[i]) == ot_curve) {
				auto curve = dynamic_cast<Curve*>(primCtrl->GetPrimitive(IDs[i]));
				curve->SetCurveParams(dataBefore[i]);
				continue;
			}
			primCtrl->SetPrimitiveParams(IDs[i], dataBefore[i]);
		}
		else {
			reqCtrl->SetReqParams(IDs[i], dataBefore[i]);
		}
	}
}

void VersionChange::Redo() {
	auto objctlr = ObjectController::GetInstance();
	auto primCtrl = PrimController::GetInstance();
	auto reqCtrl = ReqController::GetInstance();

	for (int i = 0; i < IDs.GetSize(); ++i) {
		if (primCtrl->IsPrimitive(IDs[i])) {
			if (objctlr->GetType(IDs[i]) == ot_curve) {
				auto curve = dynamic_cast<Curve*>(primCtrl->GetPrimitive(IDs[i]));
				curve->SetCurveParams(dataAfter[i]);
				continue;
			}
			primCtrl->SetPrimitiveParams(IDs[i], dataAfter[i]);
		}
		else {
			reqCtrl->SetReqParams(IDs[i], dataAfter[i]);
		}
	}
}

VersionChange::~VersionChange() {
	dataAfter.Clear();
	dataBefore.Clear();
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

	auto primCtrl = PrimController::GetInstance();
	for (int i = 0; i < IDs.GetSize(); ++i) {
		primCtrl->SetPrimitiveParams(IDs[i], dataBefore[i]);
	}
}

void VersionCreateReq::Redo() {
	auto objectController = ObjectController::GetInstance();
	objectController->MakeValid(idReq);

	auto primCtrl = PrimController::GetInstance();
	for (int i = 0; i < IDs.GetSize(); ++i) {
		primCtrl->SetPrimitiveParams(IDs[i], dataAfter[i]);
	}
}

VersionCreateReq::~VersionCreateReq() {
	auto dataController = DataController::GetInstance();
	auto objectController = ObjectController::GetInstance();

	if (!objectController->IsValid(idReq)) {
		dataController->DeleteObject(idReq);

	}
	dataAfter.Clear();
	dataBefore.Clear();
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
	auto objectController = ObjectController::GetInstance();

	if (!objectController->IsValid(IDs[0])) {
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
		return;
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
	auto iter = AllChildren.Begin();
	int j = 0;
	if (iter.IsValid()) {
		do {
			data[j] = *iter;
			++j;
		} while (++iter);
	}
	
	for (int i = 0; i < IDs.GetSize(); ++i) {
		data[j] = IDs[i];
		++j;
	}

	
	
	Version* version = new VersionCreat_Del(type, data);

	versions.Push(version);
	it = versions.End();
}

void Undo_Redo::AddDeleting(const Array<ID>& IDs) {
	auto objController = ObjectController::GetInstance();
	auto dataController = DataController::GetInstance();
	auto primController = PrimController::GetInstance();
	auto reqController = ReqController::GetInstance();

	Set<ID> set;
	Queue<ID> queue;
	for (int i = 0; i < IDs.GetSize(); ++i) {
		queue.Push(IDs[i]);
		set.Add(IDs[i]);
	}

	while (!queue.IsEmpty())
	{
		ID currentID = queue.Pop();
		if (objController->IsValid(currentID)) {
				continue;
				
		}// check CURVE
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
			if (!set.Find(*linkIter).IsValid()) {
				queue.Push(*linkIter);
			}
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
	auto primController = PrimController::GetInstance();
	Array<ID> componentIDs = dataController->GetPrimitiveFromComponents(IDs);
	if (reqController->IsReq(IDs[0])) {
		componentIDs.PushBack(IDs[0]);
	}

	auto version = new VersionChange(tfc_change, componentIDs);

	for (int i = 0; i < componentIDs.GetSize(); ++i) {
		if (objectController->GetType(componentIDs[i]) == ot_curve) {
			auto curve = dynamic_cast<Curve*>(primController->GetPrimitive(componentIDs[i]));
			version->dataBefore[i] = curve->GetCurveParams();
			continue;
		}
		version->dataBefore[i] = objectController->GetObjParam(componentIDs[i]);
	}

	versions.Push(version);
	it = versions.End();
}

void Undo_Redo::CompleteAddChange() {
	auto objectController = ObjectController::GetInstance();
	auto primController = PrimController::GetInstance();

	VersionChange* version;
	if (versions.GetTail()->type == tfc_change) {
		version = static_cast<VersionChange*>(versions.GetTail());
	}
	else {
		// $$$
		return;
	}
	
	for (int i = 0; i < version->IDs.GetSize(); ++i) {
		if (objectController->GetType(version->IDs[i]) == ot_curve) {
			auto curve = dynamic_cast<Curve*>(primController->GetPrimitive(version->IDs[i]));
			version->dataAfter[i] = curve->GetCurveParams();
			continue;
		}
		version->dataAfter[i] = objectController->GetObjParam(version->IDs[i]);

	}
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

void Undo_Redo::Clear() {
	auto i = versions.Begin();
	while (i.IsValid())
	{
		delete *i;
		++i;
	}
	versions.Clear();
	it = List<Version*>::Marker();
}

Undo_Redo::Undo_Redo() {}

void Undo_Redo::DeleteLastVersion() {
	delete versions.GetHead();
	versions.Begin().DeleteCurrent();
}

void Undo_Redo::DeleteVersionAfterIt() {
	while ((it.IsValid()) && (versions.GetSize() != 0) && (versions.End() != it)) {
		delete versions.GetTail();
		versions.End().DeleteCurrent();
	}
}

Undo_Redo* Undo_Redo::instance = nullptr;
#pragma endregion 