#ifndef __VIEW_FILE
#define __VIEW_FILE

#include "ViewHeaders.h"
#include "ViewLog.h"

class ViewFile
{
private:
	static ViewLog* viewLog;

	const int positionX = 10;
	const int positionY = 0;
	const int indentX = 10;
	const int indentY = 0;
	const int hBut = 30;
	const int wBut = 70;
	const int countBut = 3;

	Fl_Group* group;
	Fl_Button* execute_script_b;
	Fl_Button* save_b;
	Fl_Button* downland_b;
	void Initializer();

	static void cl_execute_script_b(Fl_Widget*, void*);

	static void cl_SaveProject(Fl_Widget*, void*);

	static void cl_DownloadFile(Fl_Widget*, void*);
public:
	ViewFile();

	~ViewFile();
};

#endif __VIEW_FILE
