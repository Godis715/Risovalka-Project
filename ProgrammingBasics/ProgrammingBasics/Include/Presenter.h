#pragma once
#include "IView.h"

#define SINGLE_SELECTION
#define POLY_SELECTION

class Presenter {
private:
	BinSearchTree<ID, ID> selectedObjects;

	BinSearchTree<ID, ID> selectedReq;



	void SelectObject(const ID&, int){}

	IView* view;

public:
	Presenter(IView* _view)
	{
		view = _view;
	}

	/* using for creating figures
	 points, segments, arcs, circles .. */
	void CreateObject(object_type, const Array<double>&){}

	/* trying to impose requirements
	on selected object */
	bool CreateRequirement(object_type, const Array<double>&){}

	void DeleteRequirement(int){}

	void ChangeParamsRequirement(int, double){}

	void ScaleObject(double){}

	void MoveObject(Vector2&){}

	void ChangeObject(){}

	void test(int x, int y)
	{
		view->SetColor(red);
		view->DrawPoint(Vector2(x, y));
	}
	void test2()
	{
		view->Clear();
	}
};