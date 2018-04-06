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

int HyperGraph::Search(ID& _id) {

	return -1;
}