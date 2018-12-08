#include "ViewMainWindow.h"

MainWindow::MainWindow(int x, int y, const char* name) : Fl_Window(x, y, name) 
{
	presenter = Presenter::GetInstance();
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
		if (Fl::event_key() == FL_Enter && inventory->lastEvent == ev_altDown)
		{
			if (fullscreen_active())
			{
				fullscreen_off();
			}
			else fullscreen();
		}
		if (Fl::event_key() == FL_Down)
		{
			presenter->Set_event(ev_arrowDown, params);
		}
		
		if (Fl::event_key() == FL_Up)
		{
			presenter->Set_event(ev_arrowUp, params);
		}
		if (Fl::event_key() == FL_Left)
		{
			presenter->Set_event(ev_arrowLeft, params);
		}
		if (Fl::event_key() == FL_Right)
		{
			presenter->Set_event(ev_arrowRight, params);
		}
		if (Fl::event_key() == FL_Control_L && inventory->lastEvent != ev_ctrlDown)
		{
			presenter->Set_event(ev_ctrlDown, params);
			inventory->lastEvent = ev_ctrlDown;
		}
		if ((Fl::event_key() == FL_Alt_L or Fl::event_key() == FL_Alt_R) && inventory->lastEvent != ev_altDown)
		{
			presenter->Set_event(ev_altDown, params);
			inventory->lastEvent = ev_altDown;
		}
		if (Fl::event_key() == FL_Escape)
		{
			delete inventory->lastCursor;
			inventory->lastCursor = new Fl_Cursor(FL_CURSOR_DEFAULT);
			inventory->lastEvent = ev_ctrlUp;
			presenter->Set_event(ev_escape, params);
		}
		if (Fl::event_key() == FL_Enter)
		{
			delete inventory->lastCursor;
			inventory->lastCursor = new Fl_Cursor(FL_CURSOR_DEFAULT);
			presenter->Set_event(ev_enter, params);
		}
		if (Fl::event_key() == FL_Shift_L && inventory->lastEvent != ev_ctrlDown)
		{
			presenter->Set_event(inventory->lastEvent, params);
		}
		if (Fl::event_key() == FL_Delete)
		{
			viewLog->Push("Log::Delete selection");
			presenter->Set_event(ev_del, params);
		}

		break;
	}
	case FL_KEYUP: {
		if (Fl::event_key() == FL_Control_L)
		{
			presenter->Set_event(ev_ctrlUp, params);
			inventory->lastEvent = ev_ctrlUp;
		}
		if (Fl::event_key() == FL_Alt_L or Fl::event_key() == FL_Alt_R)
		{
			presenter->Set_event(ev_altUp, params);
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

Presenter* MainWindow::presenter = nullptr;