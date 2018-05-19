#include "Mode.h"
#include "Presenter.h"


Mode* Mode::UnexpectedEvent(const Event e) {
	switch (e) {
	case ev_createPoint: {
		return new CreatingPoint();
	}
	case ev_createArc: {
		return new CreatingArc();
	}
	case ev_createSegment: {
		return new CreatingSegment();
	}
	case ev_createCircle: {
		return new CreatingCircle();
	}
	case ev_mouseMove:
		return nullptr;
	case ev_ctrlDown:
		return nullptr;
	case ev_ctrlUp:
		return nullptr;
	default:
		return new Selection();
	}
}

// SEGMENT

CreatingSegment::CreatingSegment() : segmentParameters(4) {
	state = noClick;
}

Mode* CreatingSegment::HandleEvent(const Event ev, Array<double>& params) {
	if (ev == ev_leftMouseDown) {
		if (params.GetSize() != 2) {
			throw std::exception("Bad number of parameters");
		}
		// if it were no clicks
		// then create one point and change the state
		// to one click
		if (state == noClick) {

			segmentParameters[0] = params[0];
			segmentParameters[1] = params[1];

			state = oneClick;
			//for draw mode
			infoMode.x = params[0];
			infoMode.y = params[1];
			return nullptr;
		}

		// if it was one click
		// then create a segment
		// and turn to single selection mode
		// with selected segment
		if (state == oneClick) {

			segmentParameters[2] = params[0];
			segmentParameters[3] = params[1];

			ID id;
			id = Presenter::CreateObject(segment_t, segmentParameters);

			Array<ID> selectedObjects(1);
			selectedObjects[0] = id;
			return new Selection(selectedObjects);
		}
	}
	if (ev == ev_mouseMove)
	{
		if (params.GetSize() != 2) {
			throw std::exception("Bad number of parameters");
		}

		if (state == noClick) {
			return nullptr;
		}

		if (state == oneClick) {
			infoMode.x = params[0];
			infoMode.y = params[1];
			return nullptr;
		}
	}
	return UnexpectedEvent(ev);
}

void CreatingSegment::DrawMode() {
	if (state == oneClick)
	{
		Presenter::GetView()->SetColor(red);
		Presenter::GetView()->DrawPoint(Vector2(segmentParameters[0], segmentParameters[1]));
		Presenter::GetView()->SetColor(yellow);
		Presenter::GetView()->DrawLine(Vector2(segmentParameters[0], segmentParameters[1]), infoMode, points);
	}
}

CreatingSegment::~CreatingSegment() {
	segmentParameters.Clear();
	state = noClick;
}

// POINT

Mode* CreatingPoint::HandleEvent(const Event ev, Array<double>& params) {
	if (ev == ev_leftMouseDown) {
		if (params.GetSize() != 2) {
			throw std::exception("Bad number of parameters");
		}

		ID id = Presenter::CreateObject(point_t, params);
		Array<ID> selectedObjects(1);
		selectedObjects[0] = id;
		return new Selection(selectedObjects);
	}
	return UnexpectedEvent(ev);
}

void CreatingPoint::DrawMode() {
}

// CIRCLE
CreatingCircle::CreatingCircle() : CircleParameters(3) {
	state = noClick;
}

Mode* CreatingCircle::HandleEvent(const Event ev, Array<double>& params) {
	if (ev == ev_leftMouseDown) {
		if (params.GetSize() != 2) {
			throw std::exception("Bad number of parameters");
		}
		// if it were no clicks
		// then create one point and change the state
		// to one click
		if (state == noClick) {

			CircleParameters[0] = params[0];
			CircleParameters[1] = params[1];

			state = oneClick;
			//for draw mode
			infoMode.x = params[0];
			infoMode.y = params[1];
			return nullptr;
		}
		// if it was one click
		// then create a circle
		// and turn to single selection mode
		// with selected circle
		if (state == oneClick) {
			CircleParameters[2] = (Vector2(params[0], params[1]) - Vector2(CircleParameters[0], CircleParameters[1])).GetLength();
			ID id = Presenter::CreateObject(circle_t, CircleParameters);

			Array<ID> selectedObjects(1);
			selectedObjects[0] = id;
			return new Selection(selectedObjects);
		}
	}
	if (ev == ev_mouseMove)
	{
		if (params.GetSize() != 2) {
			throw std::exception("Bad number of parameters");
		}
		if (state == noClick) {
			return nullptr;
		}

		if (state == oneClick) {
			infoMode.x = params[0];
			infoMode.y = params[1];
			return nullptr;
		}
	}
	return this->UnexpectedEvent(ev);
}

void CreatingCircle::DrawMode() {
	if (state == oneClick)
	{
		Presenter::GetView()->SetColor(red);
		Presenter::GetView()->DrawPoint(Vector2(CircleParameters[0], CircleParameters[1]));
		Presenter::GetView()->SetColor(yellow);
		Presenter::GetView()->DrawCircle(Vector2(CircleParameters[0], CircleParameters[1]), infoMode, points);
	}
}

CreatingCircle::~CreatingCircle() {
	CircleParameters.Clear();
}

// ARC

CreatingArc::CreatingArc() : arcParameters(6) {
	state = noClick;
}

Mode* CreatingArc::HandleEvent(const Event ev, Array<double>& params) {
	if (ev == ev_leftMouseDown) {
		if (params.GetSize() != 2) {
			throw std::exception("Bad number of parameters");
		}
		// if it were no clicks
		// then create one point and change the state
		// to one click
		if (state == noClick) {

			arcParameters[0] = params[0];
			arcParameters[1] = params[1];

			state = oneClick;
			//for draw mode
			infoMode.x = params[0];
			infoMode.y = params[1];
			return nullptr;
		}
		// if it were one clicks
		// then create one point and change the state
		// to two click
		if (state == oneClick) {

			arcParameters[2] = params[0];
			arcParameters[3] = params[1];

			state = twoClick;
			return nullptr;
		}
		// if it was two click
		// then create a arc
		// and turn to single selection mode
		// with selected arc
		if (state == twoClick) {

			arcParameters[4] = params[0];
			arcParameters[5] = params[1];

			ID id = Presenter::CreateObject(arc_t, arcParameters);

			Array<ID> selectedObjects(1);
			selectedObjects[0] = id;
			return new Selection(selectedObjects);
		}
	}
	if (ev == ev_mouseMove)
	{
		if (params.GetSize() != 2) {
			throw std::exception("Bad number of parameters");
		}
		if (state == noClick) {
			return nullptr;
		}

		if (state == oneClick || state == twoClick) {
			infoMode.x = params[0];
			infoMode.y = params[1];
			return nullptr;
		}
	}
	return this->UnexpectedEvent(ev);
}

void CreatingArc::DrawMode() {
	if (state == oneClick)
	{
		Presenter::GetView()->SetColor(red);
		Presenter::GetView()->DrawPoint(Vector2(arcParameters[0], arcParameters[1]));

		Presenter::GetView()->SetColor(yellow);
		Presenter::GetView()->DrawCircle(Vector2(arcParameters[0], arcParameters[1]), infoMode, points);
	}
	if (state == twoClick)
	{
		Presenter::GetView()->SetColor(red);
		Presenter::GetView()->DrawPoint(Vector2(arcParameters[0], arcParameters[1]));

		Presenter::GetView()->SetColor(yellow);
		Presenter::GetView()->DrawCircle(Vector2(arcParameters[0], arcParameters[1]), Vector2(arcParameters[2], arcParameters[3]), points);
		
		Presenter::GetView()->SetColor(red);
		Presenter::GetView()->DrawPoint(Vector2(arcParameters[2], arcParameters[3]));
		
		Presenter::GetView()->SetColor(yellow);
		Presenter::GetView()->DrawArc(Vector2(arcParameters[0], arcParameters[1]), Vector2(arcParameters[2], arcParameters[3]), infoMode, line);
	}
}

CreatingArc::~CreatingArc() {
	arcParameters.Clear();
}

// SELECTION

Selection::Selection(Array<ID> _selObjects) : Mode(), selectedObject(_selObjects) {
	if (selectedObject.GetSize() == 0) {
		selectedObject = Array<ID>(1);
	}
	state = single_selection;
}

Selection::Selection() : Mode(), selectedObject(1) {
	state = single_selection;
}

Selection::~Selection() {
	selectedObject.Clear();
}

void Selection::AddObject(const ID& obj) {
	for (int i = 0; i < selectedObject.GetSize(); ++i) {
		if (selectedObject[i] == obj) {
			selectedObject.EraseO_1_(i);
			return;
		}
	}
	selectedObject.PushBack(obj);
}

Mode* Selection::HandleEvent(const Event e, Array<double>& params) {
	if (e == ev_leftMouseDown) {
		if (params.GetSize() != 2) {
			throw std::exception("Bad number of parameters");
		}
		ID obj;
		bool isFound = Presenter::GetObject(params[0], params[1], obj);
		if (isFound) {
			if (state == single_selection) {
				selectedObject.Clear();
				selectedObject.PushBack(obj);
				return nullptr;
			}

			if (state == poly_selection) {
				AddObject(obj);
				return nullptr;
			}
		}
		else {
			if (state != poly_selection)
			{
				selectedObject.Clear();
			}
			return nullptr;
		}
	}
	switch (e)
	{
	case ev_ctrlDown: {
		state = poly_selection;
		return nullptr;
	}
	case ev_ctrlUp: {
		state = single_selection;
		return nullptr;
	}
	case ev_escape: {
		selectedObject.Clear();
		return nullptr;
	}
	case ev_transform: {
		if (selectedObject.GetSize() == 0) {
			return nullptr;
		}
		return new Redaction(selectedObject);
	}
	case ev_del: {
		Presenter::DeletePrimitives(selectedObject);
		return nullptr;
	}
	default:
		return UnexpectedEvent(e);
	}
}

void Selection::DrawMode()
{
	for (int i = 0; i < selectedObject.GetSize(); i++)
	{
		Array<double> params;
		object_type type;

		Presenter::GetObjParam(selectedObject[i], params);
		Presenter::GetObjType(selectedObject[i], type);

		switch (type)
		{
		case point_t:
			Presenter::GetView()->SetColor(green);
			Presenter::GetView()->DrawPoint(Vector2(params[0], params[1]));
			break;
		case segment_t:
			Presenter::GetView()->SetColor(green);
			Presenter::GetView()->DrawLine(Vector2(params[0], params[1]),
				Vector2(params[2], params[3]), line);
			break;
		case arc_t:
			Presenter::GetView()->SetColor(green);
			Presenter::GetView()->DrawArc(Vector2(params[0], params[1]),
				Vector2(params[2], params[3]),
				Vector2(params[4], params[5]), line);
			break;
		case circle_t:
			Presenter::GetView()->SetColor(green);
			Presenter::GetView()->DrawCircle(Vector2(params[0], params[1]),
				Vector2(params[0] + params[2], params[1]), line);
			break;
		}
	}
}

// REDACTION

Redaction::Redaction(Array<ID> _selecObj) : selectedObjects(_selecObj)
{}

Redaction::~Redaction() {
	selectedObjects.Clear();
}

Mode* Redaction::HandleEvent(const Event, Array<double>&) { return nullptr; }

void Redaction::DrawMode() {

}

// REDACTION_REQ

RedactionReq::RedactionReq(ID _selecObj) : selectedPrim(_selecObj) {
	Presenter::GetComponent(selectedPrim, objects, reqs);
}

RedactionReq::RedactionReq() { }

RedactionReq::~RedactionReq() {
	objects.Clear();
	reqs.Clear();
	objectsOfreq.Clear();
}

Mode* RedactionReq::HandleEvent(const Event ev, Array<double>& param) {
	return nullptr;
}

void RedactionReq::DrawMode() {

}