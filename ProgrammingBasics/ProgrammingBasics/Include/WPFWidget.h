#ifndef __WPFWidget
#define __WPFKWidget

#include "IWidjet.h"
#include "MailBox.h"

using namespace DrawProject;

class WPFDisplayParamPrim : public IDisplayParamPrim
{
public:
	WPFDisplayParamPrim();

	~WPFDisplayParamPrim();

	void SetParam(const object_type, const Array<double>&, const Array<std::string>&);
};

class WPFDisplayParamReq : public IDisplayParamReq
{
public:
	WPFDisplayParamReq();

	~WPFDisplayParamReq();

	void SetParam(const Array<double>&, const std::string);
};

class WPFCreatingToolbar : public ICreatingToolbar
{
public:
	WPFCreatingToolbar();
	~WPFCreatingToolbar();

	void SetParam(const Array<std::string>&);

	void Clear();
};

class WPFRequirementInput : public IRequirementInput
{
public:
	WPFRequirementInput();

	~WPFRequirementInput();
};

class WPFDrawMode : public IDrawMode
{
public:
	WPFDrawMode();
	~WPFDrawMode();

	void SetName(const std::string);
};

#endif