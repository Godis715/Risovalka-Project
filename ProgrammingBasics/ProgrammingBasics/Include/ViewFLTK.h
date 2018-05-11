#ifndef __VIEW_FLTK
#define __VIEW_FLTK

#include <iostream>
#include "Presenter.h"
#include "IView.h"
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Button.h>
#include <stdlib.h>
#include <FL/math.h>
#include <stdio.h>

class ViewFLTK : public IView
{
private:
	Presenter * presenter;
	class MyWindow : public Fl_Window
	{
	private:
		class SecondWindow : public Fl_Double_Window
		{
		private:
			Fl_Color colorScene = FL_BLACK;
			//void star(int w, int h, int n) {
			//	fl_push_matrix();
			//	fl_translate(w / 2, h / 2);
			//	fl_scale(w / 2, h / 2);
			//	for (int i = 0; i < n; i++) {
			//		for (int j = i + 1; j < n; j++)/* for (int k=0; k<10; k++)*/ {
			//			double a = .1;
			//			fl_begin_line();
			//			fl_vertex(cos(2 * M_PI*i / n + .1), sin(2 * M_PI*i / n + .1));
			//			fl_vertex(cos(2 * M_PI*j / n + .1), sin(2 * M_PI*j / n + .1));
			//			fl_end_line();
			//		}
			//	}
			//	fl_pop_matrix();
			//}
			//void bad_draw(int w, int h, int which) {
			//	fl_color(colorScene); fl_rectf(0, 0, w, h);
			//	fl_color(FL_WHITE); star(w, h, 20);
			//}
			
		public:
			bool isTwoClick = false;
			Vector2 beginV;
			SecondWindow(int x, int y, int w, int h, const char *l)
				: Fl_Double_Window(x, y, w, h, l)
			{
				box(FL_UP_BOX);
				color(FL_BLACK);
				resizable(this);
				show();
			}
			~SecondWindow(){}
			int handle(int e)
			{
				int ret = Fl_Double_Window::handle(e);
				switch (e)
				{
				case FL_PUSH:
					if (isTwoClick)
					{
						fl_color(FL_WHITE);
						fl_line(beginV.x, beginV.y, (int)Fl::event_x(), (int)Fl::event_y());
			
						std::cout << (int)Fl::event_x() << " " << (int)Fl::event_y() << " ";
						isTwoClick = false;
					}
					else
					{
						beginV.x = (int)Fl::event_x();
						beginV.y = (int)Fl::event_y();
						std::cout << beginV.x << " " << beginV.y << " ";
						isTwoClick = true;
					}
					break;

				case FL_RELEASE:
					break;

				case FL_ENTER:
					//std::cout << "Enter!";
					//fl_color(FL_CYAN); fl_rectf(0, 0, w(), h());
					break;

				case FL_LEAVE:
					//std::cout << "Leave!";
					//fl_color(FL_BLACK); fl_rectf(0, 0, w(), h());
					break;

				case FL_DRAG:
					break;

				case FL_FOCUS:
					break;

				case FL_UNFOCUS:
					break;

				case FL_KEYDOWN:
					break;

				case FL_CLOSE:
					break;

				case FL_MOVE:
					//std::cout << "move!";

					break;

				case FL_DEACTIVATE:
					break;

				case FL_ACTIVATE:
					break;

				case FL_HIDE:
					break;

				case FL_SHOW:
					break;

				case FL_PASTE:
					break;

				case  FL_SELECTIONCLEAR:
					break;

				case  FL_MOUSEWHEEL:
					break;

				case  FL_NO_EVENT:
					break;
				}
				return(ret);
			}
		};
		Fl_Button* buttenOne;
	public:
		SecondWindow * drawWindow;
		MyWindow(int w, int h, const char *l) : Fl_Window(w, h, l)
		{
			box(FL_FLAT_BOX);
			color(FL_WHITE);
			buttenOne = new Fl_Button(420, 10, 120, 40, "Click Me!");
			begin();
			drawWindow = new SecondWindow(10, 10, 400, 400, "Draw Window");
			end();
			resizable(this);
			show();
		}
		~MyWindow(){}
	};
	
	
	/*void clickOnButten(Fl_Widget* o) {
		o->label("Eeee");
	}
	void clickOnScene(Fl_Widget* o) {
		Fl::get_mouse;
		int posX = (int)Fl::event_x;
		int posY = (int)Fl::event_y;
		presenter->ClickSceneEvent(posX, posY);
		o->parent()->redraw();
	}*/
	
public:
	MyWindow * mainWindow;
	ViewFLTK() 
	{
		mainWindow = new MyWindow(840, 420, "Main Window");
		presenter = new Presenter(this);
	}
	void DrawLine(const Vector2& v1, const Vector2& v2){
		fl_color(FL_WHITE);
		fl_line((int)v1.x, (int)v1.y, (int)v2.x, (int)v2.y);
	}
	void DrawArc(const Vector2&, const Vector2&){}
	void DrawPoint(const Vector2&){}
	void SetColor(color){}

	int Run()
	{
		return Fl::run();
	}
	void Clear(){}
};

#endif

