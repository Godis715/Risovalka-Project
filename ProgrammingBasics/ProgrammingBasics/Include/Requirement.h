#ifndef REQUIREMENT_H
#define REQUIREMENT_H

class IRequirement{
public :
        virtual double error() = 0;
};

class RequirementPointsEq: public IRequirement
{
    public:
        RequirementPointsEq();
        virtual double error();
    private:
};

#endif // REQUIREMENT_H
