#include "HyperGraph.h"

bool HyperGraph::Component::Search(ID& id)
{
	if (dataPrimitive.find(id))
	{
		return true;
	}
	else if (dataRequirement.find(id))
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