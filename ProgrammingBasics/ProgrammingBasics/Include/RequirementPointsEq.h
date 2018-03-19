#pragma once
#include "Requirement.h"

class RequirementPointsEq : public IRequirement
{
public:
	RequirementPointsEq();
	virtual double error();
private:

};