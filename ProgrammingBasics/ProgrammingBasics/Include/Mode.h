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
	ev_moveObjects,
	ev_scaleObjects,
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
	ev_scroll,
	ev_ctrlDown,
	ev_ctrlUp,
	ev_escape,
	ev_clockOnReq,
	ev_req_D_point,
	ev_req_Eq_Segment,
	ev_req_on_one_hand,
	ev_req_D_point_segment,
	ev_req_D_point_arc,
	ev_req_angle_segment,
	ev_input,
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
	virtual void DrawMode() { }
};

class Selection : public Mode {
private:
	Array<ID> selectedObjects;
	enum State { single_selection, poly_selection, area_selection };
	State state;

	//for area selection
	Event lastEvent;
	Vector2 infoArea1;
	Vector2 infoArea2;

	void AddObject(const ID& obj);
public:
	Selection();
	Selection(Array<ID> _selObjects);
	~Selection();

	Mode* HandleEvent(const Event e, Array<double>& params);

	void DrawMode();
};

class CreatingSegment : public Mode {
private:
	enum State {
		noClick,
		oneClick
	};
	State state;
	Array<double> segmentParameters;
	Vector2 infoMode;
public:
	CreatingSegment();
	~CreatingSegment();

	Mode* HandleEvent(const Event, Array<double>&);

	void DrawMode();
};

class CreatingPoint : public Mode {
public:
	CreatingPoint() {}
	Mode* HandleEvent(const Event, Array<double>&);

	void DrawMode();
};

class CreatingCircle : public Mode {
private:
	enum State { noClick, oneClick };
	State state;
	Array<double> CircleParameters;
	Vector2 infoMode;
public:
	CreatingCircle();
	~CreatingCircle();

	Mode* HandleEvent(const Event, Array<double>&);
	void DrawMode();
};

class CreatingArc : public Mode {
private:
	enum State { noClick, oneClick, twoClick };
	State state;
	Array<double> arcParameters;
	Vector2 infoMode;
public:
	CreatingArc();
	~CreatingArc();
	Mode* HandleEvent(const Event, Array<double>&);

	void DrawMode();
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
	enum State { noClick, click };
	enum StatusRedaction { move, scale };
	Array<ID> selectedObjects;
	Vector2 posStart;
	Vector2 posEnd;
	State state;
	StatusRedaction status;
public:
	// must take containers in constructor
	Redaction(Array<ID>, Event);
	~Redaction();

	Mode* HandleEvent(const Event, Array<double>&);

	void DrawMode();
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

	void DrawMode();
};

//CREATE REQUIRMENT

class CreateRequirementWithParam : public Mode {
private:
	Array<ID> selectedPrim;
	object_type typeRequirement;
public:
	CreateRequirementWithParam(Array<ID>, Event);
	CreateRequirementWithParam();
	~CreateRequirementWithParam();

	Mode* HandleEvent(const Event, Array<double>&);

	void DrawMode();
};

#endif // !__MODE