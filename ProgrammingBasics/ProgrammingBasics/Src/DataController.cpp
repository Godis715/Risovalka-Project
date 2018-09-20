#include "DataController.h"
#include "ID.h"

DataController* DataController::instance = nullptr;

DataController::DataController() {
	primCtrl = PrimController::GetInstance();
	reqCtrl = ReqController::GetInstance();
	objCtrl = ObjectController::GetInstance();
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
	auto headIterator = linkData.Find(head);
	BinSearchTree<ID, ID>* newNode;
	if (!headIterator.IsValid()) {
		newNode = new BinSearchTree<ID, ID>;
		linkData.Add(head, newNode);
	}
	else {
		newNode = (*headIterator);
	}
	for (int i = 0; i < nodes.GetSize(); ++i) {
		auto repeatCheckIter = newNode->Find(nodes[i]);
		if (!repeatCheckIter.IsValid()) {
			newNode->Add(nodes[i], nodes[i]);

			auto nodeIterator = linkData.Find(nodes[i]);
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

				linkData.Add(nodes[i], currentNode);
			}

			continue;
		}
		else {
			LOG("Connect: array of id contains equal ids", LEVEL_3);
		}
	}

}

void DataController::DeleteObject(const ID& id) {
	BinSearchTree<ID, ID> objectsToDelete;
	objectsToDelete.Add(id, id);
	bool isObjPrim = primCtrl->IsPrimitive(id);

	Queue<ID> queue;
	queue.Push(id);

	// primitive's children should be deleted
	if (isObjPrim) {
		Array<ID> children = primCtrl->GetChildren(id);
		for (int i = 0; i < children.GetSize(); ++i) {
			ID child = children[i];
			bool isDel = objectsToDelete.Find(child).IsValid();
			if (!isDel) {
				queue.Push(child);
				objectsToDelete.Add(child, child);
			}
		}
	}

	// deleting links
	while (!queue.IsEmpty()) {
		ID currID = queue.Pop();
		auto linkIt = linkData.Find(currID);
		if (linkIt.IsValid()) {
			auto connectedNodes = (*linkIt);
			auto connNodesIt = connectedNodes->GetMarker();

			while (connNodesIt.IsValid()) {
				
				auto currConnNode = (*connNodesIt);
				bool isCurrConnNodeReq = reqCtrl->IsReq(currConnNode);
				if (isCurrConnNodeReq) {
					bool isDel = objectsToDelete.Find(currConnNode).IsValid();
					if (!isDel) {
						queue.Push(currConnNode);
					}
				}

				auto linkItOfConnNode = linkData.Find(currConnNode);
				if (linkItOfConnNode.IsValid()) {
					auto connOfConnNode = (*linkItOfConnNode);
					auto connOfConnNodeIt = connOfConnNode->Find(currID);
					if (connOfConnNodeIt.IsValid()) {
						connOfConnNodeIt.Delete();
						if (connOfConnNode->GetSize() == 0) {
							delete connOfConnNode;
							linkItOfConnNode.Delete();
						}
					}
				}

				++connNodesIt;
			}

			delete connectedNodes;
			linkIt.Delete();
		}
	}

	// deleting from containers
	auto objToDelete = objectsToDelete.GetMarker();
	while (objToDelete.IsValid()) {
		ID currID = (*objToDelete);

		bool isCurPrimitive = primCtrl->IsPrimitive(currID);
		bool isCurRequirement = reqCtrl->IsReq(currID);

		if (isCurPrimitive) {
			auto primIter = primData.Find(currID);
			if (!primIter.IsValid()) {
				LOG("DeleteObject: primitive don't contained in data", LEVEL_2);
			}
			primIter.Delete();
		}
		else if (isCurRequirement) {
			auto reqIter = primData.Find(currID);
			if (!reqIter.IsValid()) {
				LOG("DeleteObject: requirement don't contained in data", LEVEL_2);
			}
			reqIter.Delete();
		}
		else {
			LOGERROR("DeleteObject: unknown type", LEVEL_1);
		}
		
		objCtrl->DeleteObj(currID);

		++objToDelete;
	}
}
//
//Component DataController::GetComponent(const ID& id) {
//	Component component;
//	Queue<ID> queue;
//	queue.Push(id);
//
//	while (!queue.IsEmpty()) {
//		ID currID = queue.Pop();
//		auto componentIt = component.Find(currID);
//		if (!componentIt.IsValid()) {
//			component.Add(currID, currID);
//
//			auto linkIt = linkData.Find(currID);
//			// ...
//		}
//	}
//}

