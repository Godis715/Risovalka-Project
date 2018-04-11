#ifndef __PRESENTER
#define __PRESENTER

#include "Model.h"
#include "IView.h"

class Controller;


class Presenter
{
private:
	Model* model;
	IView* view;

	// try this !!!!
	bool CreateRequirement(Requirement_id, const Array<ID>&, const Array<double>&);

	// too many similar functions
	bool CreateRequirmentDistBetPoints(ID, ID, double);
	bool CreateRequirmentPointsOnTheOneHand(ID, ID, ID);
	bool CreateRequirmentDistanceBetweenPointSegment(ID, ID, double);
	bool CreateRequirmentAngleBetweenSegments(ID, ID, double);
	bool CreateRequirmentDistanceBetweenPointArc(ID, ID, double);
	bool CreateRequirmentPointInArc(ID, ID);
	bool CreateRequirmentTriangle(ID, ID, ID);
	bool CreateRequirmentCorrectTriangle(ID, ID, ID, double);
	bool CreateRequirmentNsAngle(Array<ID>&);
	bool CreateRequirmentCorrectNsAngle(Array<ID>&, double);
	//
	void DrawScene();
public:
	Presenter(IView*);
	//create destructor
	~Presenter();

	void Optimize();
};
#endif // !__PRESENTER
