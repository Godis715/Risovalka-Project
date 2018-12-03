#include "ViewFLTK.h"
#include "FLTKWidget.h"

ViewFLTK::ViewFLTK()
{
	dataWidjet = new DataWidjet();

	inventory = inventory->GetInstance();

	mainWindow = new MainWindow(1300, 660, "Main Window");
	DisplayWidjet* mainWindowWidjet = mainWindow;
	dataWidjet->Add("MainWindow", mainWindowWidjet);

	DisplayWidjet* viewToolbar = new ViewToolbar();
	dataWidjet->Add("ToolBar", viewToolbar);

	DisplayWidjet* viewFile = new ViewFile();
	dataWidjet->Add("WorkFile", viewFile);

	DrawMode* drawMode = DrawMode::GetInstance();
	dataWidjet->Add("DrawMode", drawMode);

	viewLog = ViewLog::GetInstance();

	OutputCoord::GetInstance();
	
	drawWindow = new DrawWindow(10, 30, 1000, 600, "Draw Window");
	drawWindow->end();
	DisplayWidjet* drawWindowWidjet = drawWindow;
	dataWidjet->Add("DrawWindow", drawWindowWidjet);


	mainWindow->end();

	mainWindow->show();
	drawWindow->show();


}

ViewFLTK::~ViewFLTK(){}

ViewFLTK* ViewFLTK::GetInstance() {
	if (instance == nullptr) {
		instance = new ViewFLTK();
	}
	return instance;
}

int ViewFLTK::Run() 
{
	Presenter::Initializer(this);
	return Fl::run(); 
}

void ViewFLTK::SetTypeDrawing(int r, int g, int b, typeDrawing type)
{
	fl_color(fl_rgb_color(r, g, b));
	switch (type)
	{
	case dot:
		fl_line_style(FL_DOT, 2);
		break;
	case dash:
		fl_line_style(FL_DASH, 1);
		break;
	case solid:
		fl_line_style(FL_SOLID, 1);
		break;
	default:
		break;
	}
}

void ViewFLTK::DrawLine(const Vector2& start, const Vector2& end)
{
	fl_begin_line();
	fl_vertex(start.x, start.y);
	fl_vertex(end.x, end.y);
	fl_end_line();
}
void ViewFLTK::DrawLine(const Array<double>& params)
{
	fl_begin_line();
	fl_vertex(params[0], params[1]);
	fl_vertex(params[2], params[3]);
	fl_end_line();
}

void ViewFLTK::DrawCircle(const Vector2& center, const Vector2& pointForCircle)
{
	double r = (pointForCircle - center).GetLength();
	fl_begin_line();
	fl_arc(center.x, center.y, r, 0.0, 360.0);
	fl_end_line();
}
void ViewFLTK::DrawCircle(const Array<double>& params)
{
	fl_begin_line();
	fl_arc(params[0], params[1], params[2], 0.0, 360.0);
	fl_end_line();
}

void ViewFLTK::_DrawArc(const Vector2& center, double R, double angleStart, double angleEnd) {
	if (angleStart < angleEnd) {
		fl_arc(center.x, center.y, R, angleStart, angleEnd);
	}
	else {
		fl_arc(center.x, center.y, R, angleStart, 360.0);
		fl_arc(center.x, center.y, R, 0.0, angleEnd);
	}
}

void ViewFLTK::DrawArc(const Vector2& center, const Vector2& start, const Vector2& end)
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

	fl_begin_line();
	_DrawArc(center, r1, angleStart, angleEnd);
	fl_end_line();
}
void ViewFLTK::DrawArc(const Array<double>& params)
{
	double EPS = 5.0;
	double r = params[6];
	double angle = params[7] * (180 / PI);
	double angleStart = (r < EPS) ? 0.0 : acos((params[0] - params[4]) / r) * (180 / PI);
	if (params[5] - params[1] < 0) {
		angleStart = 360.0 - angleStart;
	}
	fl_begin_line();
	_DrawArc(Vector2(params[4], params[5]), r, angleStart, angleStart + angle);
	fl_end_line();
}

void ViewFLTK::DrawPoint(const Vector2& pos)
{
	int size = 2;
	fl_begin_polygon();
	fl_arc(pos.x, pos.y, size, 0.0, 360.0);
	fl_end_polygon();
}
void ViewFLTK::DrawPoint(const Array<double>& params)
{
	fl_begin_polygon();
	fl_arc(params[0], params[1], 2, 0.0, 360.0);
	fl_end_polygon();
}

void ViewFLTK::DrawCurve(const Array<Vector2>& points)
{
	fl_begin_line();
	if (points.GetSize() == 2) {
		fl_vertex(points[0].x, points[0].y);
		fl_vertex(points[1].x, points[1].y);
		fl_end_line();
		return;
	}
	double x0 = points[0].x;
	double y0 = points[0].y;
	double x1;
	double y1;
	double x2;
	double y2;
	double x3;
	double y3;
	double x4;
	double y4;
	int size = points.GetSize();
	for (int i = 0; i < size; ++i) {
		if (size - i == 4) {
			x1 = points[i + 1].x;
			y1 = points[i + 1].y;
			x2 = points[i + 2].x;
			y2 = points[i + 2].y;
			x3 = points[i + 3].x;
			y3 = points[i + 3].y;
			fl_curve(x0, y0, x1, y1, x2, y2, x3, y3);
			i += 2;
		}
		if (size - i == 3) {
			x1 = points[i + 1].x;
			y1 = points[i + 1].y;
			x2 = points[i + 2].x;
			y2 = points[i + 2].y;
			fl_curve(x0, y0, x1, y1, x2, y2, x2, y2);
			i += 1;
		}
		if (size - i > 4) {
			x1 = points[i + 1].x;
			y1 = points[i + 1].y;
			x2 = points[i + 2].x;
			y2 = points[i + 2].y;
			x3 = points[i + 3].x;
			y3 = points[i + 3].y;
			x3 = (x2 + x3) / 2;
			y3 = (y2 + y3) / 2;
			fl_curve(x0, y0, x1, y1, x2, y2, x3, y3);
			x0 = x3;
			y0 = y3;
			i += 1;
		}
	}
	fl_end_line();
}
void ViewFLTK::DrawCurve(const Array<double>& points) {
	fl_begin_line();
	if (points.GetSize() == 4) {
		fl_vertex(points[0], points[1]);
		fl_vertex(points[2], points[3]);
		fl_end_line();
		return;
	}
	double x0 = points[0];
	double y0 = points[1];
	double x1;
	double y1;
	double x2;
	double y2;
	double x3;
	double y3;
	double x4;
	double y4;
	int size = points.GetSize();
	for (int i = 2; i < size; i += 2) {
		if (size - i == 6) {
			x1 = points[i];
			y1 = points[i + 1];
			x2 = points[i + 2];
			y2 = points[i + 3];
			x3 = points[i + 4];
			y3 = points[i + 5];
			fl_curve(x0, y0, x1, y1, x2, y2, x3, y3);
			i += 4;
		}
		if (size - i == 4) {
			x1 = points[i];
			y1 = points[i + 1];
			x2 = points[i + 2];
			y2 = points[i + 3];
			fl_curve(x0, y0, x1, y1, x2, y2, x2, y2);
			i += 2;
		}
		if (size - i > 8) {
			x1 = points[i];
			y1 = points[i + 1];
			x2 = points[i + 2];
			y2 = points[i + 3];
			x3 = points[i + 4];
			y3 = points[i + 5];
			x3 = (x2 + x3) / 2;
			y3 = (y2 + y3) / 2;
			fl_curve(x0, y0, x1, y1, x2, y2, x3, y3);
			x0 = x3;
			y0 = y3;
			i += 2;
		}
	}
	fl_end_line();
}

void ViewFLTK::Update()
{
	drawWindow->redraw();
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

IWidjet* ViewFLTK::GetWidjet(const typeWidjet typeW)
{
	IWidjet* widjet;
	mainWindow->begin();
	switch (typeW)
	{
	case displayParamPrim:
	{
		DisplayParamsPrim* displayParamsPrim = new DisplayParamsPrim();
		dataWidjet->Add("DisplayParamsPrim", displayParamsPrim);
		widjet = new FLTKDisplayParamPrim("DisplayParamsPrim");
		break;
	}
	case displayParamReq:
	{
		auto displayParamsPrim = dynamic_cast<DisplayParamsPrim*>(GetWidjet("DisplayParamsPrim"));
		Array<int> paramsDisp;
		displayParamsPrim->GetParamDisplay(paramsDisp);
		int coordX = paramsDisp[0];
		int coordY = paramsDisp[1] + paramsDisp[3] + 20;
		DisplayParamsReq* displayParamsReq = new DisplayParamsReq(coordX, coordY);
		dataWidjet->Add("DisplayParamsReq", displayParamsReq);
		widjet = new FLTKDisplayParamReq("DisplayParamsReq");
		break;
	}
	case creatingToolbar:
	{
		widjet = new FLTKCreatingToolbar("ToolBar");
		break;
	}
	case requirementInput:
	{
		RequirementInput* requirementInput = new RequirementInput();
		dataWidjet->Add("RequirementInput", requirementInput);
		widjet = new FLTKRequirementInput("RequirementInput");
		break;
	}
	case drawMode:
	{
		widjet = new FLTKDrawMode("DrawMode");
		break;
	}
	default:
		widjet = nullptr;
		break;
	}
	mainWindow->end();
	mainWindow->redraw();
	return widjet;
}

DisplayWidjet* ViewFLTK::GetWidjet(const string nameWidjet)
{
	auto markerDataWidjet = dataWidjet->Find(nameWidjet);

	return *markerDataWidjet; // исключение!
}

void ViewFLTK::DeleteWidjet(const string nameWidjet) {
	auto markerDataWidjet = dataWidjet->Find(nameWidjet);
	if (markerDataWidjet.IsValid()) {
		delete (markerDataWidjet.operator*());
		markerDataWidjet.Delete();
		mainWindow->redraw();
	}
	else {
		// $$$
	}
}




Inventory* ViewFLTK::inventory = nullptr;

ViewLog* ViewFLTK::viewLog = nullptr;

MainWindow* ViewFLTK::mainWindow;

DrawWindow* ViewFLTK::drawWindow;

ViewFLTK* ViewFLTK::instance = nullptr;