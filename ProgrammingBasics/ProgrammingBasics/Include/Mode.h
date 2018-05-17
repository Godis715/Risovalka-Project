#ifndef __MODE
#define __MODE

#include "Array.h"

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
	ev_ctrlDown,
	ev_ctrlUp,
	ev_escape,
	ev_ctrlDown,
	ev_ctrlUp,
	//end new events

	ev_save
	// 14
};

class Mode {
protected:
	Event lastEvent;

	Mode* UnexpectedEvent(const Event e);

public:

	//Mode(Presenter* _pres) {
	//	if (_pres == nullptr) {
	//		throw std::exception("Invalid argument. Presenter was nullptr");
	//	}
	//	presenter = _pres;
	//}
	Mode() {}

	virtual Mode* HandleEvent(const Event, Array<double>&) = 0;
	virtual bool DrawMode() = 0;
	virtual void Cancel() = 0;
};

class Selection : public Mode {

private:
	Array<ID> selectedObject;
	enum State { single_selection, poly_selection };
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
	Selection();

	Selection(Array<ID> _selObjects);

	Mode* HandleEvent(const Event e, Array<double>& params);

	bool DrawMode() { return true; }
	void Cancel() {}
};

class CreatingSegment : public Mode {
private:
	enum State { noClick, oneClick };
	State state;
	Array<double> segmentParameters;
public:
	CreatingSegment();
	Mode* HandleEvent(const Event, Array<double>&);

	bool DrawMode() { return true; }
	void Cancel() {}
};

class CreatingPoint : public Mode {
public:
	CreatingPoint() {}
	Mode* HandleEvent(const Event, Array<double>&);

	bool DrawMode() { return true; }
	void Cancel() {}
};

class CreatingCircle : public Mode {
private:
	enum State { noClick, oneClick };
	State state;
	Array<double> CircleParameters;
public:
	CreatingCircle();
	Mode* HandleEvent(const Event, Array<double>&);
	bool DrawMode() { return true; }
	void Cancel() {}
};


class CreatingArc : public Mode {
private:
	enum State { noClick, oneClick, twoClick};
	State state;
	Array<double> arcParameters;
public:
	CreatingArc();
	Mode* HandleEvent(const Event, Array<double>&);

	bool DrawMode() { return true; }
	void Cancel() {}
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
	Redaction(Array<ID>);

	Mode* HandleEvent(const Event, Array<double>&) { return nullptr; }

	bool DrawMode() { return true; }
	void Cancel() {}
};
/*
class RedactionReq : public Mode {
private:
	Array<ID> selectedObjects;
	Array<ID> Reqs;
	ID selectedReq;
	Array<ID> objectsOfreq;
public:
	// must take containers in constructor
	RedactionReq(Array<ID> _selecObj) : selectedObjects(_selecObj)
	{
		//presenter->GetRequirements(selectedObjects[0]);
	}

	Mode* HandleEvent(const Event, Array<double>&){}

	bool DrawMode() {}
	void Cancel() {}
};
*/
#endif // !__MODE