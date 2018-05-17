#include "Mode.h"
#include "Presenter.h"

Mode* Mode::UnexpectedEvent(const Event e) {
	this->Cancel();
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
	}
}

CreatingSegment::CreatingSegment() : segmentParameters(4) {
	state = noClick;
}

Mode* CreatingSegment::HandleEvent(const Event ev, Array<double>& params) {
	if (ev == ev_leftMouseClick) {
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
			//return new Selection(selectedObjects);
		}
	}
	return UnexpectedEvent(ev);
}

Mode* CreatingPoint::HandleEvent(const Event ev, Array<double>& params) {
	if (ev == ev_leftMouseClick) {
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

CreatingCircle::CreatingCircle() : CircleParameters(4) {
	state = noClick;
}

Mode* CreatingCircle::HandleEvent(const Event ev, Array<double>& params) {
	if (ev == ev_leftMouseClick) {
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
			return nullptr;
		}
		// if it was one click
		// then create a circle
		// and turn to single selection mode
		// with selected circle
		if (state == oneClick) {

			CircleParameters[2] = params[0];
			CircleParameters[3] = params[1];

			ID id = Presenter::CreateObject(circle_t, CircleParameters);

			Array<ID> selectedObjects(1);
			selectedObjects[0] = id;
			return new Selection(selectedObjects);
		}
	}

	return this->UnexpectedEvent(ev);
}

CreatingArc::CreatingArc() : arcParameters(6) {
	state = noClick;
}

Mode* CreatingArc::HandleEvent(const Event ev, Array<double>& params) {
	if (ev == ev_leftMouseClick) {
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

			ID id = Presenter::CreateObject(circle_t, arcParameters);

			Array<ID> selectedObjects(1);
			selectedObjects[0] = id;
			return new Selection(selectedObjects);
		}
	}

	return this->UnexpectedEvent(ev);
}

Mode* Selection::HandleEvent(const Event e, Array<double>& params) {
	if (e == ev_leftMouseClick) {
		if (params.GetSize() != 2) {
			throw std::exception("Bad number of parameters");
		}
		ID obj;
		bool isFound = Presenter::GetObject(params[0], params[1], obj);
		if (isFound) {
			if (state == single_selection) {
				selectedObject.Clear();
				selectedObject[0] = obj;
				return nullptr;
			}

			if (state == poly_selection) {
				AddObject(obj);
				return nullptr;
			}
		}
		else {
			selectedObject.Clear();
			return nullptr;
		}
	}
	if (e == ev_ctrlDown) {
		state = poly_selection;
		return nullptr;
	}
	if (e == ev_ctrlUp) {
		state = single_selection;
		return nullptr;
	}
	if (e == ev_escape) {
		selectedObject.Clear();
		return nullptr;
	}
	if (e == ev_transform) {
		if (selectedObject.GetSize() == 0) {
			return nullptr;
		}
		return new Redaction(selectedObject);
	}
	return UnexpectedEvent(e);
}

Selection::Selection(Array<ID> _selObjects) : Mode(), selectedObject(_selObjects) {
	if (selectedObject.GetSize() == 0) {
		selectedObject = Array<ID>(1);
	}
	state = single_selection;
}

Selection::Selection() : Mode(), selectedObject(1) {
	state = single_selection;
}

Redaction::Redaction(Array<ID> _selecObj) : selectedObjects(_selecObj)
{ }

