#ifndef __MODE
#define __MODE

#include "IView.h"
#include "Model.h"
#include "Colors.h"
#include <sstream>
#include <iomanip>

double Parse(string);

const char* ReverseParse(const double, int&);

const string ReverseParse(const double);

const char* str_ch(const string);

enum Event
{
	// create primitive
	ev_createPoint = 1,
	ev_createSegment,
	ev_createArc,
	ev_createCircle,
	//create requirements
	ev_req_D_point,
	ev_req_Eq_Segment,
	ev_req_on_one_hand,
	ev_req_D_point_segment,
	ev_req_D_point_arc,
	ev_req_angle_segment,
	ev_input,
	// redaction
	ev_moveObjects,
	ev_scaleObjects,
	ev_del,
	ev_undo,
	ev_redu,

	// mouseEvent
	ev_leftMouseClick,
	ev_rightMouseClick,
	ev_leftMouseDown,
	ev_rightMouseDown,
	ev_leftMouseUp,
	ev_rightMouseUp,
	ev_mouseMove,
	ev_scroll,
	// keyboardEvent
	ev_ctrlDown,
	ev_ctrlUp,
	ev_altDown,
	ev_altUp,
	ev_arrowUp,
	ev_arrowDown,
	ev_arrowLeft,
	ev_arrowRight,
	ev_escape,
	// Widjets
	ev_click_Req,
	ev_change_Prim,
	ev_change_Req,
	ev_delete_Req,
	ev_delete_display_Prim,
	ev_delete_display_Req,
	// file work
	ev_save
};

class Mode {
protected:
	Event lastEvent;

	Mode* UnexpectedEvent(const Event e);

	IView* view;
	Model* model;
public:
	Mode();
	virtual ~Mode() {}
	virtual Mode* HandleEvent(const Event, Array<double>&) = 0;
	virtual void DrawMode() { }
};

class ChangingProperties : public Mode {
private:
	IDisplayParamPrim* widjetPrim;
	IDisplayParamReq* widjetReq;
	ID selectedObject;
	Array<ID> reqIDs;
	ID reqID;
	Array<ID> primiOfReqIDs;
	bool isNew = true;
	//enum State { single_selection, poly_selection, area_selection };
	//State state;

	void SetWidjetParamPrim();

	void SetWidjetParamReq();
public:
	ChangingProperties();
	ChangingProperties(const ID _selObjects);
	~ChangingProperties();

	Mode* HandleEvent(const Event e, Array<double>& params);

	void DrawMode();
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
	ICreatingToolbar* widjet;

	void AddObject(const ID& obj);

	Array<string> GetPossibleReqType();
public:
	Selection();
	Selection(ID);
	Selection(Array<ID>);
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

	Vector2 center;
	Vector2 point1;
	Vector2 point2;
	double radius;
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

//class RedactionReq : public Mode {
//private:
//	Array<ID> objects;
//	Array<ID> reqs;
//	ID selectedReq;
//	ID selectedPrim;
//	Array<ID> objectsOfreq;
//public:
//	RedactionReq(ID _selecObj);
//	RedactionReq();
//	~RedactionReq();
//
//	Mode* HandleEvent(const Event, Array<double>&);
//
//	void DrawMode();
//};

class CreateRequirementWithParam : public Mode {
private:
	Array<ID> selectedObjects;
	object_type typeRequirement;
	IRequirementInput* inputWidjet;
public:
	CreateRequirementWithParam(Array<ID>, Event);
	CreateRequirementWithParam();
	~CreateRequirementWithParam();

	Mode* HandleEvent(const Event, Array<double>&);

	void DrawMode();
};

class NavigationOnScene : public Mode {
private:
	enum State	{noClick, click};
	Array<ID> selectedPrim;
	Vector2 posStart;
	Vector2 posEnd;
	double speedMove;
	State stateMove;
public:
	NavigationOnScene(Array<ID>);
	NavigationOnScene();
	~NavigationOnScene();

	Mode* HandleEvent(const Event, Array<double>&);

	void DrawMode();
};

#endif __MODE