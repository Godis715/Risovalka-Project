#include "ViewFLTK.h"

double Parse(string number) {
	int countPoint = 0;
	if (number[0] == 'e' || number[0] == '.') {
		return -1;
	}

	for (size_t i = 1; i < number.length(); ++i) {
		if (number[i] == 'e' || number[i] == '-') {
			return -1;
		}
		if (number[i] == '.') {
			++countPoint;
			if (countPoint > 1) {
				return -1;
			}
		}
	}
	return stod(number);
}

const char* ReverseParse(const double dig, int& size)
{
	std::string strDig;
	std::ostringstream ost;
	ost << std::fixed << std::setprecision(2) << dig;
	strDig = ost.str();

	size = strDig.length();
	char* charDig = new char[size];
	for (int i = 0; i < size; i++)
	{
		charDig[i] = strDig[i];
	}
	return charDig;
}

ViewFLTK::ViewFLTK()
{

	Presenter::Initializer(this);
	mainWindow = new Fl_Window(1300, 620, "Main Window");
	mainWindow->color(FL_WHITE);
	mainWindow->size_range(600, 300);

	viewToolbar = new ViewToolbar();
	viewFile = new ViewFile();
	viewLog = ViewLog::GetInstance();
	drawWindow = new DrawWindow(10, 30, 1000, 600, "Draw Window");
	//drawWindow->end();

	mainWindow->end();

	mainWindow->show();
	drawWindow->show();
}

ViewFLTK::~ViewFLTK(){}

int ViewFLTK::Run() 
{
	return Fl::run(); 
}

void ViewFLTK::DrawLine(const Vector2& start, const Vector2& end, typeDrawing type)
{
	switch (type)
	{
	case points:
		fl_line_style(FL_DOT, 2);
		fl_begin_line();
		fl_vertex(start.x, start.y);
		fl_vertex(end.x, end.y);
		fl_end_line();
		break;
	case line:
		fl_begin_line();
		fl_vertex(start.x, start.y);
		fl_vertex(end.x, end.y);
		fl_end_line();
		break;
	default:
		fl_begin_line();
		fl_vertex(start.x, start.y);
		fl_vertex(end.x, end.y);
		fl_end_line();
		break;
	}
}

void ViewFLTK::DrawCircle(const Vector2& center, const Vector2& pointForCircle, typeDrawing type)
{
	double r = (pointForCircle - center).GetLength();

	switch (type)
	{
	case points:
		fl_begin_points();
		fl_arc(center.x, center.y, r, 0.0, 360.0);
		fl_end_points();
		break;
	case line:
		fl_begin_line();
		fl_arc(center.x, center.y, r, 0.0, 360.0);
		fl_end_line();
		break;
	case polygon:
		fl_begin_polygon();
		fl_arc(center.x, center.y, r, 0.0, 360.0);
		fl_end_polygon();
		break;
	}
}

void ViewFLTK::_DrawArc(const Vector2& center, double R, double angleStart, double angleEnd) {
	if (angleStart < angleEnd) {
		fl_arc(center.x, center.y, R, angleStart, angleEnd);
		return;
	}
	else {
		fl_arc(center.x, center.y, R, angleStart, 360.0);
		fl_arc(center.x, center.y, R, 0.0, angleEnd);
	}
}

void ViewFLTK::DrawArc(const Vector2& center, const Vector2& start, const Vector2& end, typeDrawing type)
{
	double EPS = 5.0;
	double r1 = (center - start).GetLength();
	double angleStart = (abs(r1) < EPS) ? 0.0 : acos((start.x - center.x) / r1) * (180 / PI);
	if (center.y - start.y < 0) {
		angleStart = 360.0 - angleStart;
	}

	double r2 = (center - end).GetLength();
	double angleEnd = (abs(r2) < EPS) ? 360.0 : acos((end.x - center.x) / r2) * (180 / PI);
	if (center.y - end.y < 0) {
		angleEnd = 360.0 - angleEnd;
	}

	switch (type)
	{
	case points:
		fl_begin_points();
		_DrawArc(center, r1, angleStart, angleEnd);
		fl_end_points();
		break;
	case line:
		fl_begin_line();
		_DrawArc(center, r1, angleStart, angleEnd);
		fl_end_line();
		break;
	case polygon:
		fl_begin_polygon();
		_DrawArc(center, r1, angleStart, angleEnd);
		fl_end_polygon();
		break;
	}
}

void ViewFLTK::DrawPoint(const Vector2& pos)
{
	int size = 2;
	fl_begin_line();
	fl_vertex(pos.x - size, pos.y - size);
	fl_vertex(pos.x + size, pos.y + size);
	fl_end_line();

	fl_begin_line();
	fl_vertex(pos.x + size, pos.y - size);
	fl_vertex(pos.x - size, pos.y + size);
	fl_end_line();
}

void ViewFLTK::SetColor(color col)
{
	switch (col)
	{
	case white:
		fl_color(FL_WHITE);
		break;
	case red:
		fl_color(FL_RED);
		break;
	case black:
		fl_color(FL_BLACK);
		break;
	case green:
		fl_color(FL_GREEN);
		break;
	case yellow:
		fl_color(FL_YELLOW);
		break;
	case blue:
		fl_color(FL_BLUE);
		break;
	case orange:
		fl_color(fl_rgb_color(255, 140, 0));
		break;
	}
}

void ViewFLTK::Update()
{
	drawWindow->redraw();
}

void ViewFLTK::GiveParams(const object_type type, const Array<double>& params,
	const Array<string>& Reqs, const Array<Array<double>>& reqParams)
{
	/*mainWindow->begin();
	if (displayParams != nullptr)
	{
		delete displayParams;
		displayParams = nullptr;
	}
	displayParams = new DisplayParams(type, params, Reqs, reqParams);
	mainWindow->end();
	mainWindow->redraw();*/
}

void ViewFLTK::DeleteDisplay()
{
	/*if (displayParams != nullptr)
	{
		delete ViewFLTK::displayParams;
		ViewFLTK::displayParams = nullptr;
		ViewFLTK::mainWindow->redraw();
	}*/
}

//for navigation on scene
void ViewFLTK::TranslateScene(const Vector2& deltaCor)
{
	drawWindow->TranslateScene(deltaCor);
}

void ViewFLTK::ScaleScene(const double& deltaCoef)
{
	drawWindow->ScaleScene(deltaCoef);
}

void ViewFLTK::RotateScene(const double& deltaAngle)
{
	drawWindow->RotateScene(deltaAngle);
}

ViewLog* ViewFLTK::viewLog = nullptr;

Fl_Window* ViewFLTK::mainWindow;

DrawWindow* ViewFLTK::drawWindow;