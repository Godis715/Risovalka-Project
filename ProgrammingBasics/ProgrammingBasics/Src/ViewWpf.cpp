#include "ViewWPF.h"


void ViewWPF::DrawPoint(const Array<double>& params) {
	auto message = new Message;
	message->code = draw_point;
	message->doubleArr = params;
	mailBox->SendMessage(message);
}

void ViewWPF::DrawLine(const Array<double>& params) {
	auto message = new Message;
	message->code = draw_segment;
	message->doubleArr = params;
	mailBox->SendMessage(message);
}

void ViewWPF::DrawCircle(const Array<double>& params) {
	auto message = new Message;
	message->code = draw_circle;
	message->doubleArr = params;
	mailBox->SendMessage(message);
}

void ViewWPF::DrawArc(const Array<double>& params) {
	auto message = new Message;
	message->code = draw_arc;
	message->doubleArr = params;
	mailBox->SendMessage(message);
}

void ViewWPF::DrawCurve(const Array<double>& params) {
	auto message = new Message;
	message->code = draw_curve;
	message->doubleArr = params;
	mailBox->SendMessage(message);
}

void ViewWPF::SetStyleDrawing(const rgbColor color, const typeDrawing type) {
	auto message = new Message;
	message->code = set_style;
	int y = int(type);
	message->intArr = CreateArr(color.r, color.g, color.b, y);
	mailBox->SendMessage(message);
}

int ViewWPF::Run() {
	presenter->Initializer(this);
	return 0;
}
void ViewWPF::Update() {
	presenter->DrawScene();
}

void ViewWPF::TranslateScene(const Vector2& vector) {
	auto message = new Message;
	message->code = translate_scene;
	message->doubleArr = CreateArr(vector.x, vector.y);
}
void ViewWPF::ScaleScene(const double& coef) {
	auto message = new Message;
	message->code = scale_scene;
	message->doubleArr = CreateArr(coef);
}
void ViewWPF::RotateScene(const double& coef) {
	auto message = new Message;
	message->code = rotate_scene;
	message->doubleArr = CreateArr(coef);
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
	presenter = Presenter::GetInstance();
}

ViewWPF* ViewWPF::instance = nullptr;