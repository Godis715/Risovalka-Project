#include "ViewToolbar.h"

void ViewToolbar::cl_Create(Fl_Widget* o, void*)
{
	delete inventory->lastCursor;
	inventory->lastCursor = new Fl_Cursor(FL_CURSOR_DEFAULT);
	Array<double> params(0);
	if (((Fl_Menu_Button*)o)->mvalue()->label() == "Point")
	{
		viewLog->Push("Log::Create point");
		Presenter::Set_event(ev_createPoint, params);
		inventory->lastEvent = ev_createPoint;
	}
	if (((Fl_Menu_Button*)o)->mvalue()->label() == "Segment")
	{
		viewLog->Push("Log::Create segment");
		Presenter::Set_event(ev_createSegment, params);
		inventory->lastEvent = ev_createSegment;
	}
	if (((Fl_Menu_Button*)o)->mvalue()->label() == "Arc")
	{
		viewLog->Push("Log::Create arc");
		Presenter::Set_event(ev_createArc, params);
		inventory->lastEvent = ev_createArc;
	}
	if (((Fl_Menu_Button*)o)->mvalue()->label() == "Circle")
	{
		viewLog->Push("Log::Create circle");
		Presenter::Set_event(ev_createCircle, params);
		inventory->lastEvent = ev_createCircle;
	}
}

void ViewToolbar::cl_Redaction(Fl_Widget* o, void*)
{
	delete inventory->lastCursor;
	inventory->lastCursor = new Fl_Cursor(FL_CURSOR_DEFAULT);
	Array<double> params(0);

	if (((Fl_Menu_Button*)o)->mvalue()->label() == "Move selection")
	{
		viewLog->Push("Log::Move selection");
		delete inventory->lastCursor;
		inventory->lastCursor = new Fl_Cursor(FL_CURSOR_MOVE);
		Presenter::Set_event(ev_moveObjects, params);
	}

	if (((Fl_Menu_Button*)o)->mvalue()->label() == "Scale selection")
	{
		viewLog->Push("Log::Scale selection");
		Presenter::Set_event(ev_scaleObjects, params);
	}

	if (((Fl_Menu_Button*)o)->mvalue()->label() == "Delete selection")
	{
		viewLog->Push("Log::Delete selection");
		Presenter::Set_event(ev_del, params);
	}

	if (((Fl_Menu_Button*)o)->mvalue()->label() == "Delete all scene")
	{
		viewLog->Push("Log::Delete all scene");
		Presenter::CleareScene();
	}
}

void ViewToolbar::cl_Requirement(Fl_Widget* o, void*)
{
	delete inventory->lastCursor;
	inventory->lastCursor = new Fl_Cursor(FL_CURSOR_DEFAULT);
	Array<double> params(0);
	if (((Fl_Menu_Button*)o)->mvalue()->label() == "Dist points")
	{
		viewLog->Push("Log::Create requirement: Dist points");
		Presenter::Set_event(ev_req_D_point, params);
	}
	if (((Fl_Menu_Button*)o)->mvalue()->label() == "Equal segment")
	{
		viewLog->Push("Log::Create requirement: Equal segment");
		Presenter::Set_event(ev_req_Eq_Segment, params);
	}
	if (((Fl_Menu_Button*)o)->mvalue()->label() == "Points on one hand")
	{
		viewLog->Push("Log::Create requirement: Points on one hand");
		Presenter::Set_event(ev_req_on_one_hand, params);
	}
	if (((Fl_Menu_Button*)o)->mvalue()->label() == "Dist point segment")
	{
		viewLog->Push("Log::Create requirement: Dist point segment");
		Presenter::Set_event(ev_req_D_point_segment, params);
	}
	if (((Fl_Menu_Button*)o)->mvalue()->label() == "Dist point arc")
	{
		viewLog->Push("Log::Create requirement: Dist point arc");
		Presenter::Set_event(ev_req_D_point_arc, params);
	}
	if (((Fl_Menu_Button*)o)->mvalue()->label() == "Angle between segment")
	{
		viewLog->Push("Log::Create requirement: Angle between segment");
		Presenter::Set_event(ev_req_angle_segment, params);
	}

}

void ViewToolbar::Initializer()
{
	int hGroup = 2 * indentY + hBut;
	int wGroup = countBut * wBut + (countBut + 1) * indentX;
	int coordX = positionX + indentX;
	group = new Fl_Group(positionX, positionY, wGroup, hGroup);
	{
		objects = new Fl_Menu_Item[5];
		objects[0] = { "Point", FL_ALT + 'z' };
		objects[1] = { "Segment", FL_ALT + 'x' };
		objects[2] = { "Arc", FL_ALT + 'c' };
		objects[3] = { "Circle", FL_ALT + 'v' };
		objects[4] = { 0 };
		createObject_b = new  Fl_Menu_Button(coordX, indentY, wBut, hBut, "Object");
		createObject_b->menu(objects);
		createObject_b->callback(cl_Create);
		createObject_b->clear_visible_focus();
		createObject_b->color(FL_WHITE);
	}
	coordX += (wBut + indentX);
	{
		toolingRed = new Fl_Menu_Item[6];
		toolingRed[0] = { "Move selection" };
		toolingRed[1] = { "Scale selection" };
		toolingRed[2] = { "Delete selection" };
		toolingRed[3] = { "Delete all scene" };
		toolingRed[4] = { 0 };
		redaction_b = new  Fl_Menu_Button(coordX, indentY, wBut, hBut, "Redaction");
		redaction_b->menu(toolingRed);
		redaction_b->callback(cl_Redaction);
		redaction_b->clear_visible_focus();
		redaction_b->color(FL_WHITE);
	}
	coordX += (wBut + indentX);
	{
		requirements = new Fl_Menu_Item[7];
		requirements[0] = { "Dist points" };
		requirements[1] = { "Equal segment" };
		requirements[2] = { "Points on one hand" };
		requirements[3] = { "Dist point segment" };
		requirements[4] = { "Dist point arc" };
		requirements[5] = { "Angle between segment" };
		requirements[6] = { 0 };
		createRequirement_b = new  Fl_Menu_Button(coordX, indentY, wBut, hBut, "Requirement");
		createRequirement_b->menu(requirements);
		createRequirement_b->callback(cl_Requirement);
		createRequirement_b->clear_visible_focus();
		createRequirement_b->color(FL_WHITE);
	}
	group->box(FL_UP_BOX);
	group->color(fl_rgb_color(0, 140, 240)); // цвет "Аква"
	group->end();
}

ViewToolbar::ViewToolbar()
{
	viewLog = viewLog->GetInstance();
	inventory = inventory->GetInstance();
	Initializer();
}

ViewToolbar::~ViewToolbar() {}

ViewLog* ViewToolbar::viewLog = nullptr;

Inventory* ViewToolbar::inventory = nullptr;