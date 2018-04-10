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

	// temp, while we using WINAPI
	Controller* controller;

	//ID CreatePoint(double, double);
	//ID CreateSegment(double, double, double, double);
	//ID CreateSegment(ID&, ID&);
	//ID CreateArc(double, double, double, double, double);

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
	Presenter();
	//create destructor
	~Presenter();

	void Optimize();
	// void PrintSystemRequirement();

	// useless functions
	//bool getObjParam(const ID&, Array<double>&);
	//bool GetObjType(const ID&, type_id&);

	// useless 
	//bool GetClickedObjectID(double, double, ID&);

	void DrawPoint(double, double);
	void DrawSegment(double, double, double, double);

	//
	
	//ID CreateSegment(ID&, ID&);
	//ID CreateArc(double, double, double, double, double);


	//bool CreateRequirmentDistBetPoints(ID, ID, double);
	//bool CreateRequirmentPointsOnTheOneHand(ID, ID, ID);
	//bool CreateRequirmentDistanceBetweenPointSegment(ID, ID, double);
	//bool CreateRequirmentAngleBetweenSegments(ID, ID, double);

	//bool CreateRequirmentDistanceBetweenPointArc(ID, ID, double);
	//bool CreateRequirmentPointInArc(ID, ID);
	//bool CreateRequirmentTriangle(ID, ID, ID);
	//bool CreateRequirmentCorrectTriangle(ID, ID, ID, double);
	//bool CreateRequirmentNsAngle(Array<ID>&);
	//bool CreateRequirmentCorrectNsAngle(Array<ID>&, double);

	void ClickSceneEvent(double, double);
	void KeyPressedEvent(char);
};
#endif // !__PRESENTER
