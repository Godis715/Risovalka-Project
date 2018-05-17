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
	ev_clockOnReq,
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
	~Selection();

	Mode* HandleEvent(const Event e, Array<double>& params);

	bool DrawMode();
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
	~CreatingSegment();

	Mode* HandleEvent(const Event, Array<double>&);

	bool DrawMode();
};

class CreatingPoint : public Mode {
public:
	CreatingPoint() {}
	Mode* HandleEvent(const Event, Array<double>&);

	bool DrawMode();
};

class CreatingCircle : public Mode {
private:
	enum State { noClick, oneClick };
	State state;
	Array<double> CircleParameters;
public:
	CreatingCircle();
	~CreatingCircle();

	Mode* HandleEvent(const Event, Array<double>&);
	bool DrawMode();
};

class CreatingArc : public Mode {
private:
	enum State { noClick, oneClick, twoClick};
	State state;
	Array<double> arcParameters;
public:
	CreatingArc();
	~CreatingArc();
	Mode* HandleEvent(const Event, Array<double>&);

	bool DrawMode();
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
	~Redaction();

	Mode* HandleEvent(const Event, Array<double>&);

	bool DrawMode();
};

class RedactionReq : public Mode {
private:
	Array<ID> objects;
	Array<ID> reqs;
	ID selectedReq;
	ID selectedPrim;
	Array<ID> objectsOfreq;
public:
	RedactionReq(ID _selecObj);
	RedactionReq();
	~RedactionReq();

	Mode* HandleEvent(const Event, Array<double>&);

	bool DrawMode();
};

#endif // !__MODE