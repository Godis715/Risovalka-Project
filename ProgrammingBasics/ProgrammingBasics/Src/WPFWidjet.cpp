#include "WPFWidget.h"

#pragma region WPFDisplayParamPrim
WPFDisplayParamPrim::WPFDisplayParamPrim() { }

WPFDisplayParamPrim::~WPFDisplayParamPrim() {
	auto mailBox = MailBox::GetInstance();
	Message massage;
	massage.code = properties_point;
	mailBox->SendMessage(massage);
}

void WPFDisplayParamPrim::SetParam(const object_type type, const Array<double>& params, const Array<std::string>& names) {
	auto mailBox = MailBox::GetInstance();
	Message massage;
	switch (type)
	{
	case ot_point:
	{
		massage.code = properties_point;
		break;
	}
	case ot_segment:
	{
		massage.code = properties_segment;
		break;
	}
	case ot_arc:
	{
		massage.code = properties_arc;
		break;
	}
	case ot_circle:
	{
		massage.code = properties_circle;
		break;
	}
	default:
		break;
	}
	massage.doubleArr = params;
	massage.strArr = names;
	mailBox->SendMessage(massage);
}
#pragma endregion

#pragma region WPFDisplayParamReq
WPFDisplayParamReq::WPFDisplayParamReq() { }

WPFDisplayParamReq::~WPFDisplayParamReq() {
	auto mailBox = MailBox::GetInstance();
	Message massage;
	massage.code = properties_req;
	mailBox->SendMessage(massage);
}

void WPFDisplayParamReq::SetParam(const Array<double>& params, const std::string reqName) {
	auto mailBox = MailBox::GetInstance();
	Message message;
	message.code = properties_req;
	message.doubleArr = params;
	message.strArr = CreateArr(reqName);
	mailBox->SendMessage(message);
}
#pragma endregion

#pragma region WPFCreatingToolbar
WPFCreatingToolbar::WPFCreatingToolbar() { }
WPFCreatingToolbar::~WPFCreatingToolbar() { }

void WPFCreatingToolbar::SetParam(const Array<std::string>& names) {
	auto mailBox = MailBox::GetInstance();
	Message massage;
	massage.code = possible_req;
	massage.strArr = names;
	mailBox->SendMessage(massage);
}

void WPFCreatingToolbar::Clear() {
	auto mailBox = MailBox::GetInstance();
	Message massage;
	massage.code = possible_req;
	mailBox->SendMessage(massage);
}
#pragma endregion

#pragma region WPFRequirementInput
WPFRequirementInput::WPFRequirementInput() { }

WPFRequirementInput::~WPFRequirementInput() {
	auto mailBox = MailBox::GetInstance();
	Message massage;
	massage.code = delete_req_input;
	mailBox->SendMessage(massage);
}
#pragma endregion

#pragma region WPFDrawMode
WPFDrawMode::WPFDrawMode(){ }
WPFDrawMode::~WPFDrawMode(){ }

void WPFDrawMode::SetName(const std::string) {
	auto mailBox = MailBox::GetInstance();
	Message massage;
	massage.code = current_draw_mode;
	mailBox->SendMessage(massage);
}
#pragma endregion
