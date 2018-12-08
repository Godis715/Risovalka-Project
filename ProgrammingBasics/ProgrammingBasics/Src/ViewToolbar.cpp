#include "ViewToolbar.h"

void ViewToolbar::cl_DefualtDrawMode(Fl_Widget* o, void*)
{
	delete inventory->lastCursor;
	inventory->lastCursor = new Fl_Cursor(FL_CURSOR_DEFAULT);
	Array<double> params(0);
	presenter->Set_event(ev_defualtDraw, params);
}

void ViewToolbar::cl_xSymmetricDrawMode(Fl_Widget* o, void*)
{
	Array<double> params(0);
	string nameMode = ((Fl_Menu_Button*)o)->mvalue()->label();
	if (nameMode[0] == 'y') {
		nameMode[1] = '1';
	}
	nameMode[0] = '0';
	params.PushBack(std::stod(nameMode));
	presenter->Set_event(ev_symmetricalDraw, params);
}

void ViewToolbar::cl_xRotateDrawMode(Fl_Widget* o, void*)
{
	Array<double> params(0);
	string nameMode = ((Fl_Menu_Button*)o)->mvalue()->label();
	nameMode[0] = '0';
	params.PushBack(std::stod(nameMode));
	presenter->Set_event(ev_rotationDraw, params);
}

void ViewToolbar::cl_FastRequirement(Fl_Widget* o, void*) {
	delete inventory->lastCursor;
	inventory->lastCursor = new Fl_Cursor(FL_CURSOR_DEFAULT);
	Array<double> params(0);
	const string nameMode = ((Fl_Menu_Button*)o)->mvalue()->label();
	if (nameMode == "Points distance") {
		presenter->Set_event(ev_req_D_point_fast, params);
	}
	if (nameMode == "Merge points") {
		presenter->Set_event(ev_req_Eq_point_fast, params);
	}
}

void ViewToolbar::cl_Create(Fl_Widget* o, void*)
{
	delete inventory->lastCursor;
	inventory->lastCursor = new Fl_Cursor(FL_CURSOR_DEFAULT);
	Array<double> params(0);
	if (((Fl_Menu_Button*)o)->mvalue()->label() == "Point")
	{
		viewLog->Push("Log::Create point");
		presenter->Set_event(ev_createPoint, params);
		inventory->lastEvent = ev_createPoint;
	}
	if (((Fl_Menu_Button*)o)->mvalue()->label() == "Segment")
	{
		viewLog->Push("Log::Create segment");
		presenter->Set_event(ev_createSegment, params);
		inventory->lastEvent = ev_createSegment;
	}
	if (((Fl_Menu_Button*)o)->mvalue()->label() == "Star")
	{
		viewLog->Push("Log::Create Star line");
		presenter->Set_event(ev_createStar, params);
		inventory->lastEvent = ev_createStar;
	}
	if (((Fl_Menu_Button*)o)->mvalue()->label() == "Broken")
	{
		viewLog->Push("Log::Create broken line");
		presenter->Set_event(ev_createBrokenLine, params);
		inventory->lastEvent = ev_createBrokenLine;
	}
	if (((Fl_Menu_Button*)o)->mvalue()->label() == "Arc")
	{
		viewLog->Push("Log::Create arc");
		presenter->Set_event(ev_createArc, params);
		inventory->lastEvent = ev_createArc;
	}
	if (((Fl_Menu_Button*)o)->mvalue()->label() == "Curve")
	{
		viewLog->Push("Log::Create Curve");
		presenter->Set_event(ev_createCurve, params);
		inventory->lastEvent = ev_createCurve;
	}
	if (((Fl_Menu_Button*)o)->mvalue()->label() == "Circle")
	{
		viewLog->Push("Log::Create circle");
		presenter->Set_event(ev_createCircle, params);
		inventory->lastEvent = ev_createCircle;
	}
}

void ViewToolbar::cl_Redaction(Fl_Widget* o, void*)
{
	delete inventory->lastCursor;
	inventory->lastCursor = new Fl_Cursor(FL_CURSOR_DEFAULT);
	Array<double> params(0);
	auto name = ((Fl_Menu_Button*)o)->mvalue()->label();

	if (name == "Move selection")
	{
		viewLog->Push("Log::Move selection");
		delete inventory->lastCursor;
		inventory->lastCursor = new Fl_Cursor(FL_CURSOR_MOVE);
		presenter->Set_event(ev_moveObjects, params);
	}

	if (name == "Scale selection")
	{
		viewLog->Push("Log::Scale selection");
		presenter->Set_event(ev_scaleObjects, params);
	}

	if (name == "Rotate selection")
	{
		viewLog->Push("Log::Scale selection");
		presenter->Set_event(ev_rotateObjects, params);
	}

	if (name == "Delete selection")
	{
		viewLog->Push("Log::Delete selection");
		presenter->Set_event(ev_del, params);
	}

	if (name == "Delete all scene")
	{
		viewLog->Push("Log::Delete all scene");
		presenter->Set_event(ev_delAll, params);
		presenter->CleareScene();
	}
}

void ViewToolbar::cl_Requirement(Fl_Widget* b_Req, void*)
{
	delete inventory->lastCursor;
	inventory->lastCursor = new Fl_Cursor(FL_CURSOR_DEFAULT);
	Array<double> params(0);
	const string nameReq = ((Fl_Menu_Button*)b_Req)->mvalue()->label();
	if (nameReq == "Dist points")
	{
		viewLog->Push("Log::Create requirement: Dist points");
		presenter->Set_event(ev_req_D_point, params);
	}
	if (nameReq == "Equal segment")
	{
		viewLog->Push("Log::Create requirement: Equal segment");
		presenter->Set_event(ev_req_Eq_Segment, params);
	}
	if (nameReq == "Points on one hand")
	{
		viewLog->Push("Log::Create requirement: Points on one hand");
		presenter->Set_event(ev_req_on_one_hand, params);
	}
	if (nameReq == "Dist point segment")
	{
		viewLog->Push("Log::Create requirement: Dist point segment");
		presenter->Set_event(ev_req_D_point_segment, params);
	}
	if (nameReq == "Dist point arc")
	{
		viewLog->Push("Log::Create requirement: Dist point arc");
		presenter->Set_event(ev_req_D_point_arc, params);
	}
	if (nameReq == "Angle between segment")
	{
		viewLog->Push("Log::Create requirement: Angle between segment");
		presenter->Set_event(ev_req_angle_segment, params);
	}

}

void ViewToolbar::cl_Button(Fl_Widget* but, void*)
{
	Array<double> params(0);
	const string nameBut = ((Fl_Button*)but)->label();
	if (nameBut == "<--")presenter->Set_event(ev_undo, params);
	if (nameBut == "-->")presenter->Set_event(ev_redu, params);
}

void ViewToolbar::Initializer()
{
	int hGroup = 2 * indentY + hMenu;
	int wGroup = (countMenu * wMenu + (countMenu + 1) * indentX) + (countBut * wBut + (countBut + 1) * indentX);
	group = new Fl_Group(positionX, positionY, wGroup, hGroup);

	int coordX = positionX + indentX;
	b_Undo = new Fl_Button(coordX, positionY + indentY, wBut, hBut, "<--");
	b_Undo->color(FL_RED);
	b_Undo->callback(cl_Button);
	b_Undo->clear_visible_focus();

	coordX += (wBut + indentX);
	b_Redu = new Fl_Button(coordX, positionY + indentY, wBut, hBut, "-->");
	b_Redu->color(FL_GREEN);
	b_Redu->callback(cl_Button);
	b_Redu->clear_visible_focus();

	coordX += (wBut + indentX);
	{
		drawingModes = new Fl_Menu_Item[18];
		drawingModes[0] = { "Defualt", 0, cl_DefualtDrawMode, 0 , 0 };
		drawingModes[1] = { "Symmetrical", 0, 0, 0, FL_SUBMENU };
			drawingModes[2] = { "y2", 0, cl_xSymmetricDrawMode, 0, 0 };
			drawingModes[3] = { "x2", 0, cl_xSymmetricDrawMode, 0, 0 };
			drawingModes[4] = { "x4", 0, cl_xSymmetricDrawMode, 0, 0 };
			drawingModes[5] = { "x8", 0, cl_xSymmetricDrawMode, 0, 0 };
			drawingModes[6] = { 0 };
		drawingModes[7] = { "Rotation", 0, 0, 0, FL_SUBMENU };
			drawingModes[8] = { "x2", 0, cl_xRotateDrawMode, 0, 0 };
			drawingModes[9] = { "x3", 0, cl_xRotateDrawMode, 0, 0 };
			drawingModes[10] = { "x4", 0, cl_xRotateDrawMode, 0, 0 };
			drawingModes[11] = { "x5", 0, cl_xRotateDrawMode, 0, 0 };
			drawingModes[12] = { "x6", 0, cl_xRotateDrawMode, 0, 0 };
			drawingModes[13] = { "x8", 0, cl_xRotateDrawMode, 0, 0 };
			drawingModes[14] = { "x9", 0, cl_xRotateDrawMode, 0, 0 };
			drawingModes[15] = { "x10", 0, cl_xRotateDrawMode, 0, 0 };
		drawingModes[16] = { 0 };
		drawingModes[17] = { 0 };
		drawingModes_b = new  Fl_Menu_Button(coordX, positionY + indentY, wMenu, hMenu, "DrawingModes");
		drawingModes_b->menu(drawingModes);
		drawingModes_b->clear_visible_focus();
		drawingModes_b->color(FL_WHITE);
	}
	coordX += (wMenu + indentX);
	{
		objects = new Fl_Menu_Item[8];
		objects[0] = { "Point", FL_ALT + 'z' };
		objects[1] = { "Segment", FL_ALT + 'x' };
		objects[2] = { "Star", FL_ALT + 's' };
		objects[3] = { "Broken", FL_ALT + 'b' };
		objects[4] = { "Arc", FL_ALT + 'c' };
		objects[5] = { "Circle", FL_ALT + 'v' };
		objects[6] = { "Curve", FL_ALT + 'r' };
		objects[7] = { 0 };
		createObject_b = new  Fl_Menu_Button(coordX, positionY + indentY, wMenu, hMenu, "Object");
		createObject_b->menu(objects);
		createObject_b->callback(cl_Create);
		createObject_b->clear_visible_focus();
		createObject_b->color(FL_WHITE);
	}
	coordX += (wMenu + indentX);
	{
		toolingRed = new Fl_Menu_Item[6];
		toolingRed[0] = { "Move selection" };
		toolingRed[1] = { "Scale selection" };
		toolingRed[2] = { "Rotate selection" };
		toolingRed[3] = { "Delete selection" };
		toolingRed[4] = { "Delete all scene" };
		toolingRed[5] = { 0 };
		redaction_b = new  Fl_Menu_Button(coordX, positionY + indentY, wMenu, hMenu, "Redaction");
		redaction_b->menu(toolingRed);
		redaction_b->callback(cl_Redaction);
		redaction_b->clear_visible_focus();
		redaction_b->color(FL_WHITE);
	}
	coordX += (wMenu + indentX);
	{
		requirements = new Fl_Menu_Item[1];
		requirements[0] = { 0 };
		createRequirement_b = new  Fl_Menu_Button(coordX, positionY + indentY, wMenu, hMenu, "Requirement");
		createRequirement_b->menu(requirements);
		createRequirement_b->callback(cl_Requirement);
		createRequirement_b->clear_visible_focus();
		createRequirement_b->color(FL_WHITE);
	}
	coordX += (wMenu + indentX);
	{
		fastRequirements = new Fl_Menu_Item[3];
		fastRequirements[0] = { "Points distance" };
		fastRequirements[1] = { "Merge points" };
		fastRequirements[2] = { 0 };
		createFastRequirement_b = new Fl_Menu_Button(coordX, positionY + indentY, wMenu, hMenu, "FastTool");
		createFastRequirement_b->menu(fastRequirements);
		createFastRequirement_b->callback(cl_FastRequirement);
		createFastRequirement_b->clear_visible_focus();
		createFastRequirement_b->color(FL_WHITE);
	}
	group->box(FL_UP_BOX);
	group->color(fl_rgb_color(0, 140, 240)); // цвет "Аква"
	group->end();
}

ViewToolbar::ViewToolbar()
{
	presenter = Presenter::GetInstance();
	viewLog = viewLog->GetInstance();
	inventory = inventory->GetInstance();
	Initializer();
}

ViewToolbar::~ViewToolbar() {}

/*
"Dist points"
"Equal segment"
"Points on one hand"
"Dist point segment"
"Dist point arc"
"Angle between segment"
*/
void ViewToolbar::SetRequirements(const Array<string>& nameReqs)
{
	if (nameReqs.GetSize() != 0)
	{
		delete[] requirements;
		requirements = new Fl_Menu_Item[nameReqs.GetSize() + 1];
		for (int i = 0; i < nameReqs.GetSize(); i++)
		{
			requirements[i] = { str_ch(nameReqs[i]) };
		}
		requirements[nameReqs.GetSize()] = { 0 };
		createRequirement_b->menu(requirements);
	}
	else ClearRequirements();
}

void ViewToolbar::ClearRequirements()
{
	delete[] requirements;
	requirements = new Fl_Menu_Item[1];
	requirements[0] = { 0 };
	createRequirement_b->menu(requirements);
}

ViewLog* ViewToolbar::viewLog = nullptr;

Inventory* ViewToolbar::inventory = nullptr;

Presenter* ViewToolbar::presenter = nullptr;