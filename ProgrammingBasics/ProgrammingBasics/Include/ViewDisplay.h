#ifndef __DISPLAY
#define __DISPLAY
#include "ViewHeaders.h"

class DisplayParams : public DisplayWidjet
{
	private:
		int coordX = 1010;
		int coordY = 30;
		int sizeX = 160;
		int sizeY = 80;

		object_type type;

		Fl_Group* group;
		static Array<Fl_Float_Input*> inputs;
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
		void Inizializatoin(const Array<string>&,const Array<string>&);

		DisplayParams();
		~DisplayParams();

		void Clear();
};

class RequirementInput : public DisplayWidjet
{
private:
	Fl_Float_Input* textBuffer;

	static void cl_Input(Fl_Widget*, void*);
public:
	RequirementInput();

	~RequirementInput();
};

#endif __DISPLAY
