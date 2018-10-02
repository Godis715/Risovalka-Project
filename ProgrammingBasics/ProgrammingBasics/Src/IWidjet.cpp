#include "ViewFLTK.h"
#include "IWidjet.h"


#pragma region IWidjet
IWidjet::IWidjet(const std::string _pass) : password(_pass) {}

IWidjet::~IWidjet() {

}
#pragma endregion


#pragma region IDisplayParam
IDisplayParamPrim::IDisplayParamPrim(const string _pass) : IWidjet(_pass) {}

IDisplayParamPrim::~IDisplayParamPrim() {
	auto view = ViewFLTK::GetInstance();
	view->DeleteWidjet(password);
}

void IDisplayParamPrim::SetParam(const Array<std::string>& params, const Array<std::string>& names) {
	auto view = ViewFLTK::GetInstance();
	auto widjet = dynamic_cast<DisplayParamsPrim*>(view->GetWidjet(password));
	auto mainWindow = dynamic_cast<MainWindow*>(view->GetWidjet("MainWindow"));
	mainWindow->begin();
	widjet->Clear();
	widjet->Inizializatoin(params, names);
	mainWindow->end();
	mainWindow->redraw();
}
#pragma endregion

#pragma region IDisplayParamReq
IDisplayParamReq::IDisplayParamReq(const string _pass) : IWidjet(_pass) {}

IDisplayParamReq::~IDisplayParamReq() {
	auto view = ViewFLTK::GetInstance();
	view->DeleteWidjet(password);
}

void IDisplayParamReq::SetParam(const Array<std::string>& params, const std::string name) {
	/*auto view = ViewFLTK::GetInstance();
	auto widjet = dynamic_cast<DisplayParamReq*>(view->GetWidjet(password));
	auto mainWindow = dynamic_cast<MainWindow*>(view->GetWidjet("MainWindow"));
	mainWindow->begin();
	widjet->Clear();
	widjet->Inizializatoin(params, name);
	mainWindow->end();
	mainWindow->redraw();*/
}
#pragma endregion

#pragma region ICreatingToolbar
ICreatingToolbar::ICreatingToolbar(const std::string _pass) : IWidjet(_pass) {

}

ICreatingToolbar::~ICreatingToolbar() {
	Clear();
}

void ICreatingToolbar::SetParam(const Array<std::string>& names) {
	auto view = ViewFLTK::GetInstance();
	auto widjet = dynamic_cast<ViewToolbar*>(view->GetWidjet(password));
	auto mainWindow = dynamic_cast<MainWindow*>(view->GetWidjet("MainWindow"));
	mainWindow->begin();
	widjet->ClearRequirements();
	widjet->SetRequirements(names);
	mainWindow->end();
	mainWindow->redraw();
}


void ICreatingToolbar::Clear() {
	auto view = ViewFLTK::GetInstance();
	auto widjet = dynamic_cast<ViewToolbar*>(view->GetWidjet(password));
	widjet->ClearRequirements();
}
#pragma endregion

#pragma region IRequirementInput
IRequirementInput::IRequirementInput(const std::string _pass) : IWidjet(_pass) {}

IRequirementInput::~IRequirementInput() {
	auto view = ViewFLTK::GetInstance();
	view->DeleteWidjet(password);
}
#pragma endregion