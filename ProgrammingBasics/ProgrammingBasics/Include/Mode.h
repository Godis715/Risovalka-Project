#pragma once

#include "IView.h"
#include "Model.h"

enum Event

{
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
	ev_escape,
	//end new events

	ev_save
	// 14
};

class Mode {
protected:
	Presenter* presenter;
	Event lastEvent;

	Mode* UnexpectedEvent(const Event e) {
		this->Cancel();
		switch (e) {
		case ev_createPoint: {
			return new CreatingPoint();
		}
		case ev_createArc: {
			return new CreateArc();
		}
		case ev_createSegment: {
			return new CreateSegment();
		}
		case ev_createCircle: {
			return new CreateCircle();
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

	Mode* HandleEvent(const Event event, Array<double>& newParams) {
		if (event == ev_leftMouseClick) {
			if (newParams.GetSize() != 2) {
				throw std::exception("uncorrect params for leftMouseClick");
			}
			switch (lastEvent)
			{
			case ev_createPoint: {

				this->presenter->CreateObject(point_t, newParams);
				Selection* mode = new Selection(presenter);
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
		switch (ev) {
		case ev_leftMouseClick: {
			if (params.GetSize() < 1) {
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

				ID newSegment;
				presenter->CreateSegment(segment_t, segmentParameters/*, newSegment*/);
				
				Array<ID> selectedObjects(1);
				selectedObjects[0] = newSegment;
				/*return new Selection(selectedObjects); */
			break;
		}
		}
		case ev_escape: {

			//return new Selection();
			break; 
		}
		default: {
		
			break;
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

	Mode* HandleEvent(const Event, Array<double>&);
};

class Redaction : public Mode {
public:
	// must take containers in constructor
	Redaction(Event, Presenter*);
	Redaction(Event, Array<double>&, Presenter*);

	bool HandleEvent(const Event, Array<double>&, Mode*&);
};

class RedactionReq : public Mode {
public:
	// must take containers in constructor
	RedactionReq(Event, Presenter*);

	bool HandleEvent(const Event, Array<double>&, Mode*&);
};
vm