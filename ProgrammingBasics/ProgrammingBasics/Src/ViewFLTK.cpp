#include "ViewFLTK.h"

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
void ViewFLTK::DrawLine(const Array<double>& params, typeDrawing type)
{
	switch (type)
	{
	case points:
		fl_line_style(FL_DOT, 2);
		fl_begin_line();
		fl_vertex(params[0], params[1]);
		fl_vertex(params[2], params[3]);
		fl_end_line();
		break;
	case line:
		fl_begin_line();
		fl_vertex(params[0], params[1]);
		fl_vertex(params[2], params[3]);
		fl_end_line();
		break;
	default:
		fl_begin_line();
		fl_vertex(params[0], params[1]);
		fl_vertex(params[2], params[3]);
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
		fl_line_style(FL_DOT, 2);
		fl_begin_line();
		fl_arc(center.x, center.y, r, 0.0, 360.0);
		fl_end_line();
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
void ViewFLTK::DrawCircle(const Array<double>& params, typeDrawing type)
{
	switch (type)
	{
	case points:
		fl_line_style(FL_DOT, 2);
		fl_begin_line();
		fl_arc(params[0], params[1], params[2], 0.0, 360.0);
		fl_end_line();
		break;
	case line:
		fl_begin_line();
		fl_arc(params[0], params[1], params[2], 0.0, 360.0);
		fl_end_line();
		break;
	case polygon:
		fl_begin_polygon();
		fl_arc(params[0], params[1], params[2], 0.0, 360.0);
		fl_end_polygon();
		break;
	}
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

void ViewFLTK::DrawArc(const Vector2& center, const Vector2& start, const Vector2& end, typeDrawing type)
{
	double Eps = 5.0;
	double r1 = (center - start).GetLength();
	double angleStart = (abs(r1) < Eps) ? 0.0 : acos((start.x - center.x) / r1) * (180 / PI);
	if (center.y - start.y < 0) {
		angleStart = 360.0 - angleStart;
	}

	double r2 = (center - end).GetLength();
	double angleEnd = (abs(r2) < Eps) ? 360.0 : acos((end.x - center.x) / r2) * (180 / PI);
	if (center.y - end.y < 0) {
		angleEnd = 360.0 - angleEnd;
	}

	switch (type)
	{
	case points:
		fl_line_style(FL_DOT, 1);
		fl_begin_line();
		_DrawArc(center, r1, angleStart, angleEnd);
		fl_end_line();
		break;
	case line:
		fl_line_style(FL_SOLID, 2);
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
void ViewFLTK::DrawArc(const Array<double>& params, typeDrawing type)
{
	double Eps = 5.0;
	double r = params[6];
	double angle = params[7] * (180 / PI);
	double angleStart = (r < Eps) ? 0.0 : acos((params[0] - params[4]) / r) * (180 / PI);
	if (params[5] - params[1] < 0) {
		angleStart = 360.0 - angleStart;
	}
	switch (type)
	{
	case points:
		fl_line_style(FL_DOT, 1);
		fl_begin_line();
		_DrawArc(Vector2(params[4], params[5]), r, angleStart, angleStart + angle);
		fl_end_line();
		break;
	case line:
		fl_line_style(FL_SOLID, 2);
		fl_begin_line();
		_DrawArc(Vector2(params[4], params[5]), r, angleStart, angleStart + angle);
		fl_end_line();
		break;
	case polygon:
		fl_begin_polygon();
		_DrawArc(Vector2(params[4], params[5]), r, angleStart, angleStart + angle);
		fl_end_polygon();
		break;
	}
}

void ViewFLTK::DrawPoint(const Vector2& pos)
{

	int size = 2;
	/*fl_begin_line();
	fl_vertex(pos.x - size, pos.y - size);
	fl_vertex(pos.x + size, pos.y + size);
	fl_end_line();

	fl_begin_line();
	fl_vertex(pos.x + size, pos.y - size);
	fl_vertex(pos.x - size, pos.y + size);
	fl_end_line();*/
	fl_begin_polygon();
	fl_arc(pos.x, pos.y, size, 0.0, 360.0);
	fl_end_polygon();

	//double x0 = 0;
	//double y0 = 0;
	//double x1 = 500;
	//double y1 = 400;
	//double x2 = 100;
	//double y2 = 250;
	//double x3 = 150;
	//double y3 = 200;

	//double x4 = x3;
	//double y4 = y3;
	//double x5 = 2 * x3 - x2;
	//double y5 = 2 * y3 - y2;
	//double x6 = x1 - 2 * x2 - 2 * x5;
	//double y6 = y1 - 2 * y2 - 2 * y5;
	//x6 = 400;
	//y6 = 100;
	//double x7 = 600;
	//double y7 = 300;

	//double x8 = x7;
	//double y8 = y7;
	//double x9 = 2 * x7 - x6;
	//double y9 = 2 * y7 - y6;
	//double x10 = x5 - 2 * x6 - 2 * x9;
	//double y10 = y5 - 2 * y6 - 2 * y9;
	//double x11= 800;
	//double y11 = 100;
	//x10 = x11;
	//y10 = y11;
	//SetColor(col_White);
	//fl_begin_line();
	//fl_vertex(x0, y0);
	//fl_vertex(x1, y1);
	//fl_end_line();

	//fl_begin_line();
	//fl_vertex(x1, y1);
	//fl_vertex(x2, y2);
	//fl_end_line();

	//fl_begin_line();
	//fl_vertex(x2, y2);
	//fl_vertex(x3, y3);
	//fl_end_line();

	//fl_begin_line();
	//fl_vertex(x4, y4);
	//fl_vertex(x3, y3);
	//fl_end_line();

	//fl_begin_line();
	//fl_vertex(x4, y4);
	//fl_vertex(x5, y5);
	//fl_end_line();

	//fl_begin_line();
	//fl_vertex(x5, y5);
	//fl_vertex(x6, y6);
	//fl_end_line();

	//fl_begin_line();
	//fl_vertex(x7, y7);
	//fl_vertex(x6, y6);
	//fl_end_line();

	//fl_begin_line();
	//fl_vertex(x7, y7);
	//fl_vertex(x8, y8);
	//fl_end_line();

	//fl_begin_line();
	//fl_vertex(x9, y9);
	//fl_vertex(x8, y8);
	//fl_end_line();

	//fl_begin_line();
	//fl_vertex(x9, y9);
	//fl_vertex(x10, y10);
	//fl_end_line();

	//fl_begin_line();
	//fl_vertex(x11, y11);
	//fl_vertex(x10, y10);
	//fl_end_line();

	//SetColor(col_Red);
	//fl_begin_line();
	//fl_curve(x0, y0, x1, y1, x2, y2, x3, y3);
	//fl_end_line();
	//SetColor(col_ForestGreen);
	//fl_begin_line();
	//fl_curve(x4, y4, x5, y5, x6, y6, x7, y7);
	//fl_end_line();
	//SetColor(col_Blue);
	//fl_begin_line();
	//fl_curve(x8, y8, x9, y9, x10, y10, x11, y11);
	//fl_end_line();
	//SetColor(col_Orange);
	//fl_begin_line();
	//fl_curve(x1, y1, x2, y2, x5, y5, x6, y6);
	//fl_end_line();

	/*double x0 = 0;
	double y0 = 0;
	double x1 = 160;
	double y1 = 550;
	double x2 = 380;
	double y2 = 100;
	double x3 = 540;
	double y3 = 0;

	double x4 = (x0 + x1) * 3 / 4;
	double y4 = (y0 + y1) * 3 / 4;
	double x5 = (x3 - x2) / 4 + x2;
	double y5 = (y2 + y3) * 3 / 4;
	double x6 = (x4 + x5) / 2;
	double y6 = (y4 + y5) / 2;

	SetColor(col_White);
	fl_begin_line();
	fl_vertex(x0, y0);
	fl_vertex(x1, y1);
	fl_end_line();

	fl_begin_line();
	fl_vertex(x1, y1);
	fl_vertex(x2, y2);
	fl_end_line();

	fl_begin_line();
	fl_vertex(x2, y2);
	fl_vertex(x3, y3);
	fl_end_line();

	fl_begin_line();
	fl_vertex(x4, y4);
	fl_vertex(x5, y5);
	fl_end_line();

	fl_begin_line();
	fl_vertex(x5, y5);
	fl_vertex(x6, y6);
	fl_end_line();

	SetColor(col_Red);
	fl_begin_line();
	fl_curve(x0, y0, x4, y4, x6, y6, x6, y6);
	fl_end_line();
	SetColor(col_ForestGreen);
	fl_begin_line();
	fl_curve(x6, y6, x6, y6, x5, y5, x3, y3);
	fl_end_line();
	SetColor(col_Blue);
	fl_begin_line();
	fl_curve(x0, y0, x1, y1, x2, y2, x3, y3);
	fl_end_line();*/
}
void ViewFLTK::DrawPoint(const Array<double>& params)
{
	fl_begin_polygon();
	fl_arc(params[0], params[1], 2, 0.0, 360.0);
	fl_end_polygon();
}

void ViewFLTK::DrawCurve(const Array<Vector2>& points, typeDrawing type)
{
	if (type == typeDrawing::points) {
		fl_line_style(FL_DOT, 2);
	}
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
void ViewFLTK::DrawCurve(const Array<double>& points, typeDrawing type) {
	if (type == typeDrawing::points) {
		fl_line_style(FL_DOT, 2);
	}
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

void ViewFLTK::DrawCurveNew(const Array<Vector2>& points, typeDrawing type)
{
	if (type == typeDrawing::points) {
		fl_line_style(FL_DOT, 2);
	}
	fl_begin_line();
	for (size_t i = 0; i < points.GetSize() - 1; i = i + 3)
	{
		fl_curve(points[i].x, points[i].y, 
			points[i + 1].x, points[i + 1].y,
			points[i + 2].x, points[i + 2].y,
			points[i + 3].x, points[i + 3].y);
	}
	fl_end_line();
}
void ViewFLTK::DrawCurveNew(const Array<double>& points, typeDrawing type) {
	if (type == typeDrawing::points) {
		fl_line_style(FL_DOT, 2);
	}
	fl_begin_line();
	for (size_t i = 0; i < points.GetSize() - 2; i = i + 6)
	{
		fl_curve(points[i], points[i + 1],
			points[i + 2], points[i + 3],
			points[i + 4], points[i + 5],
			points[i + 6], points[i + 7]);
	}
	fl_end_line();
}

void ViewFLTK::SetColor(int r, int g, int b)
{
	fl_color(fl_rgb_color(r, g, b));
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
		widjet = new IDisplayParamPrim("DisplayParamsPrim");
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
		widjet = new IDisplayParamReq("DisplayParamsReq");
		break;
	}
	case creatingToolbar:
	{
		widjet = new ICreatingToolbar("ToolBar");
		break;
	}
	case requirementInput:
	{
		RequirementInput* requirementInput = new RequirementInput();
		dataWidjet->Add("RequirementInput", requirementInput);
		widjet = new IRequirementInput("RequirementInput");
		break;
	}
	case drawMode:
	{
		widjet = new IRequirementInput("DrawMode");
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