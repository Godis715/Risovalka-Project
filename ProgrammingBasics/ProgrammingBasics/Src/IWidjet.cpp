#include "ViewFLTK.h"
#include "IWidjet.h"



IWidjet::IWidjet(const std::string _pass) : password(_pass) {}

IWidjet::~IWidjet() {

}

IDisplayParam::IDisplayParam(const string _pass) : IWidjet(_pass) {}

IDisplayParam::~IDisplayParam() {
	auto view = ViewFLTK::GetInstance();
	view->DeleteWidjet(password);
}

void IDisplayParam::SetParam(const Array<std::string>& params, const Array<std::string>& names) {
	auto view = ViewFLTK::GetInstance();
	auto widjet = dynamic_cast<DisplayParams*>(view->GetWidjet(password));
	auto mainWindow = dynamic_cast<MainWindow*>(view->GetWidjet("MainWindow"));
	mainWindow->begin();
	widjet->Inizializatoin(params, names);
	mainWindow->end();
	mainWindow->redraw();
}

ICreatingToolbar::ICreatingToolbar(const std::string _pass) : IWidjet(_pass) {

}

void ICreatingToolbar::SetParam(const Array<std::string>& names) {

}

IRequirementInput::IRequirementInput(const std::string _pass) : IWidjet(_pass) {}

IRequirementInput::~IRequirementInput() {

}