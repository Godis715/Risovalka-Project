#ifndef __WPFWidget
#define __WPFKWidget

#include "IWidjet.h"
#include "MailBox.h"


class WPFDisplayParamPrim : public IDisplayParamPrim
{
public:
	WPFDisplayParamPrim();

	~WPFDisplayParamPrim();

	void SetParam(const Array<std::string>&, const Array<std::string>&);
};

class WPFDisplayParamReq : public IDisplayParamReq
{
public:
	WPFDisplayParamReq();

	~WPFDisplayParamReq();

	void SetParam(const Array<std::string>&, const std::string);
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