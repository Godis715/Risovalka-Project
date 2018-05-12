#pragma once
#include "IView.h"
#include "Model.h"

#define SINGLE_SELECTION
#define POLY_SELECTION
enum statusCreate { drawPoint, drawSegment, drawArc };

class Presenter {
private:
	BinSearchTree<ID, ID> selectedObjects;
	BinSearchTree<ID, ID> selectedReq;

	Array<ID> _selObj;
	Array<ID> _selReq;

	Model* model;

	void SelectObject(const ID&, int){}

	IView* view;


public:
	void drawScene()
	{
		Array<Model::infoObject> scene;
		if (model->DischargeInfoObjects(scene)) {
			for (int i = 0; i < scene.GetSize(); ++i) {
				if (scene[i].type == point_t) {
					view->SetColor(red);
					view->DrawPoint(Vector2(scene[i].params[0], scene[i].params[1]));
				}
				if (scene[i].type == segment_t) {
					view->SetColor(white);
					view->DrawLine(Vector2(scene[i].params[0], scene[i].params[1]),
						Vector2(scene[i].params[2], scene[i].params[3]), line);
				}
				if (scene[i].type == arc_t) {
					view->SetColor(white);
					view->DrawArc(Vector2(scene[i].params[0], scene[i].params[1]),
						Vector2(scene[i].params[2], scene[i].params[3]),
						Vector2(scene[i].params[4], scene[i].params[5]), line);
				}
			}
		}
	}

	Presenter(IView* _view)
	{
		view = _view;
		model = new Model();
	}

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

	//function for viewFLTK
	
	statusCreate status = drawSegment;
	Array<Vector2> posClicks;
	Array<double> params;

	bool isChangeStatus = false;

	void changeStatusCreate(statusCreate newStatus)
	{
		status = newStatus;
		posClicks.Clear();
		params.Clear();
		view->Clear();
	}

	void clearScene()
	{
		view->Clear();
		posClicks.Clear();
	}

	void clickOnScene(double x, double y)
	{
		view->SetColor(red);
		view->DrawPoint(Vector2(x, y));
		switch (status)
		{
			case drawPoint:
				params.PushBack(x);
				params.PushBack(y);
				CreateObject(point_t, params);
				params.Clear();
				break;
			case drawSegment:
				params.PushBack(x);
				params.PushBack(y);
				switch (posClicks.GetSize())
				{
				case 0:
					posClicks.PushBack(Vector2(x, y));
					break;
				case 1:
					CreateObject(segment_t, params);
					params.Clear();

					view->SetColor(white);
					view->DrawLine(posClicks[0], Vector2(x, y), line);
					posClicks.Clear();
					break;
				}
				break;
			case drawArc:
				switch (posClicks.GetSize())
				{
					case 0:
						posClicks.PushBack(Vector2(x, y));
						break;
					case 1:
						posClicks.PushBack(Vector2(x, y));

						//..
						view->SetColor(white);
						view->DrawCircle(posClicks[0], posClicks[1], points);
						//..
						break;
					case 2:
						params.PushBack(posClicks[1].x);
						params.PushBack(posClicks[1].y);
						params.PushBack(x);
						params.PushBack(y);
						params.PushBack(Vector2::Angle(posClicks[1] - posClicks[0], Vector2(x, y) - posClicks[0]));
						CreateObject(arc_t, params);
						params.Clear();

						//..
						view->SetColor(black);
						view->DrawCircle(posClicks[0], posClicks[1], points);
						//..

						view->SetColor(white);
						view->DrawArc(posClicks[0], posClicks[1], Vector2(x, y), line);

						view->SetColor(black);
						view->DrawPoint(posClicks[0]);
						posClicks.Clear();
						break;
				}
				break;
			}
		}
};