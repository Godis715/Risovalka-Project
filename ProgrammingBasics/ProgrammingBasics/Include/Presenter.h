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
	Controller* controller;
	//ID CreatePoint(double, double);
	//ID CreateSegment(double, double, double, double);
	//ID CreateSegment(ID&, ID&);
	ID CreateArc(double, double, double, double, double);

	//bool CreateRequirmentDistBetPoints(ID, ID, double);
	bool CreateRequirmentPointsOnTheOneHand(ID, ID, ID);
	bool CreateRequirmentDistanceBetweenPointSegment(ID, ID, double);
	bool CreateRequirmentAngleBetweenSegments(ID, ID, double);
	bool CreateRequirmentDistanceBetweenPointArc(ID, ID, double);
	bool CreateRequirmentPointInArc(ID, ID);
	//bool CreateRequirmentTriangle(ID, ID, ID);
	//bool CreateRequirmentCorrectTriangle(ID, ID, ID, double);
	//bool CreateRequirmentNsAngle(Array<ID>&);
	//bool CreateRequirmentCorrectNsAngle(Array<ID>&, double);

	void DrawScene();

public:
	Presenter(IView*);

	Presenter();
	//~Presenter();

	void Optimize();
	void PrintSystemRequirement();
	bool getObjParam(const ID&, Array<double>&);
	bool GetObjType(const ID&, type_id&);

	bool GetClickedObjectID(double, double, ID&);

	void DrawPoint(double, double);
	void DrawSegment(double, double, double, double);
	void DrawTriangle(
		double, double, double, double,
		double, double, double, double,
		double, double, double, double
	);

	//
	ID CreatePoint(double, double);
	ID CreateSegment(double, double, double, double);
	ID CreateSegment(ID&, ID&);
	//ID CreateArc(double, double, double, double, double);


	bool CreateRequirmentDistBetPoints(ID, ID, double);
	//bool CreateRequirmentPointsOnTheOneHand(ID, ID, ID);
	//bool CreateRequirmentDistanceBetweenPointSegment(ID, ID, double);
	//bool CreateRequirmentAngleBetweenSegments(ID, ID, double);

	//bool CreateRequirmentDistanceBetweenPointArc(ID, ID, double);
	//bool CreateRequirmentPointInArc(ID, ID);
	bool CreateRequirmentTriangle(ID, ID, ID);
	bool CreateRequirmentCorrectTriangle(ID, ID, ID, double);
	bool CreateRequirmentNsAngle(Array<ID>&);
	bool CreateRequirmentCorrectNsAngle(Array<ID>&, double);

	void ClickSceneEvent(double, double);
	void KeyPressedEvent(char);
};
#endif // !__PRESENTER
