#ifndef __DISPLAY
#define __DISPLAY
#include "ViewHeaders.h"
#include <sstream>
#include <iomanip>

double Parse(string);

const char* ReverseParse(const double, int&);

class DisplayParams : public DisplayWidjet
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

		bool DisplayPoint(const Array<double>&);

		bool DisplaySegment(const Array<double>&);

		bool DisplayArc(const Array<double>&);

		bool DisplayCircle(const Array<double>&);

		static void cl_OK(Fl_Widget*, void*);

	public:
		void Inizializatoin(const object_type, const Array<double>&,const Array<string>&, const Array<Array<double>>&);

		DisplayParams();
		~DisplayParams();
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
