#include "ViewFile.h"

void ViewFile::Initializer()
{
	viewLog = ViewLog::GetInstance();
	colorThemes = Color::GetInstance();

	int hGroup = 2 * indentY + hBut;
	int wGroup = 0;
	wGroup += (indentX + wTheme_m);
	wGroup += (indentX + wScript_b);
	wGroup += (indentX + wSave_b);
	wGroup += (indentX + wDownland_b + indentX);
	group = new Fl_Group(positionX, positionY, wGroup, hGroup);

	int coordX = positionX + indentX;
	themes = new Fl_Menu_Item[4];
	themes[0] = { "Dark" };
	themes[1] = { "Light" };
	themes[2] = { "Neutral" };
	themes[3] = { 0 };
	theme_b = new  Fl_Menu_Button(coordX, positionY + indentY, wTheme_m, hBut, "Th");
	theme_b->menu(themes);
	theme_b->callback(cl_theme_b);
	theme_b->clear_visible_focus();
	theme_b->color(FL_WHITE);

	coordX += (wTheme_m + indentX);
	execute_script_b = new Fl_Button(coordX, positionY, wScript_b, hBut, "script");
	execute_script_b->callback(cl_execute_script_b);
	execute_script_b->color(FL_WHITE);

	coordX += (wScript_b + indentX);
	save_b = new Fl_Button(coordX, positionY, wSave_b, hBut, "Save");
	save_b->callback(cl_SaveProject);
	save_b->color(FL_WHITE);

	coordX += (wSave_b + indentX);
	downland_b = new Fl_Button(coordX, positionY, wDownland_b, hBut, "Download");
	downland_b->callback(cl_DownloadFile);
	downland_b->color(FL_WHITE);

	group->box(FL_UP_BOX);
	group->color(fl_rgb_color(255, 105, 180));
	group->end();
}

void ViewFile::cl_theme_b(Fl_Widget* o, void*)
{
	Array<double> params(1);
	params[0] = ((Fl_Menu_Button *)o)->value();
	Presenter::Set_event(ex_set_theme, params);
	Presenter::Set_event(ev_createPoint, params);
	Presenter::Set_event(ev_escape, params);
}

void ViewFile::cl_execute_script_b(Fl_Widget* o, void*)
{
	viewLog->Push("Log:Download script");
	Array<double> params(0);
	Presenter::Set_event(ev_compile, params);
	((Fl_Button*)o)->deactivate();
	((Fl_Button*)o)->activate();
}

void ViewFile::cl_SaveProject(Fl_Widget* o, void*)
{
	Array<double> params(0);
	viewLog->Push("Log:Save file");
	Presenter::Set_event(ev_save, params, "project.svg");
	((Fl_Button*)o)->deactivate();
	((Fl_Button*)o)->activate();
}

void ViewFile::cl_DownloadFile(Fl_Widget* o, void*)
{
	Array<double> params(0);
	viewLog->Push("Log:Download file");
	Presenter::Set_event(ev_download, params, "project.svg");
	((Fl_Button*)o)->deactivate();
	((Fl_Button*)o)->activate();
}

ViewFile::ViewFile()
{
	Initializer();
}

ViewFile::~ViewFile() {}

ViewLog* ViewFile::viewLog = nullptr;

Color* ViewFile::colorThemes = nullptr;