#include "ViewFile.h"

void ViewFile::Initializer()
{
	viewLog = viewLog->GetInstance();

	int hGroup = 2 * indentY + hBut;
	int wGroup = countBut * wBut + (countBut + 1) * indentX;

	group = new Fl_Group(positionX, positionY, wGroup, hGroup);

	int coordX = positionX + indentX;
	execute_script_b = new Fl_Button(coordX, positionY, wBut, hBut, "script");
	execute_script_b->callback(cl_execute_script_b);
	execute_script_b->color(FL_WHITE);

	coordX += (wBut + indentX);
	save_b = new Fl_Button(coordX, positionY, wBut, hBut, "Save");
	save_b->callback(cl_SaveProject);
	save_b->color(FL_WHITE);

	coordX += (wBut + indentX);
	downland_b = new Fl_Button(coordX, positionY, wBut, hBut, "Download");
	downland_b->callback(cl_DownloadFile);
	downland_b->color(FL_WHITE);

	group->box(FL_UP_BOX);
	group->color(fl_rgb_color(255, 105, 180));
	group->end();
}

void ViewFile::cl_execute_script_b(Fl_Widget* o, void*)
{
	viewLog->Push("Log:Download script");
	Presenter::Compile();
	((Fl_Button*)o)->deactivate();
	((Fl_Button*)o)->activate();
}

void ViewFile::cl_SaveProject(Fl_Widget* o, void*)
{
	viewLog->Push("Log:Save file");
	Presenter::SaveProject("way");
	((Fl_Button*)o)->deactivate();
	((Fl_Button*)o)->activate();
}

void ViewFile::cl_DownloadFile(Fl_Widget* o, void*)
{
	viewLog->Push("Log:Download file");
	Presenter::DownloadFile("nameFile");
	((Fl_Button*)o)->deactivate();
	((Fl_Button*)o)->activate();
}

ViewFile::ViewFile()
{
	Initializer();
}

ViewFile::~ViewFile() {}

ViewLog* ViewFile::viewLog = nullptr;