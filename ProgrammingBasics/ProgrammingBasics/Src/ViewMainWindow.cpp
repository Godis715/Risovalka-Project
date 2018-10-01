#include "ViewMainWindow.h"

MainWindow::MainWindow(int x, int y, const char* name) : Fl_Window(x, y, name) 
{
	color(FL_WHITE);
	size_range(600, 300);
	inventory = inventory->GetInstance();
	viewLog = ViewLog::GetInstance();
}

MainWindow::~MainWindow() {}

int MainWindow::handle(int e)
{
	Array<double> params;
	switch (e)
	{
	case FL_KEYDOWN: {

		viewLog->Push("KEYDOWN!");
		if (Fl::event_key() == FL_Down)
		{
			Presenter::Set_event(ev_arrowDown, params);
		}
		if (Fl::event_key() == FL_Up)
		{
			Presenter::Set_event(ev_arrowUp, params);
		}
		if (Fl::event_key() == FL_Left)
		{
			Presenter::Set_event(ev_arrowLeft, params);
		}
		if (Fl::event_key() == FL_Right)
		{
			Presenter::Set_event(ev_arrowRight, params);
		}
		if (Fl::event_key() == FL_Control_L && inventory->lastEvent != ev_ctrlDown)
		{
			Presenter::Set_event(ev_ctrlDown, params);
			inventory->lastEvent = ev_ctrlDown;
		}
		if (Fl::event_key() == FL_Alt_L && inventory->lastEvent != ev_altDown)
		{
			Presenter::Set_event(ev_altDown, params);
			inventory->lastEvent = ev_altDown;
		}
		if (Fl::event_key() == FL_Escape)
		{
			delete inventory->lastCursor;
			inventory->lastCursor = new Fl_Cursor(FL_CURSOR_DEFAULT);
			inventory->lastEvent = ev_ctrlUp;
			Presenter::Set_event(ev_escape, params);
		}
		if (Fl::event_key() == FL_Shift_L && inventory->lastEvent != ev_ctrlDown)
		{
			Presenter::Set_event(inventory->lastEvent, params);
		}
		if (Fl::event_key() == FL_Delete)
		{
			viewLog->Push("Log::Delete selection");
			Presenter::Set_event(ev_del, params);
		}

		break;
	}
	case FL_KEYUP: {
		if (Fl::event_key() == FL_Control_L)
		{
			Presenter::Set_event(ev_ctrlUp, params);
			inventory->lastEvent = ev_ctrlUp;
		}
		if (Fl::event_key() == FL_Alt_L)
		{
			Presenter::Set_event(ev_altUp, params);
			inventory->lastEvent = ev_altUp;
		}
		break;
	}
	default:
		break;
	}

	return Fl_Window::handle(e);

}

Inventory* MainWindow::inventory = nullptr;

ViewLog* MainWindow::viewLog = nullptr;
