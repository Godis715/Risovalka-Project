#include "WPFWidget.h"

#pragma region WPFDisplayParamPrim
WPFDisplayParamPrim::WPFDisplayParamPrim() { }

WPFDisplayParamPrim::~WPFDisplayParamPrim() {
	auto mailBox = MailBox::GetInstance();
	auto message = new Message;
	message->code = properties_point;
	mailBox->SendMessage(message);
}

void WPFDisplayParamPrim::SetParam(const object_type type, const Array<double>& params, const Array<std::string>& names) {
	auto mailBox = MailBox::GetInstance();
	auto message = new Message;
	switch (type)
	{
	case ot_point:
	{
		message->code = properties_point;
		break;
	}
	case ot_segment:
	{
		message->code = properties_segment;
		break;
	}
	case ot_arc:
	{
		message->code = properties_arc;
		break;
	}
	case ot_circle:
	{
		message->code = properties_circle;
		break;
	}
	default:
		break;
	}
	message->doubleArr = params;
	message->strArr = names;
	mailBox->SendMessage(message);
}
#pragma endregion

#pragma region WPFDisplayParamReq
WPFDisplayParamReq::WPFDisplayParamReq() { }

WPFDisplayParamReq::~WPFDisplayParamReq() {
	auto mailBox = MailBox::GetInstance();
	auto message = new Message;
	message->code = properties_req;
	mailBox->SendMessage(message);
}

void WPFDisplayParamReq::SetParam(const Array<double>& params, const std::string reqName) {
	auto mailBox = MailBox::GetInstance();
	auto message = new Message;
	message->code = properties_req;
	message->doubleArr = params;
	message->strArr = CreateArr(reqName);
	mailBox->SendMessage(message);
}
#pragma endregion

#pragma region WPFCreatingToolbar
WPFCreatingToolbar::WPFCreatingToolbar() { }
WPFCreatingToolbar::~WPFCreatingToolbar() { }

void WPFCreatingToolbar::SetParam(const Array<std::string>& names) {
	auto mailBox = MailBox::GetInstance();
	auto message = new Message;
	message->code = possible_req;
	message->strArr = names;
	mailBox->SendMessage(message);
}

void WPFCreatingToolbar::Clear() {
	auto mailBox = MailBox::GetInstance();
	auto message = new Message;
	message->code = possible_req;
	mailBox->SendMessage(message);
}
#pragma endregion

#pragma region WPFRequirementInput
WPFRequirementInput::WPFRequirementInput() { }

WPFRequirementInput::~WPFRequirementInput() {
	auto mailBox = MailBox::GetInstance();
	auto message = new Message;
	message->code = delete_req_input;
	mailBox->SendMessage(message);
}
#pragma endregion

#pragma region WPFDrawMode
WPFDrawMode::WPFDrawMode(){
	auto mess = new Message;
	(mess->code) = 4;


	(mess->doubleArr) = CreateArr(1.0, 2.0);
	MailBox::GetInstance()->SendMessage(mess);
}
WPFDrawMode::~WPFDrawMode(){ }

void WPFDrawMode::SetName(const std::string) {
	auto mailBox = MailBox::GetInstance();
	auto message = new Message;
	message->code = current_draw_mode;

	/*message->strArray..*/

	mailBox->SendMessage(message);
}
#pragma endregion
