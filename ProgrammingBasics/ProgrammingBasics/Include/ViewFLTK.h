#ifndef __VIEW_FLTK
#define __VIEW_FLTK
#define text_type 102
#include <iostream>
#include "IView.h"
#include "Presenter.h"
#include <string>

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.h>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Input.H>
#include <FL/math.h>

class ViewFLTK : public IView
{
private:
	Fl_Menu_Item* objects;
	Fl_Menu_Button* createObject_b;

	Fl_Menu_Item* toolingRed;
	Fl_Menu_Button* redaction_b;

	Fl_Menu_Item* requirements;
	Fl_Menu_Button* createRequirement_b;

	class SecondWindow : public Fl_Double_Window
	{
		void draw()
		{
			fl_color(FL_BLACK);
			fl_rectf(0, 0, w(), h());
			Presenter::DrawScene();
		}
		Event lastEvent = ev_ctrlUp;
	public:
		SecondWindow(int x, int y, int w, int h, const char *l)
			: Fl_Double_Window(x, y, w, h, l)
		{
			box(FL_UP_BOX);
			color(FL_BLACK);
			resizable(this);
		}
		~SecondWindow() {}
		int handle(int e)
		{
			Array<double> params;
			switch (e)
			{
			case FL_PUSH:
			{
				params.PushBack(Fl::event_x());
				params.PushBack(Fl::event_y());
				Presenter::Set_event(ev_leftMouseDown, params);
				break;
			}
			case FL_RELEASE:
				params.PushBack(Fl::event_x());
				params.PushBack(Fl::event_y());
				Presenter::Set_event(ev_leftMouseUp, params);
				break;

			case FL_ENTER:
				//std::cout << "Enter!";
				//fl_color(FL_CYAN); fl_rectf(0, 0, w(), h());
				break;

			case FL_LEAVE:
				//std::cout << "Leave!";
				//fl_color(FL_BLACK); fl_rectf(0, 0, w(), h());
				break;

			case FL_KEYDOWN:
				if (Fl::event_key() == FL_Control_L && lastEvent != ev_ctrlDown)
				{
					Presenter::Set_event(ev_ctrlDown, params);
					lastEvent = ev_ctrlDown;
				}
				if (Fl::event_key() == FL_Escape)
				{
					Presenter::Set_event(ev_escape, params);
				}
				break;
			case FL_KEYUP:
				if (Fl::event_key() == FL_Control_L)
				{
					Presenter::Set_event(ev_ctrlUp, params);
					lastEvent = ev_ctrlUp;
				}
				break;
			case FL_MOVE:
				params.PushBack(Fl::event_x());
				params.PushBack(Fl::event_y());
				Presenter::Set_event(ev_mouseMove, params);
				break;
			case FL_DRAG:
				params.PushBack(Fl::event_x());
				params.PushBack(Fl::event_y());
				Presenter::Set_event(ev_mouseMove, params);
				break;
			}
			return e;
		}
	};

	//callbacks
	static void cl_ChangeStatusCreate(Fl_Widget* o, void*)
	{
		Array<double> params(0);
		if (((Fl_Menu_Button*)o)->mvalue()->label() == "Point")
		{
			Presenter::Set_event(ev_createPoint, params);
		}
		if (((Fl_Menu_Button*)o)->mvalue()->label() == "Segment")
		{
			Presenter::Set_event(ev_createSegment, params);
		}
		if (((Fl_Menu_Button*)o)->mvalue()->label() == "Arc")
		{
			Presenter::Set_event(ev_createArc, params);
		}
		if (((Fl_Menu_Button*)o)->mvalue()->label() == "Circle")
		{
			Presenter::Set_event(ev_createCircle, params);
		}
	}

	static void cl_Redaction(Fl_Widget* o, void*)
	{
		Array<double> params(0);
		if (((Fl_Menu_Button*)o)->mvalue()->label() == "Delete selection")
		{
			Presenter::Set_event(ev_del, params);
		}
		if (((Fl_Menu_Button*)o)->mvalue()->label() == "Delete all scene")
		{
			Presenter::CleareScene();
		}
	}
	
	static void cl_Requirement(Fl_Widget* o, void*)
	{
		Array<double> params(0);
	
		if (((Fl_Menu_Button*)o)->mvalue()->label() == "Dist points")
		{
			Presenter::Set_event(ev_req_D_point, params);
		}
		if (((Fl_Menu_Button*)o)->mvalue()->label() == "Equal segment")
		{
			Presenter::Set_event(ev_req_Eq_Segment, params);
		}
	}

	//..

	Fl_Window* mainWindow;
	SecondWindow* drawWindow;
public:
	ViewFLTK()
	{
		Presenter::Initializer(this);

		mainWindow = new Fl_Window(1300, 620, "Main Window");
		mainWindow->color(FL_WHITE);

		drawWindow = new SecondWindow(10, 30, 1000, 600, "Draw Window");
		drawWindow->end();

		{
			objects = new Fl_Menu_Item[5];
			objects[0] = { "Point", FL_ALT + 'z'};
			objects[1] = { "Segment", FL_ALT + 'x' };
			objects[2] = { "Arc", FL_ALT + 'c' };
			objects[3] = { "Circle", FL_ALT + 'v' };
			objects[4] = { 0 };
			createObject_b = new  Fl_Menu_Button(10, 0, 150, 30, "Status object");
			createObject_b->menu(objects);
			createObject_b->callback(cl_ChangeStatusCreate);
			createObject_b->clear_visible_focus();
			createObject_b->color(FL_WHITE);
		}

		{
			toolingRed = new Fl_Menu_Item[3];
			toolingRed[0] = { "Delete selection"};
			toolingRed[1] = { "Delete all scene"};
			toolingRed[2] = { 0 };
			redaction_b = new  Fl_Menu_Button(160, 0, 150, 30, "Redaction scene");
			redaction_b->menu(toolingRed);
			redaction_b->callback(cl_Redaction);
			redaction_b->clear_visible_focus();
			redaction_b->color(FL_WHITE);
		}

		{
			requirements = new Fl_Menu_Item[3];
			requirements[0] = { "Dist points"};
			requirements[1] = { "Equal segment" };
			requirements[2] = { 0 };
			redaction_b = new  Fl_Menu_Button(310, 0, 150, 30, "Create requirement");
			redaction_b->menu(requirements);
			redaction_b->callback(cl_Requirement);
			redaction_b->clear_visible_focus();
			redaction_b->color(FL_WHITE);
		}

		mainWindow->end();
		
		mainWindow->show();
		drawWindow->show();
	}
	~ViewFLTK(){}

	int Run(){return Fl::run();}

	void DrawLine(const Vector2& start, const Vector2& end, typeDrawing type)
	{
		switch (type)
		{
		case points:
			fl_line_style(FL_DOT, 2);
			fl_line(start.x, start.y, end.x, end.y);
			break;
		case line:
			fl_line(start.x, start.y, end.x, end.y);
			break;
		default:
			fl_line(start.x, start.y, end.x, end.y);
			break;
		}	}

	void DrawCircle(const Vector2& center, const Vector2& pointForCircle, typeDrawing type)
	{
		double r = (pointForCircle - center).GetLength();

		switch (type)
		{
		case points:
			fl_begin_points();
			fl_arc(center.x, center.y, r, 0.0, 360.0);
			fl_end_points();
			break;
		case line:
			fl_begin_line();
			fl_arc(center.x, center.y, r, 0.0, 360.0);
			fl_end_line();
			break;
		case polygon:
			fl_begin_polygon();
			fl_arc(center.x, center.y, r, 0.0, 360.0);
			fl_end_polygon();
			break;
		}
	}

	void _DrawArc(const Vector2& center, double R, double angleStart, double angleEnd) {
		if (angleStart < angleEnd) {
			fl_arc(center.x, center.y, R, angleStart, angleEnd);
			return;
		}
		else {
			fl_arc(center.x, center.y, R, angleStart, 360.0);
			fl_arc(center.x, center.y, R, 0.0, angleEnd);
		}
	}

	void DrawArc(const Vector2& center, const Vector2& start, const Vector2& end, typeDrawing type)
	{
		double EPS = 5.0;
		double r1 = (center - start).GetLength();
		double angleStart = (abs(r1) < EPS) ? 0.0 : acos((start.x - center.x) / r1) * (180 / PI);
		if (center.y - start.y < 0) {
			angleStart = 360.0 - angleStart;
		}

		double r2 = (center - end).GetLength();
		double angleEnd = (abs(r2) < EPS) ? 360.0 : acos((end.x - center.x) / r2) * (180 / PI);
		if (center.y - end.y < 0) {
			angleEnd = 360.0 - angleEnd;
		}

		switch (type)
		{
		case points:
			fl_begin_points();
			_DrawArc(center, r1, angleStart, angleEnd);
			fl_end_points();
			break;
		case line:
			fl_begin_line();
			_DrawArc(center, r1, angleStart, angleEnd);
			fl_end_line();
			break;
		case polygon:
			fl_begin_polygon();
			_DrawArc(center, r1, angleStart, angleEnd);
			fl_end_polygon();
			break;
		}
	}

	void DrawPoint(const Vector2& pos)
	{
		int size = 2;
		fl_line(pos.x - size, pos.y - size, pos.x + size, pos.y + size);
		fl_line(pos.x + size, pos.y - size, pos.x - size, pos.y + size);
	}
	
	void SetColor(color col)
	{
		switch (col)
		{
			case white:
				fl_color(FL_WHITE);
				break;
			case red:
				fl_color(FL_RED);
				break;
			case black:
				fl_color(FL_BLACK);
				break;
			case green:
				fl_color(FL_GREEN);
				break;
			case yellow:
				fl_color(FL_YELLOW);
				break;
			case blue:
				fl_color(FL_BLUE);
				break;
		}
	}
	
	void Update()
	{
		drawWindow->redraw();
	}
};
#endif // !__VIEW_FLTK
