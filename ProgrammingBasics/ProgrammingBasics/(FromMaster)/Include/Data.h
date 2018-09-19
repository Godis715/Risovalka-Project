#ifndef __DATA
#define __DATA

#define Prim Primitive*
#define Req Requirement*

#include "Logger.h"

class Data
{
private:
	class Component
	{
	public:
		Component() {
			treePrim = new PairTree<ID, Prim, Req>;
			treeReq = new PairTree<ID, Req, Prim>;
		}
		~Component() {
			delete treePrim;
			delete treeReq;
		}

		PairTree<ID, Prim, Req>* treePrim;
		PairTree<ID, Req, Prim>* treeReq;
	};

	Array<Component*> data;

	void MakeFlag(int index) {
		PairTree<ID, Prim, Req>* treePrim = data[index]->treePrim;
		PairTree<ID, Req, Prim>* treeReq = data[index]->treeReq;

		PairTree<ID, Prim, Req>::PairMarker markerPrim = treePrim->GetPairMarker();
		do
		{
			markerPrim.MakeFlag();
		} while (++markerPrim);

		PairTree<ID, Req, Prim>::PairMarker markerReq = treeReq->GetPairMarker();
		do
		{
			markerReq.MakeFlag();
		} while (++markerReq);
	}

	void TakePrim(Deck<PairNode<ID, Prim, Req>*>& deckPrim, List<PairNode<ID, Prim, Req>*>* list) {
		auto marker = list->GetMarker();
		do
		{
			if (marker.GetValue()->flag) {
				deckPrim.PushBack(marker.GetValue());
			}
		} while (++marker);
	}

	void TakeReq(Deck<PairNode<ID, Req, Prim>*> deckReq, List<PairNode<ID, Req, Prim>*>* list) {
		auto marker = list->GetMarker();
		do
		{
			if (marker.GetValue()->flag) {
				deckReq.PushBack(marker.GetValue());
			}
		} while (++marker);
	}

	void SplitingAndBFS(int index) {
		MakeFlag(index);
		PairTree<ID, Prim, Req>* treePrim = data[index]->treePrim;
		PairTree<ID, Req, Prim>* treeReq = data[index]->treeReq;

		Deck<PairNode<ID, Prim, Req>*> deckPrim;
		Deck<PairNode<ID, Req, Prim>*> deckReq;

		PairNode<ID, Prim, Req>* nodePrim;
		PairNode<ID, Req, Prim>* nodeReq;

		while (treeReq->GetSize() > 0) {
			Component* component = new Component;
			data.PushBack(component);
			PairNode<ID, Req, Prim>* nodeReq = treeReq->GetNode();
			deckReq.PushBack(nodeReq);
			while (!deckReq.IsEmpty())
			{
				while (!deckReq.IsEmpty())
				{
					nodeReq = deckReq.PopBack();
					nodeReq->flag = false;
					treeReq->ThrowOutNode(nodeReq);
					component->treeReq->Add(nodeReq);
					TakePrim(deckPrim, nodeReq->list);
				}
				while (!deckPrim.IsEmpty())
				{
					nodePrim = deckPrim.PopBack();
					nodePrim->flag = false;
					treePrim->ThrowOutNode(nodePrim);
					component->treePrim->Add(nodePrim);
					TakeReq(deckReq, nodePrim->list);
				}
			}

		}

		if (treePrim->GetSize() == 0) {
			data.Erase(index);
			return;
		}

		PairTree<ID, Prim, Req>::PairMarker marker = treePrim->GetPairMarker();
	
		/*nodePrim = treePrim->GetNode();
		deckPrim.PushBack(nodePrim);
		while (!deckPrim.IsEmpty()) {
		nodePrim = deckPrim.PopBack();
		if (nodePrim->left != nullptr) {
		deckPrim.PushBack(nodePrim->left);
		}
		if (nodePrim->right != nullptr) {
		deckPrim.PushBack(nodePrim->right);
		}

		}*/
		do
		{
			delete marker.GetList();
			dict->Add(marker.GetKey(), marker.GetValue());
		} while (++marker);
		delete treePrim;
		delete treeReq;
		data.Erase(index);
	}

	void CreateNewComponent(Array<ID>& keys, Array<Prim>& elements, ID& key, Req& value) {
		Component* component = new Component;
		int index = data.GetSize();
		data.PushBack(component);

		PairNode<ID, Req, Prim>* nodeReq = new PairNode<ID, Req, Prim>(key, value);
		nodeReq->list = new List<PairNode<ID, Prim, Req>*>;
		data[index]->treeReq->Add(nodeReq);
		key.index = index;
		// pushing new node
		for (int i = 0; i < elements.GetSize(); ++i) {
			PairNode<ID, Prim, Req>* nodePrim = new PairNode<ID, Prim, Req>(keys[i], elements[i]);
			nodePrim->list = new List<PairNode<ID, Req, Prim>*>;
			nodePrim->list->PushTail(nodeReq);
			nodeReq->list->PushTail(nodePrim);
			data[index]->treePrim->Add(nodePrim);
			keys[i].index = index;
		}
	}

	void DeletePrim(const int index, const ID& key) {
		PairTree<ID, Prim, Req>* treeFirst = data[index]->treePrim;
		PairTree<ID, Req, Prim>* treeSecond = data[index]->treeReq;
		PairNode<ID, Prim, Req>* temp;
		PairNode<ID, Prim, Req>* node1;
		PairNode<ID, Req, Prim>* node2;

		temp = treeFirst->GetNode(key);
		if (temp == nullptr) {
			return;
		}
		List<PairNode<ID, Req, Prim>*>* list = temp->list;
		auto listMarker = list->GetMarker();

		do
		{
			node2 = listMarker.GetValue();
			List<PairNode<ID, Prim, Req>*>* listReqOnPrim = node2->list;
			auto listMarkerReq = listReqOnPrim->GetMarker();

			do
			{
				node1 = listMarkerReq.GetValue();
				// Clearing link on this Req
				if (node1 != temp) {
					List<PairNode<ID, Req, Prim>*>* listPrimOnReq = node1->list;
					auto listMarkerPrim = listPrimOnReq->GetMarker();

					do
					{
						if (node2 == listMarkerPrim.GetValue()) {
							listMarkerPrim.DeleteCurrent();

							break;
						}
					} while (++listMarkerPrim);
				}
			} while (++listMarkerReq);
			// delete Requariments

			delete listReqOnPrim;
			delete node2->value;
			treeSecond->Delete(node2);
		} while (++listMarker);
		// delete Primitive
		delete list;
		delete temp->value;
		treeFirst->Delete(temp);
	}

	void DeleteReq(const int index, const ID& key) {
		PairTree<ID, Req, Prim>* treeSecond = data[index]->treeReq;
		PairNode<ID, Prim, Req>* node1;
		PairNode<ID, Req, Prim>* node2;

		node2 = treeSecond->GetNode(key);
		if (node2 == nullptr) {
			return;
		}

		List<PairNode<ID, Prim, Req>*>* listReqOnPrim = node2->list;
		auto listMarkerReq = listReqOnPrim->GetMarker();

		do
		{
			node1 = listMarkerReq.GetValue();
			// Clearing link on this Req
			List<PairNode<ID, Req, Prim>*>* listPrimOnReq = node1->list;
			auto listMarkerPrim = listPrimOnReq->GetMarker();

			do
			{
				if (node2 == listMarkerPrim.GetValue()) {
					listMarkerPrim.DeleteCurrent();

					break;
				}
			} while (++listMarkerPrim);
		} while (++listMarkerReq);
		// delete Requariments

		delete listReqOnPrim;
		delete node2->value;
		treeSecond->Delete(node2);
	}
public:
	Data() {
		dict = new BinSearchTree<ID, Prim>;
	}
	~Data() {}

	class GMarker
	{
	private:
		PairTree<ID, Prim, Req>::PairMarker marker;
		Data* graph;
		int index;
		bool isValid;
	public:
		GMarker(Data* _graph) : graph(_graph) {
			MoveBegin();
		}
		GMarker(Data* _graph, PairTree<ID, Prim, Req>::PairMarker _marker) : graph(_graph), marker(_marker) {
			this->isValid = marker.IsValid();
		}

		Prim GetValue() const {
			if (!isValid) {
				throw std::exception("Marker was not valid");
			}
			return marker.GetValue();
		}


		const ID& Getkey() {
			if (!isValid) {
				throw std::exception("Marker was not valid");
			}
			return marker.GetKey();
		}

		List<PairNode<ID, Req, Prim>*>* GetList() {
			if (!isValid) {
				throw std::exception("Marker was not valid");
			}
			return marker.GetList();
		}

		void GetReqs(Array<Req>& reqs) {
			if (!isValid) {
				throw std::exception("Marker was not valid");
			}
			List<PairNode<ID, Req, Prim>*>* list = marker.GetList();
			auto listMarker = list->GetMarker();
			do
			{
				reqs.PushBack(listMarker.GetValue()->value);
			} while (++listMarker);
		}

		bool MoveNext() {
			if (!isValid) {
				return false;
			}
			if (++marker) {
				return true;
			}
			else {
				++index;
				if (index >= graph->GetSize()) {
					return false;
				}
				marker = graph->GetPairMarker(index);
				return true;
			}
		}

		void MoveBegin() {
			index = 0;
			marker = graph->GetPairMarker(index);
			if (marker.IsValid()) {
				isValid = true;
			}
		}

		// REWRITE!!
		// REWRITE!!!
		void DeleteCurrent() {
			if (!isValid) {
				throw std::exception("Marker was not valid");
			}
			isValid = false;
			marker.DeleteCurrent();
		}

		int GetIndex() const {
			return index;
		}
	};

	BinSearchTree<ID, Prim>* dict;

	size_t GetSize() const {
		return data.GetSize();
	}

	PairTree<ID, Prim, Req>::PairMarker GetPairMarker(int index) {
		return data[index]->treePrim->GetPairMarker();
	}

	GMarker* GetMarker() {
		return new GMarker(this);
	}

	GMarker Find(int index, const ID& key) {
		auto marker = data[index]->treePrim->FindPair(key);
		return GMarker(this, marker);
	}

	void GetRequirementsByPrim(int index, const ID& IDPrim, Array<Req>& arrayReq) {
		PairNode<ID, Prim, Req>* node = data[index]->treePrim->GetNode(IDPrim);
		if (node == nullptr) {
			return;
		}
		auto marker =  node->list->GetMarker();
		do
		{
			arrayReq.PushBack(marker.GetValue()->value);
		} while (++marker);
	}

	void GetIDRequirementsByPrim(int index, const ID& IDPrim, Array<ID>& arrayReq) {
		PairNode<ID, Prim, Req>* node = data[index]->treePrim->GetNode(IDPrim);
		if (node == nullptr) {
			return;
		}
		auto marker = node->list->GetMarker();
		do
		{
			arrayReq.PushBack(marker.GetValue()->key);
		} while (++marker);
	}

	void DeleteComponent(const ID& id) {
		Queue<Node<ID, Prim>*> primQueue;
		Queue<Node<ID, Req>*> reqQueue;
		primQueue.push(data[id.index]->treePrim->GetNode());
		reqQueue.push(data[id.index]->treeReq->GetNode());
		while (!primQueue.isEmpty())
		{
			Node<ID, Prim>* node = primQueue.pop();
			if (node->left != nullptr) {
				primQueue.push(node->left);
			}
			if (node->right != nullptr) {
				primQueue.push(node->right);
			}
			delete node->value;
		}
		while (!reqQueue.isEmpty())
		{
			Node<ID, Req>* node = reqQueue.pop();
			if (node->left != nullptr) {
				reqQueue.push(node->left);
			}
			if (node->right != nullptr) {
				reqQueue.push(node->right);
			}
			delete node->value;
		}
		delete data[id.index];
		data.Erase(id.index);
	}

	void DeletePrimitive(const ID& key) {
		auto marker = data[key.index]->treePrim->Find(key);
		Primitive* primitive = marker.GetValue();
		if (primitive->GetType() == point_t) {
			Point* point = dynamic_cast<Point*>(primitive);
			if (point->GetParent() != nullptr) {
				DeletePrim(point->GetParent()->GetID().index, point->GetParent()->GetID());
			}
		}
		DeletePrim(key.index, key);
		SplitingAndBFS(key.index);
	}

	void DeleteRequirement(const ID& key) {
		DeleteReq(key.index, key);
		SplitingAndBFS(key.index);
	}

	void Add(Array<ID>& keys, Array<Prim>& elements, ID& key, Req value) {
		// Component* component;
		bool newComponent = true;
		bool* components = new bool[data.GetSize()];
		for (int i = 0; i < data.GetSize(); ++i) {
			components[i] = false;
		}

		for (int i = 0; i < keys.GetSize(); ++i) {
			// keys[i].index = -1 - new element
			// keys[i].index >= 0 - it was in components
			if (keys[i].index >= 0) {
				components[keys[i].index] = true;
				newComponent = false;
			}
		}

		if (newComponent) {
			CreateNewComponent(keys, elements, key, value);
			return;
		}
		// find bigest component
		int bigestComponent;
		int maxSize = 0;
		for (int i = 0; i < data.GetSize(); ++i) {

			if (maxSize < data[i]->treePrim->GetSize()) {
				maxSize = data[i]->treePrim->GetSize();
				bigestComponent = i;
			}
		}
		// pushing link on new Req and Prim
		PairNode<ID, Req, Prim>* nodeReq = new PairNode<ID, Req, Prim>(key, value);
		nodeReq->list = new List<PairNode<ID, Prim, Req>*>;
		data[bigestComponent]->treeReq->Add(nodeReq);
		// creating link
		for (int i = 0; i < elements.GetSize(); ++i) {
			if (keys[i].index >= 0) {
				PairNode<ID, Prim, Req>* nodePrim;

				nodePrim = data[keys[i].index]->treePrim->GetNode(keys[i]);

				nodePrim->list->PushTail(nodeReq);
				nodeReq->list->PushTail(nodePrim);
				keys[i].index = bigestComponent;
			}
		}
		// pushing new node
		for (int i = 0; i < elements.GetSize(); ++i) {
			if (keys[i].index < 0) {
				// remove from dictionary
				dict->Find(keys[i]).DeleteCurrent();
				// 
				PairNode<ID, Prim, Req>* nodePrim = new PairNode<ID, Prim, Req>(key, elements[i]);
				nodePrim->list = new List<PairNode<ID, Req, Prim>*>;
				nodePrim->list->PushTail(nodeReq);
				nodeReq->list->PushTail(nodePrim);
				data[bigestComponent]->treePrim->Add(nodePrim);
				keys[i].index = bigestComponent;
			}
		}
		// merging
		for (int i = data.GetSize() - 1; i > 0; --i) {
			if (components[i]) {
				if (i != bigestComponent) {
					data[bigestComponent]->treePrim->Merge(data[i]->treePrim);
					data[bigestComponent]->treeReq->Merge(data[i]->treeReq);
					delete data[i];
					data.Erase(i);
				}
			}
		}

	}

	void UploadingDataPrim(const ID& key, Array<Prim>& prims) {
		if (key.index >= data.GetSize()) {
			return;
		}
		PairTree<ID, Prim, Req>::PairMarker marker = data[key.index]->treePrim->GetPairMarker();
		do
		{
			prims.PushBack(marker.GetValue());
		} while (++marker);
		return;
	}

	void UploadingDataReq(const ID& key, Array<Req>& Reqs) {
		if (key.index >= data.GetSize()) {
			return;
		}
		PairTree<ID, Req, Prim>::PairMarker marker = data[key.index]->treeReq->GetPairMarker();
		do
		{
			Reqs.PushBack(marker.GetValue());
		} while (++marker);
		return;
	}
};
#endif