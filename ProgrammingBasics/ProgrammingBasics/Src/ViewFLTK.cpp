#include "ViewFLTK.h"
#include "FLTKWidget.h"

ViewFLTK::ViewFLTK()
{
	presenter = Presenter::GetInstance();
	colorTheme = Color::GetInstance();

	dataWidjet = new DataWidjet();

	inventory = inventory->GetInstance();

	mainWindow = new MainWindow(1300, 660, "Main Window");
	auto color = colorTheme->BackGround();
	mainWindow->color(fl_rgb_color(color.r, color.g, color.b));
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
	presenter->Initializer(this);
	return Fl::run(); 
}

void ViewFLTK::SetStyleDrawing(const rgbColor color, const typeDrawing type)
{
	fl_color(fl_rgb_color(color.r, color.g, color.b));
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

void ViewFLTK::DrawLine(const Array<double>& params)
{
	fl_begin_line();
	fl_vertex(params[0], params[1]);
	fl_vertex(params[2], params[3]);
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

void ViewFLTK::DrawArc(const Array<double>& params)
{
	double Eps = 5.0;
	double r = params[6];
	double angle = params[7] * (180 / PI);
	double angleStart = (r < Eps) ? 0.0 : acos((params[0] - params[4]) / r) * (180 / PI);
	if (params[5] - params[1] < 0) {
		angleStart = 360.0 - angleStart;
	}
	fl_begin_line();
	_DrawArc(Vector2(params[4], params[5]), r, angleStart, angleStart + angle);
	fl_end_line();
}

void ViewFLTK::DrawPoint(const Array<double>& params)
{
	fl_begin_polygon();
	fl_arc(params[0], params[1], 2, 0.0, 360.0);
	fl_end_polygon();
}

void ViewFLTK::Update()
{
	auto color = colorTheme->BackGround();
	mainWindow->color(fl_rgb_color(color.r, color.g, color.b));
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

	return *markerDataWidjet; // ����������!
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


void ViewFLTK::DrawCurve(const Array<double>& points) {
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

Inventory* ViewFLTK::inventory = nullptr;

ViewLog* ViewFLTK::viewLog = nullptr;

MainWindow* ViewFLTK::mainWindow;
DrawWindow* ViewFLTK::drawWindow;

Color* ViewFLTK::colorTheme = nullptr;

ViewFLTK* ViewFLTK::instance = nullptr;

Presenter* ViewFLTK::presenter = nullptr;