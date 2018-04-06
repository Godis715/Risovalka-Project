<<<<<<< Updated upstream
#include "HyperGraph.h"

bool HyperGraph::Component::Search(ID& id)
{
	if (dataPrimitive.Find(id))
	{
		return true;
	}
	else if (dataRequirement.Find(id))
	{
		return true;
	}
	else
	{
		return false;
	}
}

Array<double*> HyperGraph::Component::GetParams()
{
	Array<double*> output;
	dataPrimitive.MoveHead();
	do
	{
		switch (dataPrimitive.GetCurrent()->GetType())
		{
			case point:
			{
				Point* point = dynamic_cast<Point*>(dataPrimitive.GetCurrent());
				output.pushBack(&point->position.x);
				output.pushBack(&point->position.y);
				return true;
				break;
			}
			case arc:
			{
				Arc* arc = dynamic_cast<Arc*>(dataPrimitive.GetCurrent());
				output.pushBack(&arc->angle);
				return true;
				break;
			}
		}
	} while (dataPrimitive.MoveNext());
	return output;
}

double HyperGraph::Component::GetError()
{
	dataRequirement.MoveHead();
	double error = 0;
	do
	{
		error += dataRequirement.GetCurrent()->error();

	} while (dataRequirement.MoveNext());
	return error;
=======
#include "HyperGraph.h"

HyperGraph::Component::Component(ID _id) : id(_id){}

bool HyperGraph::Component::Search(ID& id)
{
	if (dataPrimitive.Find(id))
	{
		return true;
	}
	else if (dataRequirement.Find(id))
	{
		return true;
	}
	else
	{
		return false;
	}
}

Array<double*> HyperGraph::Component::GetParams()
{
	Array<double*> output;
	dataPrimitive.MoveHead();
	do
	{
		switch (dataPrimitive.GetCurrent()->GetType())
		{
			case point:
			{
				Point* point = dynamic_cast<Point*>(dataPrimitive.GetCurrent());
				output.pushBack(&point->position.x);
				output.pushBack(&point->position.y);
				return true;
				break;
			}
			case arc:
			{
				Arc* arc = dynamic_cast<Arc*>(dataPrimitive.GetCurrent());
				output.pushBack(&arc->angle);
				return true;
				break;
			}
		}
	} while (dataPrimitive.MoveNext());
	return output;
}

double HyperGraph::Component::GetError()
{
	dataRequirement.MoveHead();
	double error = 0;
	do
	{
		error += dataRequirement.GetCurrent()->error();

	} while (dataRequirement.MoveNext());
	return error;
>>>>>>> Stashed changes
}

bool HyperGraph::Component::Delete(ID& _id) {

	if (dataRequirement.Find(_id)) {
		delete dataRequirement.GetCurrent();
		dataRequirement.Erase(_id);
		return true;
	}

	if (dataPrimitive.Find(_id)) {
		Primitive* primitive = dataPrimitive.GetCurrent();
		dataRequirement.MoveBegin();
		do
		{
			if (dataRequirement.GetCurrent()->Contains(_id)) {
				delete dataRequirement.GetCurrent();
				dataRequirement.Erase(_id);
			}
		} while (dataRequirement.MoveNext());
		switch (primitive->GetType())
		{
		case point: {
			dataPrimitive.MoveBegin();
			do
			{
				if (dataPrimitive.GetCurrent()->GetType() == segment) {
					Segment* seg = dynamic_cast<Segment*>(dataPrimitive.GetCurrent());
					if ((seg->GetPoint1_ID() == primitive->GetID()) || (seg->GetPoint2_ID() == primitive->GetID())) {
						dataPrimitive.Erase(primitive->GetID());
						dataPrimitive.Erase(seg->GetID());
						delete primitive;
						delete seg;
						return true;
					}
				}
				if (dataPrimitive.GetCurrent()->GetType() == arc) {
					Segment* _arc = dynamic_cast<Segment*>(dataPrimitive.GetCurrent());
					if ((_arc->GetPoint1_ID() == primitive->GetID()) || (_arc->GetPoint2_ID() == primitive->GetID())) {
						dataPrimitive.Erase(primitive->GetID());
						dataPrimitive.Erase(_arc->GetID());
						delete dynamic_cast<Point*>(primitive);
						delete _arc;
						return true;
					}
				}
			} while (dataPrimitive.MoveNext());
			return true;
		}
		case segment: {
			dataPrimitive.Erase(primitive->GetID());
			delete dynamic_cast<Segment*>(primitive);
			return true;
		}
		case arc: {
			dataPrimitive.Erase(primitive->GetID());
			delete dynamic_cast<Arc*>(primitive);
			return true;
		}
		default:
			break;
		}
	}
	return false;
}

bool HyperGraph::Search(ID _id, ID& component) {
	components.MoveBegin();
	do {
		if (components.GetCurrent()->Search(_id)) {
			component = components.GetCurrentKey();
			return;
		}
	} while (components.MoveNext());
}

int HyperGraph::GetSize() {
	return components.GetSize();
}

<<<<<<< Updated upstream
	return -1;
}

void HyperGraph::DeleteComponent(ID id)
{
	//
}

void HyperGraph::MergeComponents(Array<ID> idComponets)
{
	components.Find(idComponets[0]);
	Component* input = components.GetCurrent();
	for (int i = 1; i < idComponets.getSize(); i++)
	{
		components.Find(idComponets[i]);
		components.GetCurrent()->dataPrimitive.MoveHead();
		do
		{
			input->dataPrimitive.Add(components.GetCurrent()->dataPrimitive.GetCurrentKey(),
				components.GetCurrent()->dataPrimitive.GetCurrent()
			);
		} while (components.GetCurrent()->dataPrimitive.MoveNext());
		components.GetCurrent()->dataPrimitive.DeleteDict();

		components.GetCurrent()->dataRequirement.MoveHead();
		do
		{
			input->dataRequirement.Add(components.GetCurrent()->dataRequirement.GetCurrentKey(),
				components.GetCurrent()->dataRequirement.GetCurrent()
			);
		} while (components.GetCurrent()->dataRequirement.MoveNext());
		components.GetCurrent()->dataRequirement.DeleteDict();
		components.Erase(idComponets[i]);
	}
	
=======
void HyperGraph::Add(IRequirement* requirement, Array<Primitive*>& primitives) {
	Array<ID> IDArrray(primitives.getSize());
	int maxComponent = 0;
	int tempMax;
	ID componentID;
	for (int i = 0; i < primitives.getSize(); ++i) {
		if (Search(primitives[i]->GetID(), componentID)) {
			tempMax = components.GetCurrent()->dataPrimitive.GetSize();
			IDArrray.pushBack(componentID);
			if (tempMax > maxComponent) {
				maxComponent = tempMax;
				IDArrray.swap(0, IDArrray.getSize() - 1);
			}
		}
	}
	if (IDArrray.getSize() > 0) {
		MergeComponents(IDArrray);
		components.Find(IDArrray[0]);
		for (int i = 0; i < primitives.getSize(); ++i) {
			components.GetCurrent()->dataPrimitive.Add(primitives[i]->GetID(), primitives[i]);
		}
		components.GetCurrent()->dataRequirement.Add(requirement->GetID(), requirement);
		return;
	}
	Component* component = new Component(IDGenerator::getInstance()->generateID());
	for (int i = 0; i < primitives.getSize(); ++i) {
		component->dataPrimitive.Add(primitives[i]->GetID(), primitives[i]);
	}
	component->dataRequirement.Add(requirement->GetID(), requirement);
	components.Add(component->GetID, component);
>>>>>>> Stashed changes
}