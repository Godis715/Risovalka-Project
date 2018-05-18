#ifndef __VIEW_FLTK
#define __VIEW_FLTK
#include <iostream>
#include "IView.h"
#include "Presenter.h"
#include <string>

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Button.h>
#include <FL/Fl_Round_Button.H>
#include <FL/math.h>

class ViewFLTK : public IView
{
private:

	Fl_Round_Button* status1;
	Fl_Round_Button* status2;
	Fl_Round_Button* status3;
	Fl_Round_Button* status4;
	static int test;
	class SecondWindow : public Fl_Double_Window
	{
		void draw()
		{
			redraw();
			Presenter::drawScene();
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
			//std::cout << Fl::event_text() << std::endl;
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
				//params.PushBack(Fl::event_x());
				//params.PushBack(Fl::event_y());
				//Presenter::Set_event(ev_leftMouseUp, params);
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
				//Presenter::Set_event(ev_mouseMove, params);
				break;
			case FL_DRAG:
				params.PushBack(Fl::event_x());
				params.PushBack(Fl::event_y());
				//Presenter::Set_event(ev_mouseMove, params);
				break;
			}
			return e;
		}
	};

	//callbacks
	static void cl_buttonClear(Fl_Widget* o, void*)
	{
		//Presenter::clearScene();
	}
	
	/*static void cl_clickOnScene(Fl_Widget* o, void*)
	{
		Presenter::clickOnScene(Fl::event_x(), Fl::event_y());
	}*/
	static void cl_changeStatusCreate(Fl_Widget* o, void*)
	{
		Array<double> params(0);
		if (((Fl_Round_Button*)o)->label() == "Create point")
		{
			Presenter::Set_event(ev_createPoint, params);
		}
		if (((Fl_Round_Button*)o)->label() == "Create segment")
		{
			Presenter::Set_event(ev_createSegment, params);
		}
		if (((Fl_Round_Button*)o)->label() == "Create arc")
		{
			Presenter::Set_event(ev_createArc, params);
		}
		if (((Fl_Round_Button*)o)->label() == "Create circle")
		{
			Presenter::Set_event(ev_createCircle, params);
		}
		((Fl_Round_Button*)o)->deactivate();
		((Fl_Round_Button*)o)->activate();
		((Fl_Round_Button*)o)->clear();
	}
	//..

	Fl_Window* mainWindow;
	SecondWindow* drawWindow;
	Fl_Button* buttonClear;
public:
	ViewFLTK()
	{
		
		Presenter::Initializer(this);

		mainWindow = new Fl_Window(820, 420, "Main Window");
		mainWindow->color(FL_WHITE);

		drawWindow = new SecondWindow(10, 10, 400, 400, "Draw Window");
		drawWindow->end();

		buttonClear = new Fl_Button(420, 10, 100, 30, "Clear scene");
		buttonClear->callback(cl_buttonClear);

		//buttonOk = new Fl_Button(640, 180, 50, 30, "Ok");
		{Fl_Group* StatusCreate = new Fl_Group(540, 30, 140, 170, "Status Create");
		StatusCreate->box(FL_THIN_UP_FRAME);
		{status1 = new Fl_Round_Button(StatusCreate->x(), StatusCreate->y() + 10, 100, 30, "Create point");
		status1->tooltip("Info.");
		status1->type(102);
		status1->down_box(FL_ROUND_DOWN_BOX);
		status1->callback(cl_changeStatusCreate);
		} 
		{status2 = new Fl_Round_Button(StatusCreate->x(), StatusCreate->y() + 50, 100, 30, "Create segment");
		status2->tooltip("Info.");
		status2->type(102);
		status2->down_box(FL_ROUND_DOWN_BOX);
		status2->callback(cl_changeStatusCreate);
		} 
		{status3 = new Fl_Round_Button(StatusCreate->x(), StatusCreate->y() + 90, 100, 30, "Create arc");
		status3->tooltip("Info.");
		status3->type(102);
		status3->down_box(FL_ROUND_DOWN_BOX);
		status3->callback(cl_changeStatusCreate);
		}
		{status4 = new Fl_Round_Button(StatusCreate->x(), StatusCreate->y() + 130, 100, 30, "Create circle");
		status4->tooltip("Info.");
		status4->type(102);
		status4->down_box(FL_ROUND_DOWN_BOX);
		status4->callback(cl_changeStatusCreate);
		}
		StatusCreate->end();
		}

		mainWindow->end();
		
		mainWindow->show();
		drawWindow->show();
	}
	~ViewFLTK(){}

	int Run()
	{
		return Fl::run();
	}

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
		}
	}

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

		double r = (center - start).GetLength();
		double angleStart = acos((start.x - center.x) / r) * (180 / PI);
		if (center.y - start.y < 0) {
			angleStart = 360.0 - angleStart;
		}

		double r2 = (center - end).GetLength();
		double angleEnd = acos((end.x - center.x) / r2) * (180 / PI);

		//std::cout << Vector2::Angle(start - center, end - center);
		//std::cout << std::endl;
		//std::cout << acos((end.x - center.x) / r2) - acos((start.x - center.x) / r);
		if (center.y - end.y < 0) {
			angleEnd = 360.0 - angleEnd;
		}

		switch (type)
		{
		case points:
			fl_begin_points();
			_DrawArc(center, r, angleStart, angleEnd);
			fl_end_points();
			break;
		case line:
			fl_begin_line();
			_DrawArc(center, r, angleStart, angleEnd);
			fl_end_line();
			break;
		case polygon:
			fl_begin_polygon();
			_DrawArc(center, r, angleStart, angleEnd);
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
		}
	}
	
	void Update()
	{
		drawWindow->redraw();
	}
};

int ViewFLTK::test = 0;
#endif // !__VIEW_FLTK
