#ifndef __IWIDJET
#define __IWIDJET
#include <string>
#include "Array.h"

class IWidjet
{
public:
};

class IDisplayParamPrim : public IWidjet
{
public:
	virtual void SetParam(const Array<std::string>&, const Array<std::string>&) = 0;
	virtual ~IDisplayParamPrim() { }
};

class IDisplayParamReq : public IWidjet
{
public:
	virtual void SetParam(const Array<std::string>&, const std::string) = 0;
	virtual ~IDisplayParamReq() { }

};

class ICreatingToolbar : public IWidjet
{
public:
	virtual void SetParam(const Array<std::string>&) = 0;
	virtual void Clear() = 0;
	virtual ~ICreatingToolbar() { }

};

class IRequirementInput : public IWidjet
{
public:
	virtual ~IRequirementInput() { }
};

class IDrawMode : public IWidjet
{
public:
	virtual void SetName(const std::string) = 0;
	virtual ~IDrawMode() { }
};



#endif __IWIDJET