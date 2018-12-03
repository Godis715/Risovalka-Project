#include "ViewWPF.h"


void ViewWPF::DrawPoint(const Array<double>& params) {
	Message message;
	message.code = draw_point;
	message.doubleArr = params;
	mailBox->SendMessage(message);
}

void ViewWPF::DrawLine(const Array<double>& params) {
	Message message;
	message.code = draw_segment;
	message.doubleArr = params;
	mailBox->SendMessage(message);
}

void ViewWPF::DrawCircle(const Array<double>& params) {
	Message message;
	message.code = draw_circle;
	message.doubleArr = params;
	mailBox->SendMessage(message);
}

void ViewWPF::DrawArc(const Array<double>& params) {
	Message message;
	message.code = draw_arc;
	message.doubleArr = params;
	mailBox->SendMessage(message);
}

void ViewWPF::DrawCurve(const Array<double>& params) {
	Message message;
	message.code = draw_curve;
	message.doubleArr = params;
	mailBox->SendMessage(message);
}

void ViewWPF::SetStyleDrawing(const int, const int, const int, const typeDrawing) {
	Message messege;
	messege.code = set_style;
	messege.intArr = CreateArr(color.r, color.g, color.b, type);
}

int ViewWPF::Run() {
	return 0;
}
void ViewWPF::Update() {
	Presenter::DrawScene();
}

void ViewWPF::TranslateScene(const Vector2& vector) {
	Message messege;
	messege.code = translate_scene;
	messege.doubleArr = CreateArr(vector.x, vector.y);
}
void ViewWPF::ScaleScene(const double& coef) {
	Message messege;
	messege.code = scale_scene;
	messege.doubleArr = CreateArr(coef);
}
void ViewWPF::RotateScene(const double& coef) {
	Message messege;
	messege.code = rotate_scene;
	messege.doubleArr = CreateArr(coef);
}

IWidjet* ViewWPF::GetWidjet(const typeWidjet _type) {
	IWidjet* widjet;
	switch (_type)
	{
	case displayParamPrim:
	{
		widjet = new WPFDisplayParamPrim;
		break;
	}
	case displayParamReq:
	{
		widjet = new WPFDisplayParamReq;
		break;
	}
	case creatingToolbar:
	{
		widjet = new WPFCreatingToolbar;
		break;
	}
	case requirementInput:
	{
		widjet = new WPFRequirementInput;
		break;
	}
	case drawMode:
	{
		widjet = new WPFDrawMode();
		break;
	}
	default:
		widjet = nullptr;
		break;
	}
	return widjet;
}

ViewWPF* ViewWPF::GetInstance() {
	if (instance == nullptr) {
		instance = new ViewWPF;
	}
	return instance;
}

ViewWPF::ViewWPF() : IView() {
	mailBox = MailBox::GetInstance();
}

ViewWPF* ViewWPF::instance = nullptr;