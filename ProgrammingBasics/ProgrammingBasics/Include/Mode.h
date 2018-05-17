#ifndef __MODE
#define __MODE

#include "Vector2.h"

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

	void AddObject(const ID& obj);
public:
	Selection();
	Selection(Array<ID> _selObjects);

	Mode* HandleEvent(const Event e, Array<double>& params);

	bool DrawMode();

	void Cancel();
};

class CreatingSegment : public Mode {
private:
	enum State {
		noClick,
		oneClick
	};
	State state;
	Array<double> segmentParameters;
public:
	CreatingSegment();
	Mode* HandleEvent(const Event, Array<double>&);

	bool DrawMode();

	void Cancel();
};

class CreatingPoint : public Mode {
public:
	CreatingPoint() {}
	Mode* HandleEvent(const Event, Array<double>&);

	bool DrawMode();

	void Cancel();
};

class CreatingCircle : public Mode {
private:
	enum State { noClick, oneClick };
	State state;
	Array<double> CircleParameters;
public:
	CreatingCircle();
	Mode* HandleEvent(const Event, Array<double>&);
	bool DrawMode();
	void Cancel();
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

class Control {
protected:
	Vector2 center;
public:
	virtual bool IsClicked(double, double) = 0;
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