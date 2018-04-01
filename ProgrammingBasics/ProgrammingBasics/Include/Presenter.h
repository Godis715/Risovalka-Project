#ifndef __PRESENTER
#define __PRESENTER

#include "Model.h"
#include "IView.h"

class Presenter
{
private:
	Model* model;
	IView* view;
	
	ID CreatePoint(double, double);
<<<<<<< HEAD
	//ID CreateSegment(double, double, double, double);
	ID CreateSegment(ID&, ID&);
	ID CreateArc(double, double, double, double, double);

	bool CreateRequirmentDistBetPoints(ID, ID, double);
	bool CreateRequirmentPointsOnTheOneHand(ID, ID, ID);
	bool CreateRequirmentDistanceBetweenPointSegment(ID, ID, double);
	bool CreateRequirmentAngleBetweenSegments(ID, ID, double);
	bool CreateRequirmentDistanceBetweenPointArc(ID, ID, double);
	bool CreateRequirmentPointInArc(ID, ID);
	bool CreateRequirmentTriangle(ID, ID, ID);
	bool CreateRequirmentCorrectTriangle(ID, ID, ID, double);
	//bool CreateRequirmentNsAngle(Array<ID>&);
	//bool CreateRequirmentCorrectNsAngle(Array<ID>&, double);
=======
	ID CreateSegment(double, double, double, double);
	//ID CreateSegment(ID&, ID&);
	ID CreateArc(double, double, double, double, double);

	void CreateRequirmentDistBetPoints(ID, ID, double);
	void CreateRequirmentPointsOnTheOneHand(ID, ID, ID);
	void CreateRequirmentDistanceBetweenPointSegment(ID, ID, double);
	void CreateRequirmentAngleBetweenSegments(ID, ID, double);
	void CreateRequirmentDistanceBetweenPointArc(ID, ID, double);
	void CreateRequirmentPointInArc(ID, ID);
	void CreateRequirmentTriangle(ID, ID, ID);
	void CreateRequirmentBestTriangle(ID, ID, ID, double);
>>>>>>> DimaTereschenko

	void DrawScene();

public:
	Presenter(IView*);
<<<<<<< HEAD
	Presenter() {
		model = new Model;
	}
	//~Presenter();

=======
	Presenter();
	//~Presenter();


>>>>>>> DimaTereschenko
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

	//
	//ID CreatePoint(double, double);
	ID CreateSegment(double, double, double, double);
	//ID CreateSegment(ID&, ID&);
	//ID CreateArc(double, double, double, double, double);


	/*bool CreateRequirmentDistBetPoints(ID, ID, double);
	bool CreateRequirmentPointsOnTheOneHand(ID, ID, ID);
	bool CreateRequirmentDistanceBetweenPointSegment(ID, ID, double);
	bool CreateRequirmentAngleBetweenSegments(ID, ID, double);
	bool CreateRequirmentDistanceBetweenPointArc(ID, ID, double);
	bool CreateRequirmentPointInArc(ID, ID);
	bool CreateRequirmentTriangle(ID, ID, ID);
	bool CreateRequirmentCorrectTriangle(ID, ID, ID, double);*/
	bool CreateRequirmentNsAngle(Array<ID>&);
	bool CreateRequirmentCorrectNsAngle(Array<ID>&, double);
};
#endif // !__PRESENTER
