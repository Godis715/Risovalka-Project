#include "ViewFLTK.h"
#include "FLTKWidget.h"


#pragma region IWidjet

#pragma endregion


#pragma region IDisplayParam
FLTKDisplayParamPrim::FLTKDisplayParamPrim(const string _pass) : password(_pass) {}

FLTKDisplayParamPrim::~FLTKDisplayParamPrim() {
	auto view = ViewFLTK::GetInstance();
	view->DeleteWidjet(password);
}

void FLTKDisplayParamPrim::SetParam(const Array<std::string>& params, const Array<std::string>& names) {
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
FLTKDisplayParamReq::FLTKDisplayParamReq(const string _pass) : password(_pass) {}

FLTKDisplayParamReq::~FLTKDisplayParamReq() {
	auto view = ViewFLTK::GetInstance();
	view->DeleteWidjet(password);
}

void FLTKDisplayParamReq::SetParam(const Array<std::string>& params, const std::string name) {
	auto view = ViewFLTK::GetInstance();
	auto widjet = dynamic_cast<DisplayParamsReq*>(view->GetWidjet(password));
	auto mainWindow = dynamic_cast<MainWindow*>(view->GetWidjet("MainWindow"));
	mainWindow->begin();
	widjet->Clear();
	widjet->Inizializatoin(params, name);
	mainWindow->end();
	mainWindow->redraw();
}
#pragma endregion

#pragma region ICreatingToolbar
FLTKCreatingToolbar::FLTKCreatingToolbar(const std::string _pass) : password(_pass) {

}

FLTKCreatingToolbar::~FLTKCreatingToolbar() {
	Clear();
}

void FLTKCreatingToolbar::SetParam(const Array<std::string>& names) {
	auto view = ViewFLTK::GetInstance();
	auto widjet = dynamic_cast<ViewToolbar*>(view->GetWidjet(password));
	auto mainWindow = dynamic_cast<MainWindow*>(view->GetWidjet("MainWindow"));
	mainWindow->begin();
	widjet->ClearRequirements();
	widjet->SetRequirements(names);
	mainWindow->end();
	mainWindow->redraw();
}


void FLTKCreatingToolbar::Clear() {
	auto view = ViewFLTK::GetInstance();
	auto widjet = dynamic_cast<ViewToolbar*>(view->GetWidjet(password));
	widjet->ClearRequirements();
}
#pragma endregion

#pragma region IRequirementInput
FLTKRequirementInput::FLTKRequirementInput(const std::string _pass) : password(_pass) {}

FLTKRequirementInput::~FLTKRequirementInput() {
	auto view = ViewFLTK::GetInstance();
	view->DeleteWidjet(password);
}
#pragma endregion

#pragma region IDrawMode
FLTKDrawMode::FLTKDrawMode(const std::string _pass) : password(_pass) {

}

FLTKDrawMode::~FLTKDrawMode() {}

void FLTKDrawMode::SetName(const std::string nameMode) {
	auto view = ViewFLTK::GetInstance();
	auto widjet = dynamic_cast<DrawMode*>(view->GetWidjet(password));
	auto mainWindow = dynamic_cast<MainWindow*>(view->GetWidjet("MainWindow"));
	mainWindow->begin();
	widjet->SetName(nameMode);
	mainWindow->end();
	mainWindow->redraw();
}

#pragma endregion