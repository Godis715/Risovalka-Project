#include "ViewFLTK.h"

ViewFLTK::ViewFLTK()
{
	dataWidjet = new DataWidjet();

	inventory = inventory->GetInstance();

	mainWindow = new MainWindow(1300, 620, "Main Window");
	DisplayWidjet* mainWindowWidjet = mainWindow;
	dataWidjet->Add("MainWindow", mainWindowWidjet);

	DisplayWidjet* viewToolbar = new ViewToolbar();
	dataWidjet->Add("ToolBar", viewToolbar);

	DisplayWidjet* viewFile = new ViewFile();
	dataWidjet->Add("WorkFile", viewFile);

	viewLog = ViewLog::GetInstance();
	
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
		widjet = new IDisplayParam("DisplayParamsPrim");
		break;
	}
	case displayParamReq:
	{
		auto displayParamsPrim = dynamic_cast<DisplayParamsPrim*>(GetWidjet("DisplayParamsPrim"));
		Array<int> paramsDisp;
		displayParamsPrim->GetParamDisplay(paramsDisp);
		int coordX = paramsDisp[0];
		int coordY = paramsDisp[1] + paramsDisp[3] + 10;
		DisplayParamsReq* displayParamsReq = new DisplayParamsReq(coordX, coordY);
		dataWidjet->Add("DisplayParamsReq", displayParamsReq);
		widjet = new IDisplayParam("DisplayParamsReq");//исправить
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