#include "Undo-Redo.h"

#define count_vers 10

Version::Version(const TypeOFCange _type) : type(_type) {}

#pragma region VersionChange
VersionChange::VersionChange(const TypeOFCange _type, Data& _data) : Version(_type), version(_data) {}


VersionChange::~VersionChange() {

}
#pragma endregion 


#pragma region VersionCreat_Del
VersionCreat_Del::VersionCreat_Del(const TypeOFCange _type, Data& _data) : Version(_type), version(_data){}

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
	if (type == tfc_change) {
		AddChange(IDs);
		return;
	}

	auto primController = PrimController::GetInstance();
	auto dataController = DataController::GetInstance();


	Array<std::pair<ID, const BinSearchTree<ID, ID>*>> data(IDs.GetSize());
	for (int i = 0; i < IDs.GetSize(); ++i) {
		// TEMP
		std::pair<ID, const BinSearchTree<ID, ID>*> element(IDs[i],
			dataController->GetLinks(IDs[i]));
		data.PushBack(element);
	}
	Version* version = new VersionCreat_Del(type, data);
	if (versions.GetSize() == count_vers) {
		DeleteLastVersion();
	}
	versions.PushTail(version);
}

void Undo_Redo::AddChange(const Array<ID>& IDs) {
	auto primController = PrimController::GetInstance();
	auto datsController = DataController::GetInstance();
	auto componentIDs = datsController->GetPrimitiveFromComponents(IDs);

	
	Array<std::pair<ID, const Array<double>>> data(componentIDs.GetSize());
	for (int i = 0; i < componentIDs.GetSize(); ++i) {
		// TEMP
		std::pair<ID, const Array<double>> element(componentIDs[i],
			primController->GetPrimitiveParamsAsValues(componentIDs[i]));
		data.PushBack(element);
	}

	Version* version = new VersionChange(tfc_change, data);
	if (versions.GetSize() == count_vers) {
		DeleteLastVersion();
	}
	versions.PushTail(version);
}

Undo_Redo::Undo_Redo() {}

void Undo_Redo::DeleteLastVersion() {

}

Undo_Redo* Undo_Redo::instance = nullptr;
#pragma endregion 