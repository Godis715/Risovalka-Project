#include "DataController.h"


DataController* DataController::instance = nullptr;

DataController::DataController() {
	primCtrl = PrimController::GetInstance();
	reqCtrl = ReqController::GetInstance();
}


DataController* DataController::GetInstance() {
	if (instance == nullptr) {
		instance = new DataController;
	}
	return instance;
}

void DataController::AddObject(const ID& obj) {
	LOG("AddObject: adding object to data", LEVEL_2);
	bool isPrim = primCtrl->IsPrimitive(obj);
	bool isReq = reqCtrl->IsReq(obj);
	if (!(isPrim || isReq)) {
		LOGERROR("AddObject: object has a bad type", LEVEL_1);
	}
	if (isPrim) {
		auto it = primData.Find(obj);
		if (it.IsValid()) {
			LOG("AddObject: primitive already added", LEVEL_2);
			return;
		}
		primData.Add(obj, obj);
		LOG("AddObject: primitive successfully added", LEVEL_2);
	}
	else {
		auto it = reqData.Find(obj);
		if (it.IsValid()) {
			LOG("AddObject: requirement already added", LEVEL_2);
			return;
		}
		reqData.Add(obj, obj);
		LOG("AddObject: requirement successfully added", LEVEL_2);
	}
}

void DataController::Connect(const ID& head, const Array<ID>& nodes) {
	LOG("Connect: creating a connection", LEVEL_2);
	auto headIterator = dataLink.Find(head);
	BinSearchTree<ID, ID>* newNode;
	if (!headIterator.IsValid()) {
		newNode = new BinSearchTree<ID, ID>;
	}
	else {
		newNode = (*headIterator);
	}
	for (int i = 0; i < nodes.GetSize(); ++i) {
		auto repeatCheckIter = newNode->Find(nodes[i]);
		if (repeatCheckIter.IsValid()) {
			newNode->Add(nodes[i], nodes[i]);

			auto nodeIterator = dataLink.Find(nodes[i]);
			BinSearchTree<ID, ID>* currentNode;
			if (nodeIterator.IsValid()) {
				currentNode = (*nodeIterator);
				auto currentNodeRepeatChecking = currentNode->Find(head);
				if (!currentNodeRepeatChecking.IsValid()) {
					currentNode->Add(head, head);
				}
			}
			else {
				currentNode = new BinSearchTree<ID, ID>;
				currentNode->Add(head, head);

				dataLink.Add(nodes[i], currentNode);
			}

			continue;
		}
		else {
			LOG("Connect: array of id contains equal ids", LEVEL_3);
		}
	}

}

void DataController::DeleteObject(const ID& id) { }

Array<ID> DataController::GetComponent(const ID&) const;
