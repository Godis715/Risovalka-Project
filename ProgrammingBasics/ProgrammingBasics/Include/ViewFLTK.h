#ifndef __VIEW_FLTK
#define __VIEW_FLTK
#include <iostream>
#include "IView.h"
#include "Presenter.h"

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Button.h>



class ViewFLTK : public IView
{
private:
	static Presenter * presenter;
	class SecondWindow : public Fl_Double_Window
	{
	private:
	public:
		SecondWindow(int x, int y, int w, int h, const char *l)
			: Fl_Double_Window(x, y, w, h, l)
		{
			box(FL_UP_BOX);
			color(FL_BLACK);
			resizable(this);
			show();
		}
		~SecondWindow() {}
		int handle(int e)
		{
			int ret = Fl_Double_Window::handle(e);
			if (e == FL_PUSH)
			{
				this->do_callback();
			}
			return(ret);
		}
		void clear()
		{
			fl_color(FL_BLACK);
			fl_rectf(0, 0, w(), h());
			redraw();
		}
	};

	//callbacks
	static void cl_buttenClear(Fl_Widget* o, void*)
	{
		presenter->test2();
	}
	static void cl_clickOnScene(Fl_Widget* o, void*)
	{
		presenter->test(Fl::event_x(), Fl::event_y());
		//((SecondWindow*)o)->color(FL_YELLOW);
		//((SecondWindow*)o)->redraw();
	}
	//

	Fl_Window* mainWindow;
	SecondWindow* drawWindow;
	Fl_Button* buttonClear;
public:
	ViewFLTK()
	{
		presenter = new Presenter(this);

		mainWindow = new Fl_Window(820, 420, "Main Window");
		mainWindow->color(FL_WHITE);

		drawWindow = new SecondWindow(10, 10, 400, 400, "Draw Window");
		drawWindow->end();

		buttonClear = new Fl_Button(420, 10, 100, 30, "Clear scene");
		mainWindow->end();

		mainWindow->show();
		drawWindow->show();
	}
	~ViewFLTK(){}

	int Run()
	{
		buttonClear->callback(cl_buttenClear);
		drawWindow->when(FL_WHEN_CHANGED);
		drawWindow->callback(cl_clickOnScene);
		return Fl::run();
	}

	void DrawLine(const Vector2& pos1, const Vector2& pos2)
	{
		fl_color(FL_WHITE);
		fl_line(pos1.x, pos1.y, pos2.x, pos2.y);
	}
	void DrawArc(const Vector2&, const Vector2&){}
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
		}
	}
	void Clear()
	{
		drawWindow->clear();
	}

};

Presenter* ViewFLTK::presenter = nullptr;

#endif // !__VIEW_FLTK
