#pragma once
#include "IView.h"
#include "Model.h"

#define SINGLE_SELECTION
#define POLY_SELECTION
enum statusCreate { drawPoint, drawSegment, drawArc, drawCircle };

enum Event {
	ev_createPoint = 1,
	ev_createSegment,
	ev_createArc,
	ev_createCircle,
	// 4
	ev_move,
	ev_scale,
	ev_turn,
	ev_ch_radius,
	ev_ch_angle,
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
	ev_moveMouse,
	ev_escape,
	//end new events

	ev_save
	// 14
};
/*
class Mode {
protected:
	Presenter* presenter;
	Event lastEvent;
public:
	Mode(Presenter* _pres) {
		presenter = _pres;
	}

	BinSearchTree<ID, ID>* selectedObjects;
	BinSearchTree<ID, ID>* selectedReq;

	Array<ID>* _selObj;
	Array<ID>* _selReq;
	virtual Mode* ProcesseEvent(const Event, Array<double>&) = 0;
};

class Creating : public Mode {
private:
	Array<double> params;
	int index;
public:
	Creating(Event event, Presenter* pres) : Mode(pres) {
		lastEvent = event;
		index = 0;
		switch (event)
		{
		case ev_createPoint: {
			params = Array<double>(2);
			return;
		}
		case ev_createSegment: {
			params = Array<double>(4);
			return;
		}
		case ev_createArc: {
			params = Array<double>(6);
			return;
		}
		case ev_createCircle: {
			params = Array<double>(4);
			return;
		}
		default:
			throw std::exception("Invalid Event type");
		}
	}

	Mode* ProcesseEvent(const Event event, Array<double>& newParams) {
		if (event == ev_leftMouseClick) {
			if (newParams.GetSize() != 2) {
				throw std::exception("uncorrect params for leftMouseClick");
			}
			switch (lastEvent)
			{
			case ev_createPoint: {
				this->presenter->CreateObject(point_t, newParams);
				Selection* mode= new Selection(presenter);
				return mode;
			}
			case ev_createSegment: {
				params = Array<double>(4);
				return;
			}
			case ev_createArc: {
				params = Array<double>(6);
				return;
			}
			case ev_createCircle: {
				params = Array<double>(4);
				return;
			}
			default:
				throw std::exception("Invalid Event type");
			}
		}
	}
};

class Selection : public Mode {
public:
	// must take containers in constructor
	Selection(Presenter*);
	Selection(Event, Presenter*);
	Selection(Event, Array<double>&, Presenter*);

	Mode* ProcesseEvent(const Event, Array<double>&){}
};

class Redaction : public Mode {
public:
	// must take containers in constructor
	Redaction(Event, Presenter*);
	Redaction(Event, Array<double>&, Presenter*);

	Mode* ProcesseEvent(const Event, Array<double>&);
};

class RedactionReq : public Mode {
public:
	// must take containers in constructor
	RedactionReq(Event, Presenter*);

	Mode* ProcesseEvent(const Event, Array<double>&);
};

*/
class Presenter {
private:
	BinSearchTree<ID, ID> selectedObjects;
	BinSearchTree<ID, ID> selectedReq;

	Array<ID> _selObj;
	Array<ID> _selReq;

	Model* model;
	//Mode* mode;

	void SelectObject(const ID&, int){}

	IView* view;


public:
	void set_event(Event ev, Array<double>& params)
	{
		//...
	}
	void drawScene()
	{
		Array<Model::infoObject> scene;
		if (model->DischargeInfoObjects(scene)) {
			for (int i = 0; i < scene.GetSize(); ++i) {
				if (scene[i].type == point_t) {
					view->SetColor(red);
					view->DrawPoint(Vector2(scene[i].params[0], scene[i].params[1]));
				}
				if (scene[i].type == segment_t) {
					view->SetColor(white);
					view->DrawLine(Vector2(scene[i].params[0], scene[i].params[1]),
						Vector2(scene[i].params[2], scene[i].params[3]), line);
				}
				if (scene[i].type == arc_t) {
					view->SetColor(white);
					view->DrawArc(Vector2(scene[i].params[0], scene[i].params[1]),
						Vector2(scene[i].params[2], scene[i].params[3]),
						Vector2(scene[i].params[4], scene[i].params[5]), line);
				}
				if(scene[i].type == circle_t) {
					view->SetColor(white);
					view->DrawCircle(Vector2(scene[i].params[0], scene[i].params[1]),
						Vector2(scene[i].params[0] + scene[i].params[2], scene[i].params[1]), line);
				}
			}
		}
	}

	Presenter(IView* _view)
	{
		/*Mode* temp = mode->processeEvent(PARAM);
		if (TEMP != NULL) {
			delete mode;
			mode - temp;
		}*/
		view = _view;
		model = new Model();
	}

	/* using for creating figures
	 points, segments, arcs, circles .. */
	void CreateObject(object_type, const Array<double>&);

	/* trying to impose requirements
	on selected object */

	bool CreateRequirement(object_type, const Array<double>&);

	void DeletePrimitives();

	void DeleteRequirement(int);

	void ChangeParamRequirement(int, const double);

	void ScaleObjects(const double);

	void MoveObject(const Vector2&);

	void ChangeObject(){}

	void GetRequirements();

	//function for viewFLTK
	
	statusCreate status = drawCircle;
	Array<Vector2> posClicks;
	Array<double> params;

	void changeStatusCreate(statusCreate newStatus)
	{
		status = newStatus;
		posClicks.Clear();
		params.Clear();
		view->Clear();
	}

	void clearScene()
	{
		view->Clear();
		posClicks.Clear();
	}

	void clickOnScene(double x, double y)
	{
		view->SetColor(red);
		view->DrawPoint(Vector2(x, y));
		switch (status)
		{
			case drawPoint:
				params.PushBack(x);
				params.PushBack(y);
				CreateObject(point_t, params);
				params.Clear();
				break;
			case drawSegment:
				params.PushBack(x);
				params.PushBack(y);
				switch (posClicks.GetSize())
				{
				case 0:
					posClicks.PushBack(Vector2(x, y));
					break;
				case 1:
					CreateObject(segment_t, params);
					params.Clear();

					view->SetColor(white);
					view->DrawLine(posClicks[0], Vector2(x, y), line);
					posClicks.Clear();
					break;
				}
				break;
			case drawArc:
				switch (posClicks.GetSize())
				{
					case 0:
						posClicks.PushBack(Vector2(x, y));
						break;
					case 1:
						posClicks.PushBack(Vector2(x, y));

						//..
						view->SetColor(white);
						view->DrawCircle(posClicks[0], posClicks[1], points);
						//..
						break;
					case 2:
						params.PushBack(posClicks[1].x);
						params.PushBack(posClicks[1].y);
						params.PushBack(x);
						params.PushBack(y);
						params.PushBack(Vector2::Angle(posClicks[1] - posClicks[0], Vector2(x, y) - posClicks[0]));
						CreateObject(arc_t, params);
						params.Clear();

						//..
						view->SetColor(black);
						view->DrawCircle(posClicks[0], posClicks[1], points);
						//..

						view->SetColor(white);
						view->DrawArc(posClicks[0], posClicks[1], Vector2(x, y), line);

						view->SetColor(black);
						view->DrawPoint(posClicks[0]);
						posClicks.Clear();
						break;
				}
				break;
			case drawCircle:
				switch (posClicks.GetSize())
				{
				case 0:
					posClicks.PushBack(Vector2(x, y));
					break;
				case 1:
					params.PushBack(posClicks[0].x);
					params.PushBack(posClicks[0].y);
					params.PushBack((Vector2(x, y) - posClicks[0]).GetLength());
					CreateObject(circle_t, params);
					params.Clear();

					view->SetColor(black);
					view->DrawPoint(Vector2(x, y));

					//..
					view->SetColor(white);
					view->DrawCircle(posClicks[0], Vector2(x, y), line);
					
					posClicks.Clear();
					//..
					break;
				}
				break;
			}
		}
};