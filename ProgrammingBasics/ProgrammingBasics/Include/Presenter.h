#pragma once
// #include "IView.h"
#include "Model.h"

#define SINGLE_SELECTION
#define POLY_SELECTION

class Presenter {
private:
	BinSearchTree<ID, ID> selectedObjects;
	BinSearchTree<ID, ID> selectedReq;

	Array<ID> _selObj;
	Array<ID> _selReq;

	Model* model;



	void SelectObject(const ID&, int){}

	// IView* view;

public:
	/*Presenter(IView* _view)
	{
		view = _view;
	}*/

	/* using for creating figures
	 points, segments, arcs, circles .. */
	void CreateObject(object_type, const Array<double>&);

	/* trying to impose requirements
	on selected object */

	bool CreateRequirement(object_type, const Array<double>&);

	void DeletePrimitives();

	void DeleteRequirement(int);

	void ChangeParamRequirement(int, const double);

	void ScaleObjects(const double);

	void MoveObject(const Vector2&);

	void ChangeObject(){}

	void GetRequirements();

	//function for test viewFLTK
	/*void test(int x, int y)
	{
		view->SetColor(red);
		view->DrawPoint(Vector2(x, y));
	}
	void test2()
	{
		view->Clear();
	}*/
	//
};