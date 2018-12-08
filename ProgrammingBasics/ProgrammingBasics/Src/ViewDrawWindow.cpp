#include "ViewDrawWindow.h"

void DrawWindow::draw()
{
	//fl_color(FL_BLACK);
	rgbColor colorSc = colorScene->DrowWindow();
	fl_color(fl_rgb_color(colorSc.r, colorSc.g, colorSc.b));
	fl_rectf(0, 0, w(), h());

	fl_push_matrix();
	fl_translate(translateScene->x, translateScene->y);
	fl_scale(scaleScene);
	fl_rotate(rotateScene);
	presenter->DrawScene();
	fl_pop_matrix();
}

DrawWindow::DrawWindow(int x, int y, int w, int h, const char *l)
	: Fl_Double_Window(x, y, w, h, l)
{
	presenter = Presenter::GetInstance();
	colorScene = Color::GetInstance();
	rgbColor colorSc = colorScene->DrowWindow();
	box(FL_UP_BOX);
	color(fl_rgb_color(colorSc.r, colorSc.g, colorSc.b));

	drawCoord = new Fl_Output(520, 630, 200, 30);

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
		fl_cursor(*(inventory->lastCursor));
		params.PushBack((Fl::event_x() - translateScene->x) / scaleScene);
		params.PushBack((Fl::event_y() - translateScene->y) / scaleScene);
		if (Fl::event_button() == FL_RIGHT_MOUSE)
		{
			presenter->Set_event(ev_rightMouseDown, params);
		}
		if (Fl::event_button() == FL_LEFT_MOUSE)
		{
			presenter->Set_event(ev_leftMouseDown, params);
		}
		break;
	}
	case FL_RELEASE: {
		fl_cursor(FL_CURSOR_DEFAULT);
		params.PushBack((Fl::event_x() - translateScene->x) / scaleScene);
		params.PushBack((Fl::event_y() - translateScene->y) / scaleScene);
		presenter->Set_event(ev_leftMouseUp, params);
		break;
	}
	case FL_MOUSEWHEEL: {
		params.PushBack(Fl::event_dy());
		presenter->Set_event(ev_scroll, params);
		break;
	}
	case FL_ENTER: {
		fl_cursor(*(inventory->lastCursor));
		break;
	}
	case FL_LEAVE: {
		fl_cursor(FL_CURSOR_DEFAULT);
		break;
	}
	case FL_MOVE: {
		fl_cursor(*(inventory->lastCursor));
		params.PushBack((Fl::event_x() - translateScene->x) / scaleScene);
		params.PushBack((Fl::event_y() - translateScene->y) / scaleScene);
		std::string out = "x:" + ReverseParse(params[0]) + " y: " + ReverseParse(params[1]);
		OutputCoord::Push(str_ch(out));
		presenter->Set_event(ev_mouseMove, params);
		break;
	}
	case FL_DRAG: {
		/*if (*(inventory->lastCursor) == FL_CURSOR_DEFAULT)
		{
			fl_cursor(FL_CURSOR_CROSS);
		}*/
		params.PushBack((Fl::event_x() - translateScene->x) / scaleScene);
		params.PushBack((Fl::event_y() - translateScene->y) / scaleScene);
		presenter->Set_event(ev_mouseMove, params);
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

Color* DrawWindow::colorScene = nullptr;

Inventory* DrawWindow::inventory = nullptr;

Vector2* DrawWindow::translateScene = new Vector2(0.0, 0.0);

double DrawWindow::scaleScene = 1.0;

double DrawWindow::rotateScene = 0.0;

Presenter* DrawWindow::presenter;