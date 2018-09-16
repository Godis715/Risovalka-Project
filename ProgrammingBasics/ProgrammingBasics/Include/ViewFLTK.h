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
#include <FL/Fl_Button.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Float_Input.H>
#include <FL/math.h>
#include <sstream>
#include <iomanip>
//#include <FL/Fl_File_Chooser.H>


double Parse(string number) {
	int countPoint = 0;
	if (number[0] == 'e' || number[0] == '.') {
		return -1;
	}

	for (size_t i = 1; i < number.length(); ++i) {
		if (number[i] == 'e' || number[i] == '-') {
			return -1;
		}
		if (number[i] == '.') {
			++countPoint;
			if (countPoint > 1) {
				return -1;
			}
		}
	}
	return stod(number);
}

class ViewFLTK : public IView
{
private:
	static Fl_Output* log;

	static Fl_Widget* currentWindget;

	static Fl_Float_Input* textBuffer;

	static Event lastEvent;

	static Fl_Cursor* lastCursor;

	//..
	static Vector2* translateScene;

	static double scaleScene;

	static double rotateScene;
	//..

	Fl_Menu_Item* objects;
	Fl_Menu_Button* createObject_b;

	Fl_Menu_Item* toolingRed;
	Fl_Menu_Button* redaction_b;

	Fl_Menu_Item* requirements;
	Fl_Menu_Button* createRequirement_b;

	Fl_Button* execute_script_b;
	Fl_Button* save_b;
	Fl_Button* downland_b;

	class SecondWindow : public Fl_Double_Window
	{
		void draw()
		{
			fl_color(FL_BLACK);
			fl_rectf(0, 0, w(), h());

			fl_push_matrix();
			fl_translate(ViewFLTK::translateScene->x, ViewFLTK::translateScene->y);
			fl_scale(ViewFLTK::scaleScene);
			fl_rotate(ViewFLTK::rotateScene);
			Presenter::DrawScene();
			fl_pop_matrix();
		}
		
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
				fl_cursor(*ViewFLTK::lastCursor);
				params.PushBack((Fl::event_x() - ViewFLTK::translateScene->x) / scaleScene);
				params.PushBack((Fl::event_y() - ViewFLTK::translateScene->y) / scaleScene);
				Presenter::Set_event(ev_leftMouseDown, params);
				break;
			case FL_RELEASE:
				fl_cursor(FL_CURSOR_DEFAULT);
				params.PushBack((Fl::event_x() - ViewFLTK::translateScene->x) / scaleScene);
				params.PushBack((Fl::event_y() - ViewFLTK::translateScene->y) / scaleScene);
				Presenter::Set_event(ev_leftMouseUp, params);
				break;
			case FL_MOUSEWHEEL:
				params.PushBack(Fl::event_dy());
				Presenter::Set_event(ev_scroll, params);
				break;
			case FL_ENTER:
				fl_cursor(*ViewFLTK::lastCursor);
				break;

			case FL_LEAVE:
				fl_cursor(FL_CURSOR_DEFAULT);
				break;

			case FL_KEYDOWN:
				if (Fl::event_key() == FL_Down)
				{
					Presenter::Set_event(ev_arrowDown, params);
				}
				if (Fl::event_key() == FL_Up)
				{
					Presenter::Set_event(ev_arrowUp, params);
				}
				if (Fl::event_key() == FL_Left)
				{
					Presenter::Set_event(ev_arrowLeft, params);
				}
				if (Fl::event_key() == FL_Right)
				{
					Presenter::Set_event(ev_arrowRight, params);
				}
				if (Fl::event_key() == FL_Control_L && lastEvent != ev_ctrlDown)
				{
					Presenter::Set_event(ev_ctrlDown, params);
					lastEvent = ev_ctrlDown;
				}
				if (Fl::event_key() == FL_Alt_L && lastEvent != ev_altDown)
				{
					Presenter::Set_event(ev_altDown, params);
					lastEvent = ev_altDown;
				}
				if (Fl::event_key() == FL_Escape)
				{
					if (currentWindget != nullptr)
					{
						delete ViewFLTK::currentWindget;
						ViewFLTK::mainWindow->redraw();
					}
					delete ViewFLTK::lastCursor;
					ViewFLTK::lastCursor = new Fl_Cursor(FL_CURSOR_DEFAULT);
					ViewFLTK::lastEvent = ev_ctrlUp;
					Presenter::Set_event(ev_escape, params);
				}
				if (Fl::event_key() == FL_Shift_L && lastEvent != ev_ctrlDown)
				{
					Presenter::Set_event(lastEvent, params);
				}
				if (Fl::event_key() == FL_Delete)
				{
					ViewFLTK::log->value("Log::Delete selection");
					Presenter::Set_event(ev_del, params);
				}

				break;
			case FL_KEYUP:
				if (Fl::event_key() == FL_Control_L)
				{
					Presenter::Set_event(ev_ctrlUp, params);
					lastEvent = ev_ctrlUp;
				}
				if (Fl::event_key() == FL_Alt_L)
				{
					Presenter::Set_event(ev_altUp, params);
					lastEvent = ev_altUp;
				}
				break;
			case FL_MOVE:
				fl_cursor(*ViewFLTK::lastCursor);
				params.PushBack((Fl::event_x() - ViewFLTK::translateScene->x) / scaleScene);
				params.PushBack((Fl::event_y() - ViewFLTK::translateScene->y) / scaleScene);
				Presenter::Set_event(ev_mouseMove, params);
				break;
			case FL_DRAG:
				/*if (*ViewFLTK::lastCursor == FL_CURSOR_DEFAULT)
				{
					fl_cursor(FL_CURSOR_CROSS);
				}*/
				params.PushBack((Fl::event_x() - ViewFLTK::translateScene->x) / scaleScene);
				params.PushBack((Fl::event_y() - ViewFLTK::translateScene->y) / scaleScene);
				Presenter::Set_event(ev_mouseMove, params);
				break;
			}
			return e;
		}
	};

	class DisplayParams
	{
	private:
		int coordX = 1010;
		int coordY = 100;
		int sizeX = 110;
		int sizeY = 200;
		object_type type;
		Fl_Group* group;
		Array<Fl_Float_Input*> inputs;
		Fl_Button* b_OK;
		Fl_Button* b_close;
		const char* ReverseParse(const double dig, int& size)
		{
			std::string strDig;
			std::ostringstream ost;
			ost << std::fixed << std::setprecision(2) << dig;
			strDig = ost.str();

			size = strDig.length();
			char* charDig = new char[size];
			for (int i = 0; i < size; i++)
			{
				charDig[i] = strDig[i];
			}
			return charDig;
		}

		bool DisplayPoint(const Array<double>& params)
		{
			if (params.GetSize() != 2) return false; //исключение
			int digLength = 0;
			const char* dig;

			inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 10, 50, 30, "x"));
			dig = ReverseParse(params[0], digLength);
			inputs[0]->value(dig, digLength);

			inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 40, 50, 30, "y"));
			dig = ReverseParse(params[1], digLength);
			inputs[1]->value(dig, digLength);
		}

		bool DisplaySegment(const Array<double>& params)
		{
			if (params.GetSize() != 4) return false; //исключение
			int digLength = 0;
			const char* dig;

			inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 10, 50, 30, "x1"));
			dig = ReverseParse(params[0], digLength);
			inputs[0]->value(dig, digLength);

			inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 40, 50, 30, "y1"));
			dig = ReverseParse(params[1], digLength);
			inputs[1]->value(dig, digLength);

			inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 70, 50, 30, "x2"));
			dig = ReverseParse(params[2], digLength);
			inputs[2]->value(dig, digLength);

			inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 100, 50, 30, "y2"));
			dig = ReverseParse(params[3], digLength);
			inputs[3]->value(dig, digLength);
		}

		bool DisplayArc(const Array<double>& params)
		{
			if (params.GetSize() != 6) return false; //исключение
			int digLength = 0;
			const char* dig;

			inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 10, 50, 30, "x1"));
			dig = ReverseParse(params[2], digLength);
			inputs[0]->value(dig, digLength);

			inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 40, 50, 30, "y1"));
			dig = ReverseParse(params[3], digLength);
			inputs[1]->value(dig, digLength);

			inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 70, 50, 30, "x2"));
			dig = ReverseParse(params[4], digLength);
			inputs[2]->value(dig, digLength);

			inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 100, 50, 30, "y2"));
			dig = ReverseParse(params[5], digLength);
			inputs[3]->value(dig, digLength);

			Vector2 vector1 = Vector2(params[2], params[3]) - Vector2(params[0], params[1]);
			Vector2 vector2 = Vector2(params[4], params[5]) - Vector2(params[0], params[1]);
			double angle = (Vector2::Angle(vector1, vector2) * 180)/PI;
			inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 130, 50, 30, "an"));
			dig = ReverseParse(angle, digLength);
			inputs[4]->value(dig, digLength);
		}

		bool DisplayCircle(const Array<double>& params)
		{
			if (params.GetSize() != 3) return false; //исключение
			int digLength = 0;
			const char* dig;

			inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 10, 50, 30, "x"));
			dig = ReverseParse(params[0], digLength);
			inputs[0]->value(dig, digLength);

			inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 40, 50, 30, "y"));
			dig = ReverseParse(params[1], digLength);
			inputs[1]->value(dig, digLength);

			inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 70, 50, 30, "r"));
			dig = ReverseParse(params[2], digLength);
			inputs[2]->value(dig, digLength);
		}

	public:
		DisplayParams(const object_type type, const Array<double>& params)
		{

			group = new Fl_Group(coordX, coordY, sizeX, sizeY);
			{
				switch (type)
				{
				case ot_point: {
					DisplayPoint(params);
					break;
				}
				case ot_segment: {
					DisplaySegment(params);
					break;
				}
				case ot_arc: {
					DisplayArc(params);
					break;
				}
				case ot_circle: {
					DisplayCircle(params);
					break;
				}
				default:
					break;
				}

				b_OK = new Fl_Button(coordX + 10, coordY + sizeY - 30, 30, 20, "OK");
				b_close = new Fl_Button(coordX + 50, coordY + sizeY - 30, 50, 20, "CLOSE");
				group->color(FL_YELLOW);
				group->box(FL_UP_BOX);
				group->end();
			}
			
		}



	};

	static DisplayParams* displayParams;

	//callbacks
	static void cl_Create(Fl_Widget* o, void*)
	{
		delete lastCursor;
		lastCursor = new Fl_Cursor(FL_CURSOR_DEFAULT);
		Array<double> params(0);
		if (((Fl_Menu_Button*)o)->mvalue()->label() == "Point")
		{
			log->value("Log::Create point");
			Presenter::Set_event(ev_createPoint, params);
			lastEvent = ev_createPoint;
		}
		if (((Fl_Menu_Button*)o)->mvalue()->label() == "Segment")
		{
			log->value("Log::Create segment");
			Presenter::Set_event(ev_createSegment, params);
			lastEvent = ev_createSegment;
		}
		if (((Fl_Menu_Button*)o)->mvalue()->label() == "Arc")
		{
			log->value("Log::Create arc");
			Presenter::Set_event(ev_createArc, params);
			lastEvent = ev_createArc;
		}
		if (((Fl_Menu_Button*)o)->mvalue()->label() == "Circle")
		{
			log->value("Log::Create circle");
			Presenter::Set_event(ev_createCircle, params);
			lastEvent = ev_createCircle;
		}
	}

	static void cl_Redaction(Fl_Widget* o, void*)
	{
		delete lastCursor;
		lastCursor = new Fl_Cursor(FL_CURSOR_DEFAULT);
		Array<double> params(0);

		if (((Fl_Menu_Button*)o)->mvalue()->label() == "Move selection")
		{
			log->value("Log::Move selection");
			delete lastCursor;
			lastCursor = new Fl_Cursor(FL_CURSOR_MOVE);
			Presenter::Set_event(ev_moveObjects, params);
		}

		if (((Fl_Menu_Button*)o)->mvalue()->label() == "Scale selection")
		{
			log->value("Log::Scale selection");
			Presenter::Set_event(ev_scaleObjects, params);
		}

		if (((Fl_Menu_Button*)o)->mvalue()->label() == "Delete selection")
		{
			log->value("Log::Delete selection");
			Presenter::Set_event(ev_del, params);
		}

		if (((Fl_Menu_Button*)o)->mvalue()->label() == "Delete all scene")
		{
			log->value("Log::Delete all scene");
			Presenter::CleareScene();
		}
	}

	static void cl_Requirement(Fl_Widget* o, void*)
	{
		delete lastCursor;
		lastCursor = new Fl_Cursor(FL_CURSOR_DEFAULT);
		Array<double> params(0);
		if (((Fl_Menu_Button*)o)->mvalue()->label() == "Dist points")
		{
			log->value("Log::Create requirement: Dist points");
			mainWindow->begin();
			textBuffer = new Fl_Float_Input(1010, 50, 100, 30);
			textBuffer->when(FL_WHEN_ENTER_KEY);
			textBuffer->callback(cl_Input);
			mainWindow->end();
			mainWindow->redraw();
			currentWindget = textBuffer;
			Presenter::Set_event(ev_req_D_point, params);
		}
		if (((Fl_Menu_Button*)o)->mvalue()->label() == "Equal segment")
		{
			log->value("Log::Create requirement: Equal segment");
			Presenter::Set_event(ev_req_Eq_Segment, params);
		}
		if (((Fl_Menu_Button*)o)->mvalue()->label() == "Points on one hand")
		{
			log->value("Log::Create requirement: Points on one hand");
			Presenter::Set_event(ev_req_on_one_hand, params);
		}
		if (((Fl_Menu_Button*)o)->mvalue()->label() == "Dist point segment")
		{
			log->value("Log::Create requirement: Dist point segment");
			mainWindow->begin();
			textBuffer = new Fl_Float_Input(1010, 50, 100, 30);
			textBuffer->when(FL_WHEN_ENTER_KEY);
			textBuffer->callback(cl_Input);
			mainWindow->end();
			mainWindow->redraw();
			currentWindget = textBuffer;
			Presenter::Set_event(ev_req_D_point_segment, params);
		}
		if (((Fl_Menu_Button*)o)->mvalue()->label() == "Dist point arc")
		{
			log->value("Log::Create requirement: Dist point arc");
			mainWindow->begin();
			textBuffer = new Fl_Float_Input(1010, 50, 100, 30);
			textBuffer->when(FL_WHEN_ENTER_KEY);
			textBuffer->callback(cl_Input);
			mainWindow->end();
			mainWindow->redraw();
			currentWindget = textBuffer;
			Presenter::Set_event(ev_req_D_point_arc, params);
		}
		if (((Fl_Menu_Button*)o)->mvalue()->label() == "Angle between segment")
		{
			log->value("Log::Create requirement: Angle between segment");
			mainWindow->begin();
			textBuffer = new Fl_Float_Input(1010, 50, 100, 30);
			textBuffer->when(FL_WHEN_ENTER_KEY);
			textBuffer->callback(cl_Input);
			mainWindow->end();
			mainWindow->redraw();
			currentWindget = textBuffer;
			Presenter::Set_event(ev_req_angle_segment, params);
		}

	}

	static void cl_Input(Fl_Widget* o, void*) {
		fl_cursor(FL_CURSOR_DEFAULT);

		Array<double> params(1);
		string numbers = ((Fl_Float_Input*)o)->value();
		((Fl_Float_Input*)o)->value("");
		params[0] = Parse(numbers);
		Presenter::Set_event(ev_input, params);

		delete currentWindget;
		currentWindget = nullptr;
		mainWindow->redraw();
	}

	static void cl_execute_script_b(Fl_Widget* o, void*)
	{
		Presenter::Compile();
		((Fl_Button*)o)->deactivate();
		((Fl_Button*)o)->activate();
	}

	static void cl_SaveProject(Fl_Widget* o, void*)
	{
		//char *newfile;
		
		//newfile = fl_file_chooser("Save File As?", "*", "title");
		Presenter::SaveProject("way");
		((Fl_Button*)o)->deactivate();
		((Fl_Button*)o)->activate();
	}

	static void cl_DownloadFile(Fl_Widget* o, void*)
	{
		Presenter::DownloadFile("nameFile");
		((Fl_Button*)o)->deactivate();
		((Fl_Button*)o)->activate();
	}
	//..

	static Fl_Window* mainWindow;
	SecondWindow* drawWindow;
public:
	ViewFLTK()
	{
		Presenter::Initializer(this);

		mainWindow = new Fl_Window(1300, 620, "Main Window");
		mainWindow->color(FL_WHITE);

		drawWindow = new SecondWindow(10, 30, 1000, 600, "Draw Window");
		drawWindow->end();

		save_b = new Fl_Button(1050, 30, 40, 30, "Save");
		save_b->callback(cl_SaveProject);
		save_b->color(FL_WHITE);

		execute_script_b = new Fl_Button(1010, 30, 40, 30, "script");
		execute_script_b->callback(cl_execute_script_b);
		execute_script_b->color(fl_rgb_color(255, 105, 180));

		downland_b = new Fl_Button(1090, 30, 70, 30, "Download");
		downland_b->callback(cl_DownloadFile);
		downland_b->color(FL_WHITE);

		log = new Fl_Output(1010, 0, 300, 30);

		{
			objects = new Fl_Menu_Item[5];
			objects[0] = { "Point", FL_ALT + 'z'};
			objects[1] = { "Segment", FL_ALT + 'x' };
			objects[2] = { "Arc", FL_ALT + 'c' };
			objects[3] = { "Circle", FL_ALT + 'v' };
			objects[4] = { 0 };
			createObject_b = new  Fl_Menu_Button(10, 0, 150, 30, "Create object");
			createObject_b->menu(objects);
			createObject_b->callback(cl_Create);
			createObject_b->clear_visible_focus();
			createObject_b->color(FL_WHITE);
		}

		{
			toolingRed = new Fl_Menu_Item[6];
			toolingRed[0] = { "Move selection" };
			toolingRed[1] = { "Scale selection" };
			toolingRed[2] = { "Delete selection"};
			toolingRed[3] = { "Delete all scene"};
			toolingRed[4] = { 0 };
			redaction_b = new  Fl_Menu_Button(160, 0, 150, 30, "Redaction scene");
			redaction_b->menu(toolingRed);
			redaction_b->callback(cl_Redaction);
			redaction_b->clear_visible_focus();
			redaction_b->color(FL_WHITE);
		}

		{
			requirements = new Fl_Menu_Item[7];
			requirements[0] = { "Dist points"};
			requirements[1] = { "Equal segment" };
			requirements[2] = { "Points on one hand" };
			requirements[3] = { "Dist point segment" };
			requirements[4] = { "Dist point arc" };
			requirements[5] = { "Angle between segment" };
			requirements[6] = { 0 };
			createRequirement_b = new  Fl_Menu_Button(310, 0, 150, 30, "Create requirement");
			createRequirement_b->menu(requirements);
			createRequirement_b->callback(cl_Requirement);
			createRequirement_b->clear_visible_focus();
			createRequirement_b->color(FL_WHITE);
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
			fl_begin_line();
			fl_vertex(start.x, start.y);
			fl_vertex(end.x, end.y);
			fl_end_line();
			break;
		case line:
			fl_begin_line();
			fl_vertex(start.x, start.y);
			fl_vertex(end.x, end.y);
			fl_end_line();
			break;
		default:
			fl_begin_line();
			fl_vertex(start.x, start.y);
			fl_vertex(end.x, end.y);
			fl_end_line();
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
		fl_begin_line();
		fl_vertex(pos.x - size, pos.y - size);
		fl_vertex(pos.x + size, pos.y + size);
		fl_end_line();

		fl_begin_line();
		fl_vertex(pos.x + size, pos.y - size);
		fl_vertex(pos.x - size, pos.y + size);
		fl_end_line();
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

	void GiveParams(const object_type type, const Array<double>& params)
	{
		mainWindow->begin();
		displayParams = new DisplayParams(type, params);
		mainWindow->end();
		mainWindow->redraw();
	}

	//for navigation on scene
	void TranslateScene(const Vector2& deltaCor)
	{
		*translateScene += deltaCor;
	}

	void ScaleScene(const double& deltaCoef)
	{
		if ((scaleScene + deltaCoef > 0.1) && (scaleScene + deltaCoef < 10))
		{
			scaleScene += deltaCoef;
		}
	}

	void RotateScene(const double& deltaAngle)
	{
		rotateScene += deltaAngle;
	}
};
Fl_Window* ViewFLTK::mainWindow;

Fl_Output* ViewFLTK::log = nullptr;

Fl_Float_Input* ViewFLTK::textBuffer = nullptr;

Fl_Widget* ViewFLTK::currentWindget = nullptr;

Fl_Cursor* ViewFLTK::lastCursor = new Fl_Cursor(FL_CURSOR_DEFAULT);

Event ViewFLTK::lastEvent = ev_ctrlUp;

Vector2* ViewFLTK::translateScene = new Vector2(0.0, 0.0);

double ViewFLTK::scaleScene = 1.0;

double ViewFLTK::rotateScene = 0.0;

ViewFLTK::DisplayParams* ViewFLTK::displayParams = nullptr;

#endif // !__VIEW_FLTK
