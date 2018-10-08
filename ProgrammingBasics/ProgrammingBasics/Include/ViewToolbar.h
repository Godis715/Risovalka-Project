#ifndef __VIEW_TOOLBAR
#define __VIEW_TOOLBAR
#include "ViewHeaders.h"
#include "ViewLog.h"
class ViewToolbar : public DisplayWidjet
{
private:
	static ViewLog* viewLog;
	static Inventory* inventory;

	const int positionX = 260;
	const int positionY = 0;
	const int indentX = 10;
	const int indentY = 0;
	const int hMenu = 30;
	const int wMenu = 120;
	const int countMenu = 4;
	const int countBut = 2;
	const int hBut = 30;
	const int wBut = 30;

	Fl_Group* group;

	Fl_Button* b_Undo;
	Fl_Button* b_Redu;

	Fl_Menu_Item* drawingModes;
	Fl_Menu_Button* drawingModes_b;

	Fl_Menu_Item* objects;
	Fl_Menu_Button* createObject_b;

	Fl_Menu_Item* toolingRed;
	Fl_Menu_Button* redaction_b;

	Fl_Menu_Item* requirements;
	Fl_Menu_Button* createRequirement_b;

	static void cl_DrawingModes(Fl_Widget*, void*);

	static void cl_Create(Fl_Widget*, void*);

	static void cl_Redaction(Fl_Widget*, void*);

	static void cl_Requirement(Fl_Widget*, void*);

	static void cl_Button(Fl_Widget*, void*);

	void Initializer();
public:
	ViewToolbar();

	~ViewToolbar();

	void SetRequirements(const Array<string>&);

	void ClearRequirements();
};

#endif