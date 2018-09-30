#ifndef __VIEW_FLTK
#define __VIEW_FLTK
#define text_type 102
#include "IView.h"

#include "ViewHeaders.h"

#include "ViewDrawWindow.h"
#include "ViewToolbar.h"
#include "ViewLog.h"
#include "ViewFile.h"

#include <sstream>
#include <iomanip>

double Parse(string);

const char* ReverseParse(const double, int&);

class ViewFLTK : public IView
{
private:
	
	static ViewLog* viewLog;

	ViewToolbar* viewToolbar;

	ViewFile* viewFile;

	static DrawWindow* drawWindow;

	//-------------------

	//static Fl_Float_Input* textBuffer;

	/*class DisplayParams
	{
	private:
		int coordX = 1010;
		int coordY = 90;
		int sizeX = 160;
		int sizeY = 230;

		object_type type;

		Fl_Group* group;
		static Array<Fl_Float_Input*> inputs;
		Fl_Button* b_OK;
		Fl_Button* b_close;

		Fl_Menu_Button* b_req;
		Fl_Menu_Item* i_req;

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

		static void cl_OK(Fl_Widget* o, void*)
		{
			Array<double> params;
			for (int i = 0; i < inputs.GetSize(); i++)
			{
				params.PushBack(Parse(inputs[i]->value()));
			}
			Presenter::Set_event(ev_change_Prim, params);
		}

	public:
		DisplayParams(const object_type _type, const Array<double>& params,
			const Array<string>& nameReqs, const Array<Array<double>>& reqParams)
		{
			switch (_type)
			{
			case ot_point:
				sizeY = 140;
				break;
			case ot_segment:
				sizeY = 200;
				break;
			case ot_arc: 
				sizeY = 230;
				break;
			case ot_circle: 
				sizeY = 170;
				break;
			default:
				break;
			}
			group = new Fl_Group(coordX, coordY, sizeX, sizeY);
			{
				switch (_type)
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
				type = _type;
				b_OK = new Fl_Button(coordX + 10, coordY + sizeY - 30, 30, 20, "OK");
				b_OK->color(FL_WHITE);
				b_OK->callback(cl_OK);
				{
					i_req = new Fl_Menu_Item[nameReqs.GetSize() + 1];
					for (int i = 0; i < nameReqs.GetSize(); ++i) {
						char* nameIt = new char[nameReqs[i].size() + 1];
						for (int j = 0; j < nameReqs[i].size(); j++)
						{
							nameIt[j] = nameReqs[i][j];
						}
						nameIt[nameReqs[i].size()] = '\0';
						i_req[i] = { nameIt };
						//delete[] nameIt;
					}
					i_req[nameReqs.GetSize()] = { 0 };
					b_req = new  Fl_Menu_Button(coordX + 90, coordY + 10, 50, 30, "Req");
					b_req->menu(i_req);
					b_req->callback(cl_OK);
					b_req->clear_visible_focus();
					b_req->color(FL_WHITE);
				}
				group->color(FL_YELLOW);
				group->box(FL_UP_BOX);
				group->end();
			}
			
		}

		~DisplayParams()
		{
			delete b_OK;
			delete b_close;
			delete b_req;
			for (int i = 0; i < inputs.GetSize(); i++)
			{
				delete inputs[i];
			}
			inputs.Clear();
			delete group;
		}

	};

	static DisplayParams* displayParams;

	/*class MainWindow : public Fl_Window
	{
	private:

	public:
		MainWindow(int x, int y, const char* name) : Fl_Window(x, y , name){}
		~MainWindow(){}
		int handle(int e)
		{
			if (e == FL_KEYDOWN || e == FL_KEYUP)
			{
				drawWindow->handle(e);
			}
			return e;
		}
	};*/

	static Fl_Window* mainWindow;


	//callbacks

	/*static void cl_Input(Fl_Widget* o, void*) {

		fl_cursor(FL_CURSOR_DEFAULT);

		Array<double> params(1);
		string numbers = ((Fl_Float_Input*)o)->value();
		((Fl_Float_Input*)o)->value("");
		params[0] = Parse(numbers);
		Presenter::Set_event(ev_input, params);

		delete currentWindget;
		currentWindget = nullptr;
		mainWindow->redraw();
	}*/

	//..
public:
	ViewFLTK();

	~ViewFLTK();

	int Run();

	void DrawLine(const Vector2&, const Vector2&, typeDrawing);

	void DrawCircle(const Vector2&, const Vector2&, typeDrawing);

	void _DrawArc(const Vector2&, double, double, double);

	void DrawArc(const Vector2&, const Vector2&, const Vector2&, typeDrawing);

	void DrawPoint(const Vector2&);
	
	void SetColor(color);
	
	void Update();

	void GiveParams(const object_type, const Array<double>&, const Array<string>&, const Array<Array<double>>&);

	void DeleteDisplay();

	//for navigation on scene
	void TranslateScene(const Vector2&);

	void ScaleScene(const double&);

	void RotateScene(const double&);
};

//Fl_Float_Input* ViewFLTK::textBuffer = nullptr;

//ViewFLTK::DisplayParams* ViewFLTK::displayParams = nullptr;

//DisplayParams

//Array<Fl_Float_Input*> ViewFLTK::DisplayParams::inputs;

#endif // !__VIEW_FLTK
