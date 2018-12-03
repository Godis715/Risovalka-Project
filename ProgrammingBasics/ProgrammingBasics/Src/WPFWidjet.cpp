#include "WPFWidget.h"

#pragma region WPFDisplayParamPrim
WPFDisplayParamPrim::WPFDisplayParamPrim() { }

WPFDisplayParamPrim::~WPFDisplayParamPrim() {
	auto mailBox = MailBox::GetInstance();
	Message massage;
	massage.code = properties_point;
	mailBox->SendMessage(massage);
}

void WPFDisplayParamPrim::SetParam(const Array<std::string>& params, const Array<std::string>& names) {
	auto mailBox = MailBox::GetInstance();
	Message massage;
	massage.code = properties_point;
	Array<std::string> strArr(0);
	strArr += params;
	strArr += names;
	massage.strArr = strArr;
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

void WPFDisplayParamReq::SetParam(const Array<std::string>& params, const std::string reqName) {
	auto mailBox = MailBox::GetInstance();
	Message massage;
	massage.code = properties_req;
	Array<std::string> strArr(0);
	strArr += params;
	strArr.PushBack(reqName);
	massage.strArr = strArr;
	mailBox->SendMessage(massage);
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

void SetName(const std::string) {
	auto mailBox = MailBox::GetInstance();
	Message massage;
	massage.code = current_draw_mode;
	mailBox->SendMessage(massage);
}
#pragma endregion
