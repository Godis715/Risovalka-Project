#ifndef __DISPLAY
#define __DISPLAY
#include "ViewHeaders.h"

using namespace DrawProject;

class DisplayParamsPrim : public DisplayWidjet
{
	private:
		int coordX = 1010;
		int coordY = 30;
		int sizeX = 160;
		int sizeY = 80;

		Fl_Group* group;
		static Array<Fl_Float_Input*> inputs;

		static Presenter* presenter;

		Fl_Button* b_OK;
		Fl_Button* b_close;

		Fl_Menu_Button* b_req;
		Fl_Menu_Item* i_req;

		void DisplayPoint(const Array<string>&);

		void DisplaySegment(const Array<string>&);

		void DisplayArc(const Array<string>&);

		void DisplayCircle(const Array<string>&);

		static void cl_OK(Fl_Widget*, void*);

		static void cl_Close(Fl_Widget*, void*);

		static void cl_req(Fl_Widget*, void*);
	public:
		void Inizializatoin(const object_type, const Array<string>&,const Array<string>&);

		void GetParamDisplay(Array<int>&);

		DisplayParamsPrim();
		~DisplayParamsPrim();

		void Clear();
};

class RequirementInput : public DisplayWidjet
{
private:
	Fl_Float_Input* textBuffer;

	static void cl_Input(Fl_Widget*, void*);

	static Presenter* presenter;
public:
	RequirementInput();

	~RequirementInput();
};

class DisplayParamsReq : public DisplayWidjet
{
private:
	int coordX;
	int coordY;
	int sizeX = 160;
	int sizeY = 80;

	Fl_Group* group;
	static Array<Fl_Float_Input*> inputs;
	static Presenter* presenter;
	Fl_Button* b_OK;
	Fl_Button* b_close;
	Fl_Button* b_delete;

	static void cl_OK(Fl_Widget*, void*);

	static void cl_Close(Fl_Widget*, void*);

	static void cl_Delete(Fl_Widget*, void*);

	void CreateInputs(const Array<string>&);
public:
	void Inizializatoin(const Array<string>&, const string);

	DisplayParamsReq(int, int);
	~DisplayParamsReq();

	void Clear();

};

class DrawMode : public DisplayWidjet
{
private:
	static Fl_Output* output;
	static DrawMode* instance;
	static Presenter* presenter;
	DrawMode();
public:
	static DrawMode* GetInstance();

	void SetName(const std::string);
};

#endif __DISPLAY
