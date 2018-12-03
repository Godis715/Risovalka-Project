#ifndef __WPFWidget
#define __WPFKWidget

#include "IWidjet.h"


class WPFDisplayParamPrim : public IDisplayParamPrim
{
public:
	WPFDisplayParamPrim(const std::string);

	~WPFDisplayParamPrim();

	void SetParam(const Array<std::string>&, const Array<std::string>&);
};

class WPFDisplayParamReq : public IDisplayParamReq
{
public:
	WPFDisplayParamReq(const std::string);

	~WPFDisplayParamReq();

	void SetParam(const Array<std::string>&, const std::string);
};

class WPFCreatingToolbar : public ICreatingToolbar
{
public:
	WPFCreatingToolbar(const std::string);
	~WPFCreatingToolbar();

	void SetParam(const Array<std::string>&);

	void Clear();
};

class WPFRequirementInput : public IRequirementInput
{
public:
	WPFRequirementInput(const std::string);

	~WPFRequirementInput();
};

class WPFDrawMode : public IDrawMode
{
public:
	WPFDrawMode(const std::string);
	~WPFDrawMode();

	void SetName(const std::string);
};

#endif