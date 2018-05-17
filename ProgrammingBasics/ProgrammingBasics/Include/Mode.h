#pragma once

#include "Presenter.h"
#include "IView.h"
#include "Model.h"

enum Event

{
	ev_createPoint = 1,
	ev_createSegment,
	ev_createArc,
	ev_createCircle,
	// 4
	ev_transform,
	// 9
	ev_del,
	ev_delReq,
	// 11
	ev_leftMouseClick,
	ev_rightMouseClick,

	// new events
	ev_leftMouseDown,
	ev_rightMouseDown,
	ev_leftMouseUp,
	ev_rightMouseUp,
	ev_mouseMove,
	ev_escape,
	ev_ctrlDown,
	ev_ctrlUp,
	//end new events

	ev_save
	// 14
};

class Mode {
protected:
	static Presenter* presenter;
	Event lastEvent;

	Mode* UnexpectedEvent(const Event e) {
		this->Cancel();
		switch (e) {
		case ev_createPoint: {
			return new CreatingPoint(presenter);
		}
		case ev_createArc: {
			return new CreatingArc(presenter);
		}
		case ev_createSegment: {
			return new CreatingSegment(presenter);
		}
		case ev_createCircle: {
			return new CreatingCircle(presenter);
		}
		}
	}
public:
	Mode(Presenter* _pres) {
		if (_pres == nullptr) {
			throw std::exception("Invalid argument. Presenter was nullptr");
		}
		presenter = _pres;
	}

	virtual Mode* HandleEvent(const Event, Array<double>&) = 0;
	virtual bool DrawMode() { }
	virtual void Cancel() { }
};

class CreatingSegment : public Mode {
private:
	enum State { noClick, oneClick };
	State state;
	Array<double> segmentParameters;
public:
	CreatingSegment(Presenter* _pres) : Mode(_pres), segmentParameters(4) {
		state = noClick;
	}
	Mode* HandleEvent(const Event ev, Array<double>& params) {
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
				id = presenter->CreateObject(segment_t, segmentParameters);

				Array<ID> selectedObjects(1);
				selectedObjects[0] = id;
				return new Selection(selectedObjects, presenter);
			}
		}
		return UnexpectedEvent(ev);
	}
};

class CreatingPoint : public Mode {
public:
	CreatingPoint(Presenter* _pres) : Mode(_pres) {}
	Mode* HandleEvent(const Event ev, Array<double>& params) {
		if (ev == ev_leftMouseClick) {
			if (params.GetSize() != 2) {
				throw std::exception("Bad number of parameters");
			}

			ID id = presenter->CreateObject(point_t, params);
			Array<ID> selectedObjects(1);
			selectedObjects[0] = id;
			return new Selection(selectedObjects, presenter);
		}
		return UnexpectedEvent(ev);
	}
};

class CreatingCircle : public Mode {
private:
	enum State { noClick, oneClick };
	State state;
	Array<double> CircleParameters;
public:
	CreatingCircle(Presenter* _pres) : Mode(_pres), CircleParameters(4) {
		state = noClick;
	}
	Mode* HandleEvent(const Event ev, Array<double>& params) {
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

				ID id = presenter->CreateObject(circle_t, CircleParameters);

				Array<ID> selectedObjects(1);
				selectedObjects[0] = id;
				return new Selection(selectedObjects, presenter); 
			}
		}
		
		return this->UnexpectedEvent(ev);
	}
};

class CreatingArc : public Mode {
private:
	enum State { noClick, oneClick, twoClick};
	State state;
	Array<double> arcParameters;
public:
	CreatingArc(Presenter* _pres) : Mode(_pres), arcParameters(6) {
		state = noClick;
	}
	Mode* HandleEvent(const Event ev, Array<double>& params) {
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

				ID id = presenter->CreateObject(circle_t, arcParameters);

				Array<ID> selectedObjects(1);
				selectedObjects[0] = id;
				return new Selection(selectedObjects, presenter);
			}
		}

		return this->UnexpectedEvent(ev);
	}
};

class Selection : public Mode {
private:
	Array<ID> selectedObject;
	enum State {single_selection, poly_selection};
	State state;

	void AddObject(const ID& obj) {
		for (int i = 0; i < selectedObject.GetSize(); ++i) {
			if (selectedObject[i] == obj) {
				selectedObject.EraseO_1_(i);
				return;
			}
		}
		selectedObject.PushBack(obj);
	}

public:
	// must take containers in constructor
	Selection(Presenter* _pres) : Mode(_pres), selectedObject(1) {
		state = single_selection;
	}
	Selection(Array<ID> _selObjects, Presenter* _pres) : Mode(_pres), selectedObject(_selObjects) {
		if (selectedObject.GetSize() == 0) {
			selectedObject = Array<ID>(1);
		}
		state = single_selection;
	}

	Mode* HandleEvent(const Event e, Array<double>& params) {

		if (e == ev_leftMouseClick) {
			if (params.GetSize() != 2) {
				throw std::exception("Bad number of parameters");
			}
			ID obj;
			bool isFound = presenter->GetObject(params[0], params[1], obj);
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
			return new Redaction(selectedObject, presenter);
		}

		return UnexpectedEvent(e);
	}
};

class Control {
protected:
	Vector2 center;
public:
	virtual bool IsClicked(double, double);
};

class RotationControl : public Control {
private:

public:
};

class Redaction : public Mode {
private:
	Array<ID> selectedObjects;
public:
	// must take containers in constructor
	Redaction(Array<ID> _selecObj, Presenter* _pres) : Mode(_pres),
		selectedObjects(_selecObj)
	{}

	Mode* HandleEvent(const Event, Array<double>&);
};

class RedactionReq : public Mode {
private:
	Array<ID> selectedObjects;
	Array<ID> Reqs;
	ID selectedReq;
	Array<ID> objectsOfreq;
public:
	// must take containers in constructor
	RedactionReq(Array<ID> _selecObj, Presenter* _pres) : Mode(_pres),
		selectedObjects(_selecObj)
	{
		presenter->GetRequirements(selectedObjects[0]);
	}

	Mode* HandleEvent(const Event, Array<double>&);
};