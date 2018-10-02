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
				bool isCurrConnNodePrim = primCtrl->IsPrimitive(currConnNode);
				bool isCurrObjPrim = primCtrl->IsPrimitive(currID);
				if (isCurrConnNodeReq || isObjPrim && isCurrObjPrim) {
					bool isDel = objectsToDelete.Find(currConnNode).IsValid();
					if (!isDel) {
						queue.Push(currConnNode);
						objectsToDelete.Add(currConnNode, currConnNode);
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
void DataController::Clear() {
	auto linkIt = linkData.GetMarker();
	while (linkIt.IsValid()) {
		delete *linkIt;
		++linkIt;
	}
	linkData.DeleteDict();
	primData.DeleteDict();
	reqData.DeleteDict();
}

Component DataController::GetComponent(const ID& id) {
	Component component;
	Queue<ID> queue;
	queue.Push(id);

	while (!queue.IsEmpty()) {
		ID currID = queue.Pop();
		auto componentIt = component.Find(currID);
		if (!componentIt.IsValid()) {
			component.Add(currID, currID);

			auto linkIt = linkData.Find(currID);
			if (linkIt.IsValid()) {
				auto childrenIt = (*linkIt)->GetMarker();
				while (childrenIt.IsValid()) {
					if (!component.Find(*childrenIt).IsValid()) {
						queue.Push(*childrenIt);
					}
					++childrenIt;
				}
			}
		}
	}
	return component;
}

ID DataController::GetObjectInCircle(double x, double y, double r) {
	ID currentObject = IDGenerator::GetNullID();
	bool wasPoint = false;
	double minDist = DBL_MAX;
	auto primIt = primData.GetMarker();
	while (primIt.IsValid()) {
		ID obj = *primIt;
		double dist = primCtrl->GetDistanceToPoint(obj, x, y);
		if (dist <= r) {
			if (objCtrl->GetType(obj) == ot_point) {
				if (wasPoint) {
					if (dist < minDist) {
						minDist = dist;
						currentObject = obj;
					}
				}
				else {
					wasPoint = true;
					currentObject = obj;
				}
			}
			else {
				if (!wasPoint) {
					if (dist < minDist) {
						minDist = dist;
						currentObject = obj;
					}
				}
			}
		}
		++primIt;
	}

	return currentObject;
}

BinSearchTree<ID, ID>::bst_iterator DataController::GetPrimIterator() {
	return primData.GetMarker();
}

Array<ID> DataController::GetRelatedObjects(const ID& obj) {
	auto objType = objCtrl->GetType(obj);
	auto compIt = linkData.Find(obj);
	Array<ID> relatedObjects(0);
	if (compIt.IsValid()) {
		auto connectedObjects = *compIt;
		auto connObjIt = connectedObjects->GetMarker();
		while (connObjIt.IsValid()) {
			
			ID currObj = *connObjIt;
			auto currObjType = objCtrl->GetType(currObj);

			if (primCtrl->IsPrimitive(objType) && reqCtrl->IsReq(currObj) ||
				primCtrl->IsPrimitive(currObj) && reqCtrl->IsReq(objType)) {
				relatedObjects.PushBack(currObj);
			}

			++connObjIt;
		}
	}
	return relatedObjects;
}
