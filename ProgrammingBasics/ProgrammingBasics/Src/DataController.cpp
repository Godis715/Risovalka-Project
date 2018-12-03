#include "DataController.h"
#include "ID.h"

DataController* DataController::instance = nullptr;

DataController::DataController() {
	primCtrl = PrimController::GetInstance();
	reqCtrl = ReqController::GetInstance();
	objCtrl = ObjectController::GetInstance();
	currentComponent = nullptr;
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
	primData.Add(obj);
	LOG("AddObject: primitive successfully added", LEVEL_2);
}
else {
	auto it = reqData.Find(obj);
	if (it.IsValid()) {
		LOG("AddObject: requirement already added", LEVEL_2);
		return;
	}
	reqData.Add(obj);
	LOG("AddObject: requirement successfully added", LEVEL_2);
}
}

void DataController::Connect(const ID& head, const Array<ID>& nodes) {
	LOG("Connect: creating a connection", LEVEL_2);
	auto headIterator = linkData.Find(head);
	Set<ID>* newNode;
	if (!headIterator.IsValid()) {
		newNode = new Set<ID>;
		linkData.Add(head, newNode);
	}
	else {
		newNode = (*headIterator);
	}
	for (int i = 0; i < nodes.GetSize(); ++i) {
		auto repeatCheckIter = newNode->Find(nodes[i]);
		if (!repeatCheckIter.IsValid()) {
			newNode->Add(nodes[i]);

			auto nodeIterator = linkData.Find(nodes[i]);
			Set<ID>* currentNode;
			if (nodeIterator.IsValid()) {
				currentNode = (*nodeIterator);
				auto currentNodeRepeatChecking = currentNode->Find(head);
				if (!currentNodeRepeatChecking.IsValid()) {
					currentNode->Add(head);
				}
			}
			else {
				currentNode = new Set<ID>;
				currentNode->Add(head);

				linkData.Add(nodes[i], currentNode);
			}


			continue;
		}
		else {
			LOG("Connect: array of id contains equal ids", LEVEL_3);
		}
	}

}

void DataController::Connect(const ID& head, Component* headLink) {
	auto linkDataIterator = linkData.Find(head);
	if (linkDataIterator.IsValid()) {
		auto linkIterator = headLink->GetMarker();
		auto node = *linkDataIterator;
		while (linkIterator.IsValid())
		{
			node->Add(*linkIterator);
			++linkIterator;
		}
	}
	else {
		linkData.Add(head, headLink);
	}

	auto linkIterator = headLink->GetMarker();
	while (linkIterator.IsValid())
	{
		auto nodeIterator = linkData.Find(*linkIterator);
		Set<ID>* currentNode;
		if (nodeIterator.IsValid()) {
			currentNode = (*nodeIterator);
			currentNode->Add(head);
		}
		else {
			currentNode = new Set<ID>;
			currentNode->Add(head);

			linkData.Add(*linkIterator, currentNode);
		}
	}
}


void DataController::DeleteObject(const ID& id) {
	if ((!primData.Find(id).IsValid()) && (!reqData.Find(id).IsValid())){
		return;
	}
	DataID objectsToDelete;
	objectsToDelete.Add(id);
	bool isObjPrim = primCtrl->IsPrimitive(id);

	Queue<ID> queue;
	queue.Push(id);

	// deleting links
	while (!queue.IsEmpty()) {
		ID currID = queue.Pop();
		auto linkIt = linkData.Find(currID);
		if (linkIt.IsValid()) {
			Component* connectedNodes = (*linkIt);
			auto connNodesIt = connectedNodes->GetMarker();

			while (connNodesIt.IsValid()) {
				
				ID currConnNode = (*connNodesIt);
				++connNodesIt;
				if (objCtrl->GetType(currConnNode) == ot_curve) {
					auto curve = dynamic_cast<Curve*>(primCtrl->GetPrimitive(currConnNode));
					if (!curve->ItISExtremePoint(currID)) {
						curve->DeletePoint(currID);
						continue;
					}// we have to delete point from  curve
				}// if point don`t extreme point we heve NOT delete curve
				bool isCurrConnNodeReq = reqCtrl->IsReq(currConnNode);
				bool isCurrConnNodePrim = primCtrl->IsPrimitive(currConnNode);
				bool isCurrObjPrim = primCtrl->IsPrimitive(currID);
				if (isCurrConnNodeReq || isObjPrim && isCurrObjPrim) {
					bool isDel = objectsToDelete.Find(currConnNode).IsValid();
					if (!isDel) {
						queue.Push(currConnNode);
						objectsToDelete.Add(currConnNode);
					}
				}

				// delete connect between currConnNode and currID
				auto linkItOfConnNode = linkData.Find(currConnNode);
				if (linkItOfConnNode.IsValid()) {
					Component* connOfConnNode = (*linkItOfConnNode);
					auto connOfConnNodeIt = connOfConnNode->Find(currID);
					if (connOfConnNodeIt.IsValid()) {
						connOfConnNodeIt.Delete();
						if (connOfConnNode->GetSize() == 0) {
							delete connOfConnNode;
							linkItOfConnNode.Delete();
						}
					}
				}


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
			auto reqIter = reqData.Find(currID);
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

void DataController::MakeInValid(ID& id) {
	if ((reqCtrl->IsReq(id)) || (!objCtrl->IsValid(id))) {
		objCtrl->MakeInValid(id);
		return;
	}

	Queue<ID> queue;
	objCtrl->MakeInValid(id);
	queue.Push(id);


	while (!queue.IsEmpty()) {
		ID currID = queue.Pop();
		
		auto linkIt = linkData.Find(currID);
		if (linkIt.IsValid()) {
			auto connectedNodes = (*linkIt);
			auto connNodesIt = connectedNodes->GetMarker();

			while (connNodesIt.IsValid()) {

				ID currIDLink = (*connNodesIt);
				++connNodesIt;
				if (!objCtrl->IsValid(currIDLink)) {
					continue;
				}
				if (objCtrl->GetType(currIDLink) == ot_curve) {
					auto curve = dynamic_cast<Curve*>(primCtrl->GetPrimitive(currIDLink));
					if (!curve->ItISExtremePoint(id)) {
						continue;
					}
				}// check Curve
				objCtrl->MakeInValid(currIDLink);

				if (reqCtrl->IsReq(currIDLink)) {
					continue;
				}
				queue.Push(currIDLink);
			}
		}
	}
}

void DataController::Clear() {
	auto linkIt = linkData.GetMarker();
	while (linkIt.IsValid()) {
		delete *linkIt;
		++linkIt;
	}
	linkData.DeleteDict();
	primData.DeleteSet();
	reqData.DeleteSet();
}

Component DataController::GetComponent(const ID& id) {
	Component component;
	Queue<ID> queue;
	queue.Push(id);

	while (!queue.IsEmpty()) {
		ID currID = queue.Pop();
		if (!objCtrl->IsValid(currID)) {
			continue;
		}
		auto componentIt = component.Find(currID);
		if (!componentIt.IsValid()) {
			component.Add(currID);

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

void DataController::CashComponent(const Array<ID>& IDs) {
	delete currentComponent;
	currentComponent = new Component;

	bool* matching = new bool[IDs.GetSize()];
	for (int i = 0; i < IDs.GetSize(); ++i) {
		matching[i] = true;
	}

	bool isComplete = false;
	while (!isComplete)
	{
		isComplete = true;
		for (int i = 0; i < IDs.GetSize(); ++i) {
			if (matching[i]) {
				matching[i] = false;
				isComplete = false;
				auto component = GetComponent(IDs[i]);
				auto it = component.GetMarker();
				while (it.IsValid())
				{
					currentComponent->Add(*it);
					++it;
				}

				for (int j = i + 1; j < IDs.GetSize(); ++j) {
					if ((matching[j]) && (component.Find(IDs[j]).IsValid())) {
						matching[j] = false;
					}
				}
			}
		}
	}
}

Component* DataController::GetComponent() {
	return currentComponent;
}

ID DataController::GetObjectInCircle(double x, double y, double r) {
	ID currentObject = IDGenerator::GetNullID();
	bool wasPoint = false;
	double minDist = DBL_MAX;
	auto primIt = primData.GetMarker();
	while (primIt.IsValid()) {
		ID obj = *primIt;
		++primIt;
		if (!objCtrl->IsValid(obj)) {
			continue;
		}
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
	}

	return currentObject;
}

Set<ID>::bst_iterator DataController::GetPrimIterator() {
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
			++connObjIt;
			if (!objCtrl->IsValid(currObj)) {
				continue;
			}
			auto currObjType = objCtrl->GetType(currObj);

			if (primCtrl->IsPrimitive(objType) && reqCtrl->IsReq(currObj) ||
				primCtrl->IsPrimitive(currObj) && reqCtrl->IsReq(objType)) {
				relatedObjects.PushBack(currObj);
			}

		
		}
	}
	return relatedObjects;
}

Array<ID> DataController::GetPrimitiveFromComponent(const ID& id) {
	auto component = GetComponent(id);
	return GetPrimitiveFromComponent(component);
}

Array<ID> DataController::GetPrimitiveFromComponent(Component& component) {
	Array<ID> result;
	auto iter = component.GetMarker();
	while (iter.IsValid())
	{
		if (primCtrl->IsPrimitive(*iter)) {
			result.PushBack(*iter);
		}
		++iter;
	}

	return result;
}

Array<ID> DataController::GetPrimitiveFromComponents(const Array<ID>& IDs) {
	if (IDs.GetSize() == 0) {
		return Array<ID>(0);
	}

	bool* matching = new bool[IDs.GetSize()];
	for (int i = 0; i < IDs.GetSize(); ++i) {
		matching[i] = true;
	}

	auto result = Array<ID>(0);
	bool isComplete = false;
	Component component;
	while (!isComplete)
	{
		isComplete = true;
		for (int i = 0; i < IDs.GetSize(); ++i) {
			if (matching[i]) {
				matching[i] = false;
				isComplete = false;
				component = GetComponent(IDs[i]);
				result += GetPrimitiveFromComponent(component);

				for (int j = i + 1; j < IDs.GetSize(); ++j) {
					if ((matching[j]) && (component.Find(IDs[j]).IsValid())){
						matching[j] = false;
					}
				}
			}
		}
	}
	return result;
}

bool DataController::PointInArea(double point_x, double point_y, double x1, double y1, double x2, double y2) const {
	if ((point_y >= y1 && point_x >= x1 && point_y <= y2 && point_x <= x2) ||
		(point_y >= y1 && point_x <= x1 && point_y <= y2 && point_x >= x2) ||
		(point_y <= y1 && point_x >= x1 && point_y >= y2 && point_x <= x2) ||
		(point_y <= y1 && point_x <= x1 && point_y >= y2 && point_x >= x2))
	{
		return true;
	}
	else
	{
		return false;
	}
}

Array<ID> DataController::GetObjectsByArea(double x1, double y1, double x2, double y2) {
	Array<ID> obj_id;
	Primitive* obj = nullptr;
	for (auto i = primData.GetMarker(); i.IsValid(); ++i) {
		if (!objCtrl->IsValid(*i)) {
			continue;
		}
		obj = primCtrl->GetPrimitive(*i);
		switch (obj->GetType())
		{
		case ot_point: {
			Point* point = dynamic_cast<Point*>(obj);
			if (PointInArea(point->GetPos().x, point->GetPos().y, x1, y1, x2, y2))
			{
				obj_id.PushBack(point->GetID());
			}
			break;
		}
		case ot_segment: {
			Segment* segment = dynamic_cast<Segment*>(obj);
			if (PointInArea(segment->GetPointPos1().x, segment->GetPointPos1().y, x1, y1, x2, y2) &&
				PointInArea(segment->GetPointPos2().x, segment->GetPointPos2().y, x1, y1, x2, y2)
				)
			{
				obj_id.PushBack(segment->GetID());
			}
			break;
		}
		case ot_arc: {
			Arc* arc = dynamic_cast<Arc*>(obj);
			if (PointInArea(arc->GetPointPos1().x, arc->GetPointPos1().y, x1, y1, x2, y2) &&
				PointInArea(arc->GetPointPos2().x, arc->GetPointPos2().y, x1, y1, x2, y2)
				)
			{
				obj_id.PushBack(arc->GetID());
			}
			break;
		}
		case ot_circle: {
			Circle* circle = dynamic_cast<Circle*>(obj);
			if (PointInArea(circle->GetCenter().x - circle->GetRadius(), circle->GetCenter().y, x1, y1, x2, y2) &&
				PointInArea(circle->GetCenter().x + circle->GetRadius(), circle->GetCenter().y, x1, y1, x2, y2) &&
				PointInArea(circle->GetCenter().x, circle->GetCenter().y - circle->GetRadius(), x1, y1, x2, y2) &&
				PointInArea(circle->GetCenter().x, circle->GetCenter().y + circle->GetRadius(), x1, y1, x2, y2))
			{
				obj_id.PushBack(circle->GetID());
			}
			break;
		}
		default: {
			break;
		}
		}
	}
	return obj_id;
}

Set<ID>* DataController::GetLinks(const ID& id) {
	auto iter = linkData.Find(id);
	if (iter.IsValid()) {
		return *iter;
	}
	else {
		// $$$
		return nullptr;
	}
}