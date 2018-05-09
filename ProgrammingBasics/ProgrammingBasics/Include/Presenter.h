#pragma once
#include "IView.h"

#define SINGLE_SELECTION
#define POLY_SELECTION

class Presenter {
private:
	BinSearchTree<ID, ID> selectedObjects;

	BinSearchTree<ID, ID> selectedReq;



	void SelectObject(const ID&, int);


public:
	Presenter(IView*);

	/* using for creating figures
	 points, segments, arcs, circles .. */
	void CreateObject(prim_type, const Array<double>&);

	/* trying to impose requirements
	on selected object */
	bool CreateRequirement(req_type, const Array<double>&);

	void DeleteRequirement(int);

	void ChangeParamsRequirement(int, double);

	void ScaleObject(double);

	void MoveObject(Vector2&);

	void ChangeObject();
};