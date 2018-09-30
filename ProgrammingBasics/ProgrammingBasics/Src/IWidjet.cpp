#include "ViewFLTK.h"
#include "IWidjet.h"



IWidjet::IWidjet(const std::string _pass) : password(_pass) {}

IDisplayParam::IDisplayParam(const string _pass) : IWidjet(_pass) {

}

IDisplayParam::~IDisplayParam() {

}

void IDisplayParam::SetParam(const Array<std::string>& params, const Array<std::string>& names) {

}

ICreateToolbar::ICreateToolbar(const std::string _pass) : IWidjet(_pass) {

}

void ICreateToolbar::SetParam(const Array<std::string>& names) {

}

IRequirementInput::IRequirementInput(const std::string _pass) : IWidjet(_pass) {}

IRequirementInput::~IRequirementInput() {

}