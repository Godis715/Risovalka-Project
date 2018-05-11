#pragma once
#include "IView.h"
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



	void SelectObject(const ID&, int);


public:
	Presenter(IView*);

	/* using for creating figures
	 points, segments, arcs, circles .. */
	void CreateObject(object_type, const Array<double>&);

	/* trying to impose requirements
	on selected object */
	bool CreateRequirement(object_type, const Array<double>&);

	void DeletePrimitives();

	void DeleteRequirement(int);

	void ChangeParamRequirement(int, const double);

	void ScaleObject(double);

	void MoveObject(const Vector2&);

	void ChangeObject();

	void GetRequirements();
};