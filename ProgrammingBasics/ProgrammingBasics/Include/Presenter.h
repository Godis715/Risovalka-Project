#ifndef __PRESENTER
#define __PRESENTER

#include "Model.h"
#include "View.h"

class Presenter
{
private:
	Model* model;
	View* view;
	
public:
	Presenter(View*);
	Presenter() {
		model = new Model;
	}
	//~Presenter();

	ID CreatePoint(double, double);
	ID CreateSegment(double, double, double, double);
	ID CreateSegment(ID&, ID&);
	ID CreateArc(double, double, double, double, double);

	void CreateRequirmentDistBetPoints(ID, ID, double);
	void CreateRequirmentPointsOnTheOneHand(ID, ID, ID);
	void CreateRequirmentDistanceBetweenPointSegment(ID, ID, double);
	void CreateRequirmentAngleBetweenSegments(ID, ID, double);
	void CreateRequirmentDistanceBetweenPointArc(ID, ID, double);
	void CreateRequirmentPointInArc(ID, ID);
	void CreateRequirmentTriangle(ID, ID, ID);
	void CreateRequirmentBestTriangle(ID, ID, ID, double);

	int Optimize();
	void PrintSystemRequirement();
	bool getObjParam(const ID&, Array<double>&);

	void DrawPoint(double, double);
	void DrawSegment(double, double, double, double);
	void DrawTriangle(
		double, double, double, double,
		double, double, double, double,
		double, double, double, double
	);

};
#endif // !__PRESENTER
