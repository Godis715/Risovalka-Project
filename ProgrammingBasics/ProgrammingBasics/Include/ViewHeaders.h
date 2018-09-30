#ifndef __VIEW_HEADERS
#define __VIEW_HEADERS
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

#include "Presenter.h"

class DisplayWidjet
{
public:
	DisplayWidjet();
	~DisplayWidjet();
private:
};

class Inventory
{
private:
	static Inventory* instance;
	Inventory();
public:
	static Inventory* GetInstance();

	Event lastEvent;

	Fl_Cursor* lastCursor;

	Fl_Widget* currentWindget;
};


#endif __VIEW_HEADERS