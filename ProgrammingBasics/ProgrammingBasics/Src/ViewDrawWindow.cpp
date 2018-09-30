#include "ViewDrawWindow.h"

void DrawWindow::draw()
{
	fl_color(FL_BLACK);
	fl_rectf(0, 0, w(), h());

	fl_push_matrix();
	fl_translate(translateScene->x, translateScene->y);
	fl_scale(scaleScene);
	fl_rotate(rotateScene);
	Presenter::DrawScene();
	fl_pop_matrix();
}

DrawWindow::DrawWindow(int x, int y, int w, int h, const char *l)
	: Fl_Double_Window(x, y, w, h, l)
{
	box(FL_UP_BOX);
	color(FL_BLACK);

	resizable(this);
	viewLog = viewLog->GetInstance();
	inventory = inventory->GetInstance();
}

DrawWindow::~DrawWindow() {}

int DrawWindow::handle(int e)
{

	Array<double> params;
	switch (e)
	{
	case FL_PUSH: {
		if (inventory->currentWindget != nullptr)
		{
			delete inventory->currentWindget;
			inventory->currentWindget = nullptr;
			redraw();//
		}
		fl_cursor(*(inventory->lastCursor));
		params.PushBack((Fl::event_x() - translateScene->x) / scaleScene);
		params.PushBack((Fl::event_y() - translateScene->y) / scaleScene);
		if (Fl::event_button() == FL_RIGHT_MOUSE)
		{
			Presenter::Set_event(ev_rightMouseDown, params);
		}
		if (Fl::event_button() == FL_LEFT_MOUSE)
		{
			Presenter::Set_event(ev_leftMouseDown, params);
		}
		break;
	}
	case FL_RELEASE: {
		fl_cursor(FL_CURSOR_DEFAULT);
		params.PushBack((Fl::event_x() - translateScene->x) / scaleScene);
		params.PushBack((Fl::event_y() - translateScene->y) / scaleScene);
		Presenter::Set_event(ev_leftMouseUp, params);
		break;
	}
	case FL_MOUSEWHEEL: {
		params.PushBack(Fl::event_dy());
		Presenter::Set_event(ev_scroll, params);
		break;
	}
	case FL_ENTER: {
		//fl_cursor(*(inventory->lastCursor));
		break;
	}
	case FL_LEAVE: {
		fl_cursor(FL_CURSOR_DEFAULT);
		break;
	}
	case FL_KEYDOWN: {
		if (inventory->currentWindget != nullptr)
		{
			delete inventory->currentWindget;
			inventory->currentWindget = nullptr;
			redraw();//
		}
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
	case FL_MOVE: {
		fl_cursor(*(inventory->lastCursor));
		params.PushBack((Fl::event_x() - translateScene->x) / scaleScene);
		params.PushBack((Fl::event_y() - translateScene->y) / scaleScene);
		Presenter::Set_event(ev_mouseMove, params);
		break;
	}
	case FL_DRAG: {
		/*if (*(inventory->lastCursor) == FL_CURSOR_DEFAULT)
		{
			fl_cursor(FL_CURSOR_CROSS);
		}*/
		params.PushBack((Fl::event_x() - translateScene->x) / scaleScene);
		params.PushBack((Fl::event_y() - translateScene->y) / scaleScene);
		Presenter::Set_event(ev_mouseMove, params);
		break;
	}
	}
	return e;
}

void DrawWindow::TranslateScene(const Vector2& deltaCor)
{
	if ((translateScene->x + deltaCor.x >= 0) && (translateScene->y + deltaCor.y >= 0)) {
		*translateScene += deltaCor;
	}
}

void DrawWindow::ScaleScene(const double& deltaCoef)
{
	if ((scaleScene + deltaCoef > 0.1) && (scaleScene + deltaCoef < 10))
	{
		scaleScene += deltaCoef;
	}
}

void DrawWindow::RotateScene(const double& deltaAngle)
{
	rotateScene += deltaAngle;
}

ViewLog* DrawWindow::viewLog = nullptr;

Inventory* DrawWindow::inventory = nullptr;

Vector2* DrawWindow::translateScene = new Vector2(0.0, 0.0);

double DrawWindow::scaleScene = 1.0;

double DrawWindow::rotateScene = 0.0;